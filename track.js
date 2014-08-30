require('js-yaml');
var stdin = process.openStdin();
var settings = require('./config.yaml');
var Server = require('./lib/server.js');
var server = new Server(settings);
var track = require("./build/Release/obj.target/track.node");

console.log( track.locatePoint(function(msg) {
	console.log(msg);
	server.sendUpdate('serverStatus', msg);
}));


//update server with point data
var lastPoint;
var pointUpdate = setInterval(function() {
	var newPoint = track.getDataPoint();
	console.log(JSON.stringify(newPoint));
	if(lastPoint != newPoint) {
		server.sendUpdate('point', JSON.stringify(newPoint));
		lastPoint = newPoint;
	}
}, 500);

stdin.on("data", function(data) {
	data = data.toString().substring(0, data.length-1);
	console.log("you entered: [" + data + "]");
	if(data == 'exit'){
		clearInterval(pointUpdate);
		var serverClosed = server.exitCleanly();
		var trackClosed = track.exitCleanly();
		setTimeout(function() {
			if(serverClosed) console.log("\033[1;34m" + "Server closed successfully" + "\033[0m");
			else console.log("\033[1;31m" + "Server did not close properly" + "\033[0m");
			if(trackClosed) console.log("\033[1;34m" + "Track closed successfully" + "\033[0m");
			else console.log("\033[1;31m" + "Track did not close properly" + "\033[0m");
			process.exit();
		}, 1000);
	}
});