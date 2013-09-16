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

  cc.Menu = cc.Screen.extend({
    init: function() {
      this._super();

      this.backgroundStars = cc.EntityManager.create(1000, cc.Star.create(), this);

      cc.Entity.create(s_GameManuBackground, this, function(entity) {
        entity.setCenterPosition(CAMERA_CENTER_X, CAMERA_CENTER_Y);
      });

      cc.Button.create(s_ButtonStart, this, function(entity) {
        entity.setCenterPosition(CAMERA_CENTER_X, CAMERA_CENTER_Y / 2);
      }, function(entity) {
        director.replaceScene(cc.TransitionFade.create(2.0, cc.Level.create()));
      });

      for(var i = 0; i < 1000; i++) {
        this.backgroundStars.create();

        this.backgroundStars.last().setCenterPosition(randomf(0.0, CAMERA_WIDTH), randomf(0.0, CAMERA_HEIGHT));
      }
    },

    update: function(deltaTime) {
      this._super(deltaTime);
    }
});

cc.Menu.create = function() {
  var screen = new cc.Menu();
  screen.init();

  return screen;
};