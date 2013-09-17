/**
 * Tooflya Inc. Development
 *
 * @author Igor Mats from Tooflya Inc.
 * @copyright (c) 2013 by Igor Mats
 *
 * @license http://opensource.org/licenses/gpl-license.php GNU Public License v2
 * @all rights granted under this License are granted for the term of
 * copyright on the Program, and are irrevocable provided the stated
 * conditions are met. This License explicitly affirms your unlimited
 * permission to run the unmodified Program. The output from running a
 * covered work is covered by this License only if the output, given its
 * content, constitutes a covered work. This License acknowledges your
 * rights of fair use or other equivalent, as provided by copyright law.
 *
 * @version
 *
 */

Array.prototype.swap = function(x, y) {
  var b = this[x];
  this[x] = this[y];
  this[y] = b;

  return this;
}

String.prototype.format = function() {
  var args = arguments;
  return this.replace(/{(\d+)}/g, function(match, number) { 
    return typeof args[number] != 'undefined'
      ? args[number]
      : match;
  });
};

cc.Node.prototype.getTotalChildrenCount = function(visible) {
  var count = 0;

  for(var i = 0; i < this.getChildrenCount(); i++) {
    var child = this.getChildren()[i];

    if(child.isVisible() || !visible) {
      count++;

      count += child.getTotalChildrenCount(visible);
    }
  }

  return count;
}

vectorNormalize = function(px, py, factor) {
  var x = px / Math.sqrt(px * px + py * py) * factor;
  var y = py / Math.sqrt(px * px + py * py) * factor;

  return [x, y];
}

getSafePizzaPosition = function() {
  var angle = randomf(0.0, 1.0) * Math.PI * 2.0;
  var distance = (0.3 + randomf(0.0, 1.0) * 0.7) * 1600.0 * 0.40 * 0.95;

  var x = CAMERA_CENTER_X + Math.cos(angle) * distance;
  var y = CAMERA_CENTER_Y + Math.sin(angle) * distance * 0.5;

  return [x, y];
}

isOnPizza = function(entity) {
  var cx = CAMERA_CENTER_X + 25;
  var cy = CAMERA_CENTER_Y + 25;
  var pizzaRadiusX = 775.2;
  var pizzaRadiusY = 418.2;
  
  var dx = (entity.getCenterX() - cx);
  var dy = (entity.getCenterY() - cy) * pizzaRadiusX / pizzaRadiusY;

  return ((dx * dx) + (dy * dy)) <= pizzaRadiusX * pizzaRadiusX;
}

obstacle = function(entity, px, py, magnet, radius)
{
  if(entity.circlesCollideCoordinatesWith(entity.getCenterX(), entity.getCenterY() - entity.getHeight() / 2, px, py, magnet) && entity.getZ() <= MIN_Z)
  {
    radius = Math.max(entity.getWidth(), entity.getHeight()) + radius;

    var dx = (px - entity.getCenterX()) * 2.5;
    var dy = (py - entity.getCenterY() + entity.getHeight() / 2) * 2.5;
    {
      var dist = Math.sqrt(dx * dx + dy * dy);

      dx = px - (dx / dist) * radius * 0.4;
      dy = py - (dy / dist) * radius * 0.4;
    }

    entity.setCenterPosition(dx, dy + entity.getHeight() / 2);
  }
}

pizzaPositionFromRad = function(rad, distanceFromCenterPercentage) {
  var pizzaRadiusX = 1560 / 2;
  var pizzaRadiusY = 840 / 2;
  var x = Math.sin(rad) * distanceFromCenterPercentage;
  var y = Math.cos(rad) * distanceFromCenterPercentage;

  return [x * pizzaRadiusX + 800 / 2 + 10, y * pizzaRadiusY + CAMERA_CENTER_Y];
}