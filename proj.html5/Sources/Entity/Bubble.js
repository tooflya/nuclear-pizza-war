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

cc.Bubble = cc.AnimatedEntity.extend({
  init: function() {
    this._super(s_Bubble, 9, 1);

    this.m_Splash = cc.BubbleSplash.create();
  },

  onCreate: function() {
    this._super();

    this.m_HealthFull = 120;
    this.m_Health = this.m_HealthFull;

    this.animate(0.1, 1);
  },
  onDestroy: function() {
    this._super();

    if(this.m_Splash) {
      if(!this.m_Splash.getParent()) {
        this.getParent().addChild(this.m_Splash, this.getZOrder());
      }
      this.m_Splash.create();
      this.m_Splash.setCenterPosition(this.getCenterX(), this.getCenterY());
    }

    if(this.getParent()) {
      if(probably(90)) {
        this.getParent().m_Pickups.create();
        this.getParent().m_Pickups.last().setCenterPosition(this.getCenterX(), this.getCenterY());
      }
    }

    cc.AudioEngine.getInstance().playEffect(s_BubblePop);
  },

  onCollide: function(object, description) {
    this.m_Health -= object.m_Power;
  },

  update: function(deltaTime) {
    this._super(deltaTime);
  },

  deepCopy: function() {
    return cc.Bubble.create();
  }
});

cc.BubbleSplash = cc.AnimatedEntity.extend({
  init: function() {
    this._super(s_BubbleSplash, 11, 1);
  },

  onCreate: function() {
    this._super();

    this.animate(0.1, 1);
  },
  onDestroy: function() {
    this._super();
  },

  onAnimationEnd: function() {
    this._super();

    this.destroy();
  },

  update: function(deltaTime) {
    this._super(deltaTime);
  },

  deepCopy: function() {
    return cc.BubbleSplash.create();
  }
});

cc.Bubble.create = function() {
  var entity = new cc.Bubble();
  entity.init();

  return entity;
};

cc.BubbleSplash.create = function() {
  var entity = new cc.BubbleSplash();
  entity.init();

  return entity;
};