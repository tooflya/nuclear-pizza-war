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

  cc.Button = cc.Entity.extend({
    init: function(fileName, parent, callback, button_callback) {
      this._super(fileName, parent, callback);

      this.callback = button_callback;

      this.touched = false;
    },

    onEnter: function() {
      this._super();

      director.getTouchDispatcher()._addTargetedDelegate(this, 0, false);
    },
    onExit: function() {
      this._super();

      director.getTouchDispatcher()._removeDelegate(this);
    },

    containsTouchLocation: function(touch) {
      return cc.rectContainsPoint(cc.RectMake(this.getWorldCenterX() - this.getWidth() / 2, this.getWorldCenterY() - this.getHeight() / 2, this.getWidth(), this.getHeight()), touch.getLocation()) && this.isVisible() && this.getOpacity() >= 255;
    },

    onTouchBegan: function(touch, event) {
      if(this.containsTouchLocation(touch)) {
        this.stopAllActions();
        this.runAction(cc.ScaleTo.create(0.3, 0.9));

        this.touched = true;

        return true;
      }

      return false;
    },
    onTouchMoved: function(touch, event) {
      if(!this.containsTouchLocation(touch) && this.touched) {
        this.touched = false;

        this.stopAllActions();
        this.runAction(cc.ScaleTo.create(0.1, 1.0));
      }
    },
    onTouchEnded: function(touch, event) {
      if(this.containsTouchLocation(touch) && this.touched) {
        this.touched = false;

        this.stopAllActions();
        this.runAction(cc.ScaleTo.create(0.1, 1.0));

        this.callback(this);
      }
    }
});

cc.Button.create = function(fileName, parent, callback, button_callback) {
  var entity = new cc.Button();
  entity.init(fileName, parent, callback, button_callback);

  return entity;
};