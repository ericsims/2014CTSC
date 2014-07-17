require('js-yaml');
var settings = require('./config.yaml');
var server = require('./lib/server.js')(settings);
var track = require("./build/Release/obj.target/track.node");
console.log( track.locatePoint(function(msg) {
	server.sendupdate('serverStatus', msg);
}));