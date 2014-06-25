exports.drawBoundingRect = function(im, boundingRect, color) {
	var firstCorner =  [boundingRect.x, boundingRect.y];
	var secondCorner = [boundingRect.x + boundingRect.width, boundingRect.y];
	var thirdCorner =  [boundingRect.x, boundingRect.y + boundingRect.height];
	var fourthCorner = [boundingRect.x + boundingRect.width, boundingRect.y + boundingRect.height];

	im.line(firstCorner, secondCorner, color);
	im.line(secondCorner, fourthCorner, color);
	im.line(fourthCorner, thirdCorner, color);
	im.line(thirdCorner, firstCorner, color);
};

exports.drawCenter = function(im, boundingRect, color, getCenter) {
	var center = getCenter(
		boundingRect.x,
		boundingRect.y,
		boundingRect.width,
		boundingRect.height
	);
    im.ellipse(center.x, center.y, center.width/2, center.height/2, color);
};

