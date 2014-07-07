var fs = require('fs');
var FFmpeg = require('fluent-ffmpeg');
var child_process = require('child_process');

var input_file = fs.createReadStream('in.avi');
input_file.on('error', function(err) {
	console.log(err);
});

var output_path = 'out.mp4';
var output_stream = fs.createWriteStream('out.mp4');

var ffmpeg = child_process.spawn('ffmpeg', ['-i', 'pipe:0', '-f', 'mp4', '-movflags', 'frag_keyframe', 'pipe:1']);
input_file.pipe(ffmpeg.stdin);
ffmpeg.stdout.pipe(output_stream);

ffmpeg.stderr.on('data', function (data) {
	console.log(data.toString());
});

ffmpeg.stderr.on('end', function () {
	console.log('file has been converted succesfully');
});

ffmpeg.stderr.on('exit', function () {
	console.log('child process exited');
});

ffmpeg.stderr.on('close', function() {
	console.log('...closing time! bye');
});