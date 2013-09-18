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

cc.CastleEnemy = cc.BaseEnemy.extend({
  init: function() {
    this._super(s_CastleEnemy, 8, 1);

    this.m_Shadow = cc.Entity.create(s_Shadow);
    this.m_Shockwave = cc.Entity.create(s_EnemyShockwave);
    this.m_Shockwave.setZOrder(20);
    this.m_Shockwave.m_Power = 1;

    this.m_Speed = 50;
    this.m_Power = 1;
  },

  onCreate: function() {
    this._super();

    if(!this.m_Shockwave._parent) {
      this._parent.addChild(this.m_Shockwave);
    }
  },
  onDestroy: function() {
    this._super();

    this.m_Shockwave.destroy();

    this._parent.m_Explosions[1].create();
    this._parent.m_Explosions[1].last().setCenterPosition(this.getCenterX(), this.getCenterY() + 60);

    cc.AudioEngine.getInstance().playEffect(s_EnemySuicide);
  },

  move: function(deltaTime) {
    var vectorX = this.getCenterX() - CAMERA_CENTER_X;
    var vectorY = this.getCenterY() - CAMERA_CENTER_Y;

    var vector = vectorNormalize(vectorX, vectorY, this.m_Speed * deltaTime);

    var x = this.getCenterX() - vector[0];
    var y = this.getCenterY() - vector[1];

    this.setCenterPosition(x, y);
    this.m_Shockwave.setCenterPosition(x, y - 15);
  },

  update: function(deltaTime) {
    this._super(deltaTime);

    this.m_FireTimeElapsed += deltaTime;

    var magnet;
    var radius;

    switch(FORTIFICATION_LEVEL)
    {
      case 0:
        magnet = 50.0;
        radius = 135.0;
      break;
      case 1:
        magnet = 60.0;
        radius = 160.0;
      break;
      case 2:
        magnet = 70.0;
        radius = 185.0;
      break;
      case 3:
        magnet = 80.0;
        radius = 210.0;
      break;
    }

    if(obstacle(this, CAMERA_CENTER_X, CAMERA_CENTER_Y, magnet, radius)) {
      if(this.m_FireTimeElapsed >= this.m_FireTime) {
        this.m_FireTimeElapsed = 0;

        this.m_Shockwave.setScale(0);
        this.m_Shockwave.create();
        this.m_Shockwave.runAction(cc.ScaleTo.create(0.2, 1.5));

        this.m_Health -= 10;

        this._parent.m_Castle.onCollide(this, "enemy");

        cc.AudioEngine.getInstance().playEffect(s_EnemyWarning);
      }
    }

    if(this.m_Shockwave.isVisible()) {
      if(this.m_FireTimeElapsed >= 0.2) {
        this.m_Shockwave.destroy();
      }
    }
  },

  deepCopy: function() {
    return cc.CastleEnemy.create();
  }
});

cc.CastleEnemy.create = function() {
  var entity = new cc.CastleEnemy();
  entity.init();

  return entity;
};