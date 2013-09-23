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

cc.BaseEnemy = cc.AnimatedEntity.extend({
  onCreate: function() {
    this._super();

    this.m_VectorX = 0;
    this.m_VectorY = 0;

    this.m_VoiceTime = randomf(2.0, 15.0);
    this.m_VoiceTimeElapsed = 0;

    this.m_FireTime = 1.0;
    this.m_FireTimeElapsed = 0;

    this.m_FirePower = 0;
    this.m_FireCount = 0;

    this.m_ShootPadding = 0;

    this.animate(0.1);
    this.setCollideable(true);
    this.setIgnoreSorting(false);
    this.setColor(new cc.Color3B(255, 255, 255));
    this.setScale(0);
    this.runAction(cc.ScaleTo.create(0.2, 1));
  },
  onDestroy: function() {
    this._super();
    
    this._parent.getParent().m_EnemiesCount--;

    this._parent.shake(0.5, 3.0);

    if(this.getParent()) {
      if(probably(10)) {
        this.getParent().m_Pickups.create();
        this.getParent().m_Pickups.last().setCenterPosition(this.getCenterX(), this.getCenterY());
      }
    }
  },

  onCollide: function(object, description) {
    this._super();

    switch(description) {
      case "bullet":
        this.m_VectorX = object.m_VectorX;
        this.m_VectorY = object.m_VectorY;

        this.m_ShootPadding = 20;
        this.m_ShootPaddingSpeed = 100;

        this.m_Health -= object.m_Power;
      break;
      case "shockwave":
        this.m_VectorX = this.getCenterX() - object.getCenterX();
        this.m_VectorY = this.getCenterY() - object.getCenterY();

        this.m_ShootPadding = 50;
        this.m_ShootPaddingSpeed = 200;

        this.m_Health -= object.m_Power;
      break
      case "spider":
        this.m_Health -= object.m_Power;
      break;
    }
  },

  setFireTime: function(value) {
    this.m_FireTime = value;
  },
  setFirePower: function(value) {
    this.m_FirePower = value;
  },
  setFireCount: function(value) {
    this.m_FireCount = value;
  },

  update: function(deltaTime) {
    this._super(deltaTime);

    if(this.m_ShootPadding > 0) {
      var vector = vectorNormalize(this.m_VectorX, this.m_VectorY, this.m_ShootPaddingSpeed * deltaTime);

      this.setCenterPosition(this.getCenterX() + vector[0], this.getCenterY() + vector[1]);

      this.m_ShootPadding -= this.m_ShootPaddingSpeed * deltaTime;
    } else {
      this.move(deltaTime);
    }

    this.m_Shadow.setCenterPosition(this.getCenterX(), this.getCenterY() - 15);

    this.m_VoiceTimeElapsed += deltaTime;

    if(this.m_VoiceTimeElapsed >= this.m_VoiceTime) {
      this.m_VoiceTimeElapsed = 0;

      cc.AudioEngine.getInstance().playEffect(s_EnemyVoice);
    }
  }
});