var track = require("./build/Release/obj.target/track.node");
console.log( track.locatePoint(function(msg) {
	console.log(msg); // 'hello world'
}) );