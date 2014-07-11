var track = require("./build/Release/obj.target/track.node");
console.log( track.locatePoint() );
setTimeout(function() {
	process.exit(0);
}, 10000);