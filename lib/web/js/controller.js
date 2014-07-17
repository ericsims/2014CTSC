window.onload = function(){

};

var socket = io.connect(location.host);
function run() {
    socket.emit('controlState', 'initiate');
}
function stop() {
    socket.emit('controlState', 'stop');
	document.getElementById('time').value = "";
}

function clearStatus() {
    document.getElementById('status').value = "";
}

function displayStatus(data){
	document.getElementById('status').value = document.getElementById('status').value + data + '\n';
	document.getElementById('status').scrollTop = document.getElementById('status').scrollHeight;
}