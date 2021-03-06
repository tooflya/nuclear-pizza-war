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

  cc.CyberHipposSplashScreen = cc.Screen.extend({
    init: function() {
      this._super();

      this.background = cc.Entity.create(s_CyberHippo, this, function(entity) {
        entity.setCenterPosition(CAMERA_CENTER_X, CAMERA_CENTER_Y);
        entity.setOpacity(0);
      });

      this.updateTime = 2.0;
      this.updateTimeElapsed = 0;
    },

    onEnter: function() {
      this._super();

      this.background.runAction(cc.FadeIn.create(1.0));
    },

    update: function(deltaTime) {
      this._super();

      this.updateTimeElapsed += deltaTime;

      if(this.updateTimeElapsed >= this.updateTime) {
        this.updateTimeElapsed = 0;

        director.replaceScene(cc.TransitionFade.create(2.0, cc.MojangSplashScreen.create()));
      }
    }
});

cc.CyberHipposSplashScreen.create = function() {
  if(cc.CyberHipposSplashScreen.instance) {
    return cc.CyberHipposSplashScreen.instance;
  } else {
  cc.CyberHipposSplashScreen.instance = new cc.CyberHipposSplashScreen();
  cc.CyberHipposSplashScreen.instance.init();

  return cc.CyberHipposSplashScreen.instance;
  }
};