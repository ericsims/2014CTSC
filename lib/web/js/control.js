var socket = io.connect('192.168.1.4');
socket.on('serverStatus', function (data) {
	console.log(data);
	displayStatus(data);
});

function clearStatus() {
    document.getElementById('status').value = "";
}

function displayStatus(data){
	document.getElementById('status').value = document.getElementById('status').value + data + '\n';
	document.getElementById('status').scrollTop = document.getElementById('status').scrollHeight;
}
