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

  cc.Screen = cc.Scene.extend({
    init: function() {
      this._super();

      this.touched = false;
    },

    onEnter: function() {
      this._super();

      this.scheduleUpdate();

      director.getTouchDispatcher()._addTargetedDelegate(this, 0, false);
    },
    onExit: function() {
      this._super();

      this.unscheduleUpdate();

      director.getTouchDispatcher()._removeDelegate(this);
    },

    containsTouchLocation: function(touch) {
      return true;
    },

    onTouchBegan: function(touch, event) {
      this.touched = this.containsTouchLocation(touch);

      return this.touched;
    },
    onTouchMoved: function(touch, event) {
    },
    onTouchEnded: function(touch, event) {
      if(this.touched) {
        this.onTouch();
      }
    },

    onTouch: function() {

    }
});

cc.Screen.create = function() {
  var screen = new cc.Screen();
  screen.init();

  return screen;
};