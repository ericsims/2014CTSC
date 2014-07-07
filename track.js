require('js-yaml');

var fs = require('fs');
var sys = require("sys");
var exec = require('child_process').exec;


var settings = require('./track/config/settings.yaml');
var detection = require('./track/components/detection');
var actions = require('./track/components/actions');
var server = require('./track/components/mjpeg-stream');

var stdin = process.openStdin();
var target = -1;
var follow = false;

process.argv.forEach(function (val, index, array) {
	if( index == 2 ) target = val;
});

if(target < 0) throw new Error('Please set a target number!');


.pipe(detection.cvstream);

detection.cvstream.on('image', function(data){
	server.update(data);
});

detection.cvstream.on('found', function(cordinates){
	console.log(cordinates);
});

stdin.addListener("data", function(data) {
	data = data.toString().substring(0, data.length-1);
	console.log("you entered: [" + data + "]");
	if(data == 'takeoff'){
		takeoff();
	} else if(data == 'land'){
		land();
	} else if(data == 'calibrate'){
		actions.calibrate(client);
	} else if(data == 'hover'){
		actions.hover(client);
	} else if (data.indexOf('set streamSource') != -1) {
		streamSource = data.substring(17);
		console.log('steamSource is now: ' + streamSource);
	} else if (data.indexOf('set target') != -1) {
		target = parseInt(data.substring(10));
		console.log('target is now: ' + target);
	} else if (data == 'start track') {
		if (target > -1){
			follow = true;
			console.log('tracking started');
		} else 
			console.log('target not defined!');
	} else if (data == 'stop track') {
		follow = false;
		console.log('tracking stopped');
	} else if (data == 'exit') {
		process.exit();
	}
});

function takeoff(){
	client.takeoff();
};

function land(){
	client.stop();
	client.land();
};