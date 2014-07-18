require('js-yaml');
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
setInterval(function() {
	var newPoint = track.getDataPoint();
	if(lastPoint != newPoint) {
		server.sendUpdate('point', JSON.stringify(newPoint));
		lastPoint = newPoint;
	}
}, 500);