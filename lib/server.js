var express = require('express');
var app = express()
, server = require('http').createServer(app)
, io = require('socket.io').listen(server);
var settings;
module.exports = Server;

var currentFrame;
var stop = false;

Server.prototype.hi = function hi() {
	console.log('asdfasdf');
};

function Server(newSettings){
	settings = newSettings;
	server.listen(settings.server.port);
};


app.use(express.static('./lib/web/'));
app.get('/', function (req, res) {
	res.sendfile('./lib/web/index.html');
});


io.sockets.on('connection', function (socket) {
	socket.emit('serverStatus', 'connected');
	console.log('connected: ' + JSON.stringify(socket.handshake.address));
	socket.on('controlState', function (data) {
	});
});

Server.prototype.sendUpdate = function sendUpdate(name, data) {
	io.sockets.emit(name, data);
};

app.get('/img', function(request, response) {
	response.send('AR.Drone Image Processing:\
			<br/>\
			<img src=im.mjpeg width=100% heigth=100%>\
			<br/>\
			<a href=im.mjpeg>im.mjepg</a>');
	stop = false;
});

app.get('/im.mjpeg', function(request, res) {
	res.writeHead(200, {
		'Content-Type': 'multipart/x-mixed-replace; boundary=myboundary',
		'Cache-Control': 'no-cache',
		'Connection': 'close',
		'Pragma': 'no-cache'
	});


	res.connection.on('close', function() {
		stop = true;
	});

	var send_next = function() {
		if (stop || !content)
			return;
		res.write("--myboundary\r\n");
		res.write("Content-Type: image/jpeg\r\n");
		res.write("Content-Length: " + content.length + "\r\n");
		res.write("\r\n");
		res.write(content, 'binary');
		res.write("\r\n");
		setTimeout(send_next(), 100);
	};
	send_next();
});

exports.update = function update(img){
	if(!content)
		console.log("Image server running");
	content = img;
};