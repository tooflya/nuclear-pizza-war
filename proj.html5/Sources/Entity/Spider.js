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

cc.Spider = cc.AnimatedEntity.extend({
  init: function() {
    this._super(s_Spider, 4, 1);

    this.m_Shadow = cc.Entity.create(s_SmallShadow);
    this.m_Shockwave = cc.Entity.create(s_PersonageShockwave);
    this.m_Shockwave.setZOrder(20);

    this.m_VoiceTime = randomf(2.0, 10.0);
    this.m_VoiceTimeElapsed = 0;

    this.m_Speed = 30;
    this.m_Power = 50;

    this.m_VectorX = -1;
    this.m_VectorY = -1;

    this.animate(0.1);
  },

  onCreate: function() {
    this._super();

    if(!this.m_Shockwave._parent) {
      this._parent.addChild(this.m_Shockwave);
    }

    this.m_Shadow.setZOrder(19);
    this.setCenterPosition(0, 0);
  },
  onDestroy: function() {
    this._super();

    this.m_Shockwave.destroy();

    this._parent.m_Explosions[2].create();
    this._parent.m_Explosions[2].last().setCenterPosition(this.getCenterX(), this.getCenterY());

    cc.AudioEngine.getInstance().playEffect(s_SpiderDestroy);
  },

  move: function(deltaTime) {
    if(this.m_VectorX < 0 || (Math.abs(this.getCenterX() - this.m_VectorX) < 10 && Math.abs(this.getCenterY() - this.m_VectorY) < 10)) {
      var pos = pizzaPositionFromRad(randomf(0.0, 1.0) * Math.PI * 2.0, 0.25 + randomf(0.0, 1.0) * 0.6);
      
      this.m_VectorX = pos[0];
      this.m_VectorY = pos[1];
    }

    var vector = vectorNormalize(this.getCenterX() - this.m_VectorX, this.getCenterY() - this.m_VectorY, this.m_Speed * deltaTime);

    this.setCenterPosition(this.getCenterX() - vector[0], this.getCenterY() - vector[1]);
    this.m_Shadow.setCenterPosition(this.getCenterX(), this.getCenterY() - 5);
    this.m_Shockwave.setCenterPosition(this.getCenterX(), this.getCenterY());
  },

  update: function(deltaTime) {
    this._super(deltaTime);

    this.m_VoiceTimeElapsed += deltaTime;

    if(this.m_VoiceTimeElapsed >= this.m_VoiceTime) {
      this.m_VoiceTimeElapsed = 0;

        this.m_Shockwave.setScale(0);
        this.m_Shockwave.create();
        this.m_Shockwave.runAction(cc.ScaleTo.create(0.2, 1.0));

      cc.AudioEngine.getInstance().playEffect(s_SpiderVoice);
    }

    if(this.m_Shockwave.isVisible()) {
      if(this.m_VoiceTimeElapsed >= 0.2) {
        this.m_Shockwave.destroy();
      }
    }

    this.move(deltaTime);
  },

  onCollide: function(object, description) {
    this._super();

    switch(description) {
      case "enemy":
        this.destroy();
      break;
    }
  },

  deepCopy: function() {
    return cc.Spider.create();
  }
});

cc.Spider.create = function() {
  var entity = new cc.Spider();
  entity.init();

  return entity;
};