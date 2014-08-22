var socket = io.connect('192.168.1.3');
socket.on('serverStatus', function (data) {
	console.log(data);
	displayStatus(data);
});

socket.on('point', function (data) {
	data = JSON.parse(data);
	var c = document.getElementById("canvas");
	c.setAttribute('width', window.innerWidth);
	c.setAttribute('height', window.innerHeight);
	var context = c.getContext("2d");
	context.beginPath();
	context.arc(data.x, data.y, 10, 0, 2 * Math.PI, false);
	context.fillStyle = 'gray';
	context.fill();
	context.lineWidth = 2;
	context.strokeStyle = 'black';//'#003300';
	context.stroke();
	console.log(data);
});

function clearStatus() {
    document.getElementById('status').value = "";
}

function displayStatus(data){
	document.getElementById('status').value = document.getElementById('status').value + data + '\n';
	document.getElementById('status').scrollTop = document.getElementById('status').scrollHeight;
}


