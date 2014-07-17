var express = require('express');
var app = express()
, server = require('http').createServer(app)
, io = require('socket.io').listen(server);
var settings;
module.exports = Server;

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