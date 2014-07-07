var cv = require('opencv');
var PNG = require('png.js');
var draw = require('./draw');
var http = require('http');

exports.cvstream = new cv.ImageDataStream();

exports.cvstream.on('load', function(matrix){
	var object = detection.readImage(matrix, settings, target, true);
	if(object.cordinates && follow){
		if(settings.debug) console.log(XYZ);
		cvstream.emit('found', object.cordinates);
	} else {
		console.log('stop');
		client.stop();
	}
	cvstream.emit('image', object.image);
});

exports.readImage = function readImage(data, settings, index, adjustWhiteBalance){
	if(target = settings['target'+index]){
		var reader = new PNG(data);
		reader.parse(function(err, png){
			if (err) throw err;
			cv.readImage(data, function(err, im){
				return exports.cvProcess(err, im, settings, target, adjustWhiteBalance);
			});
		});
	} else
		return false;
};


exports.cvProcess = function cvProcess(err, im_orig, settings, target, whitebalance) {
	var big = im_orig.copy();
	var im = im_orig.copy();
	if(settings.opencv.saveFiles){
		im.save('./stills/matrix.png');
		if(settings.debug) console.log('matrix.png saved');
	}
	var colors = undefined;
	if(whiteBalanceAdjust)
		colors = adjustColors(target, calculateWhiteBalance(png, settings, target));
	else
		colors = adjustColors(target);
		
	im.inRange(colors.upper, colors.lower);

	if(settings.opencv.saveFiles){
		im.save('./stills/color.png');
		if(settings.debug) console.log('color.png saved');
	}
	im.canny(settings.opencv.lowThresh, settings.opencv.highThresh);
	im.dilate(target.nIters);
	if(settings.opencv.saveFiles){
		im.save('./stills/canny.png');
		if(settings.debug) console.log('canny.png saved');
	}

	var contours = im.findContours();
	if(settings.debug){
		console.log('found contours: ' + contours.size());
		console.log('settings.targetx.minArea: ' + target.minArea);
	}
	var largest_blob = false;
	var current = false;
	if (contours.size() > 0) {
		for(var i = 0; i < contours.size(); i++) {
			var area = contours.area(i);
			current = contours.boundingRect(i);
			if((area > target.minArea && area < target.maxArea && area > contours.area(largest_blob) 
					&& !(current.x == 1 || current.x == settings.opencv.width || current.y == 1 || current.y == settings.opencv.height)) 
					|| !largestblob)
				largest_blob=i;
		}

		if(settings.debug) console.log('largest_blob: ' + largest_blob);

		big.drawAllContours(contours, settings.WHITE);
	}
	if(largest_blob) {
		var center = getCenter(current.x, current.y, current.width, current.height, settings);
		if(settings.debug) console.log('center: ' + center);

		big.drawContour(contours, largest_blob, settings.BLUE);
		draw.drawBoundingRect(big, current, settings.RED);
		draw.drawCenter(big, current, settings.RED, getCenter);

		if(settings.opencv.saveFiles){
			big.save('./stills/big.png');
			if(settings.debug) console.log('big.png saved');
		}
		return new Object(cordinates[center[0], center[1]],image[big.toBuffer()]);
	} else {
		if (settings.debug)
			console.log('no target found');
		return undefined;
	}

};

function calculateWhiteBalance(png, settings, target){
	var whiteBalance = 0;
	if(settings.debug){
		console.log('png.width: ' + png. width);
		console.log('png.height: ' + png. height);
	}

	var usageFrequency = 10;
	var totalPixels = (png.width * png.height) / (usageFrequency * usageFrequency);

	for (var x = 0; x <= png.width - usageFrequency; x += usageFrequency){
		for (var y = 0; y <= png.height - usageFrequency; y += usageFrequency){
			var average = (png.getPixel(x,y)[0] + png.getPixel(x,y)[1] + png.getPixel(x,y)[2]) / 3;
			whiteBalance += average;
		}
	}

	whiteBalance = whiteBalance / totalPixels;

	if(settings.debug){
		console.log('whiteBalance: ' + whiteBalance);
		console.log('target.color: ' + target.color);
		console.log('settings.targetx.threshold: ' + target.threshold);
		console.log('whiteBalanceAdjust: ' + whiteBalanceAdjust);
	}

	return whiteBalance / target.whiteBalance;
};

function adjustColors(target, whitebalance) {
	if(!whitebalance) whitebalace = 1;
	var lowerThresh = [(target.color[0] * whiteBalanceAdjust) - target.threshold * target.color[0],
	                   (target.color[1] * whiteBalanceAdjust) - target.threshold * target.color[1],
	                   (target.color[2] * whiteBalanceAdjust) - target.threshold * target.color[2]];
	var upperThresh = [(target.color[0] * whiteBalanceAdjust) + target.threshold * target.color[0],
	                   (target.color[1] * whiteBalanceAdjust) + target.threshold * target.color[1],
	                   (target.color[2] * whiteBalanceAdjust) + target.threshold * target.color[2]];
	return new Object([lower[lowerThresh],upper[upperThresh]]);
};

function getCenter(x, y, width, height, settings) {
	var center_x = x + width/2;
	var center_y = y + height/2;
	return [center_x, center_y];
};