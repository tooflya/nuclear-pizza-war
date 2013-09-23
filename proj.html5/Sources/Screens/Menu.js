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

      this.backgroundStars = cc.EntityManager.create(100, cc.Star.create(), this);

      cc.Entity.create(s_GameManuBackground, this, function(entity) {
        entity.setCenterPosition(CAMERA_CENTER_X, CAMERA_CENTER_Y);
      });

      cc.Button.create(s_ButtonStart, this, function(entity) {
        entity.setCenterPosition(CAMERA_CENTER_X, CAMERA_CENTER_Y / 2);
      }, function(entity) {
        if(document.ccConfig.multiplayer) {
          TEMP = cc.Level.create();
          Connection.connect();
        } else {TEMP = cc.Level.create();}

        director.replaceScene(cc.TransitionFade.create(2.0, TEMP));
      });

      for(var i = 0; i < 100; i++) {
        this.backgroundStars.create();

        this.backgroundStars.last().setCenterPosition(randomf(0.0, CAMERA_WIDTH), randomf(0.0, CAMERA_HEIGHT));
      }
    },

    update: function(deltaTime) {
      this._super(deltaTime);
    },

    onEnter: function() {
      this._super();

      cc.AudioEngine.getInstance().playMusic(s_MainTheme, true);
    },
    onExit: function() {
      this._super();
    }
});

cc.Menu.create = function() {
  if(cc.Menu.instance) {
    return cc.Menu.instance;
  } else {
  cc.Menu.instance = new cc.Menu();
  cc.Menu.instance.init();

  return cc.Menu.instance;
  }
};