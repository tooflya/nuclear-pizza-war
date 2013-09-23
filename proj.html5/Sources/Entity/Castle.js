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

  cc.Castle = cc.AnimatedEntity.extend({
    init: function(parent, callback) {
      this._super(s_Castle, 8, 1, parent, callback);

      FORTIFICATION_LEVEL = 2;

      this.m_FortnessHealth = [];
      this.m_Wall = [];

      this.m_FireTime = 1;
      this.m_FireTimeElapsed = 0;

      this.m_FortnessHealth[0] = 10;
      this.m_FortnessHealth[1] = 10;
      this.m_FortnessHealth[2] = 10;

      this.m_Wall[0] = cc.Entity.create(s_Wall1, this);
      this.m_Wall[1] = cc.Entity.create(s_Wall2, this);
      this.m_Wall[2] = cc.Entity.create(s_Wall3, this);

      this.m_Wall[0].create();
      this.m_Wall[1].create();

      this.m_Wall[0].setCenterPosition(this.getWidth() / 2 - 4, this.getHeight() / 2 - 30);
      this.m_Wall[1].setCenterPosition(this.getWidth() / 2 - 4, this.getHeight() / 2 - 30);
      this.m_Wall[2].setCenterPosition(this.getWidth() / 2 - 4, this.getHeight() / 2 - 30);

      this.animate(0.1);

      this.setMaxHealth(50);
    },

    onCreate: function() {
      this._super();
    },
    onDestroy: function() {
      this._super();

      director.pushScene(cc.TransitionFade.create(3.0, cc.GameOver.create()));
    },

    onCollide: function(object, description) {
      this.removeHealth(object.m_Power);
    },

    fire: function() {
      var target = false;

      for(var i = 0; i < 4; i++) {
        for(var j = 0; j < this._parent.m_Enemies[i].getCount(); j++) {
          var enemy = this._parent.m_Enemies[i].get(j);

          if(true) {
            target = enemy;
          }
        }
      }

      if(target) {
        this._parent.m_Bullets.create();

        var x = this.getCenterX() - target.getCenterX();
        var y = this.getCenterY() + 50 - target.getCenterY();

        this._parent.m_Bullets.last().setCurrentFrameIndex(0);
        this._parent.m_Bullets.last().setCoordinates(-x, y, target.getCenterX(), target.getCenterY());
        this._parent.m_Bullets.last().setCenterPosition(this.getCenterX(), this.getCenterY() + 50);
        this._parent.m_Bullets.last().m_Power = 10;
        this._parent.m_Bullets.last().m_Speed = 600;
        this._parent.m_Bullets.last().by = "castle";

        cc.AudioEngine.getInstance().playEffect(s_PersonageShoot[0]);
      }
    },

    update: function(deltaTime) {
      this._super(deltaTime);

      if(this.m_FireTime > 0) {
        this.m_FireTimeElapsed += deltaTime;

        if(this.m_FireTimeElapsed >= this.m_FireTime) {
          this.m_FireTimeElapsed = 0;

          this.fire();
        }
      }
    },

    removeHealth: function(value) {
      if(FORTIFICATION_LEVEL <= 0) {
        this.m_Health -= value;
      } else {
        this.m_FortnessHealth[FORTIFICATION_LEVEL - 1] -= value;
        if(this.m_FortnessHealth[FORTIFICATION_LEVEL - 1] <= 0) {
          this.m_Wall[FORTIFICATION_LEVEL - 1].destroy();

          FORTIFICATION_LEVEL--;
        }
      }
    },

  upgrade: function(index, level) {
    switch(index) {
      case 8:
        switch(level) {
          case 1:
          break;
          case 2:
          break;
          case 3:
          break;
        }
      break;
      case 9:
        switch(level) {
          case 1:
            this.m_FireTime = 2;
          break;
          case 2:
            this.m_FireTime = 1.5;
          break;
          case 3:
            this.m_FireTime = 1.0;
          break;
          case 4:
            this.m_FireTime = 0.7;
          break;
          case 5:
            this.m_FireTime = 0.4;
          break;
        }
      break;
      case 10:
        switch(level) {
          case 1:
          break;
          case 2:
          break;
          case 3:
          break;
        }
      break;
    }
  }
});

cc.Castle.create = function(parent, callback) {
  var entity = new cc.Castle();
  entity.init(parent, callback);

  return entity;
};