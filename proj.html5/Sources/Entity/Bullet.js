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

cc.Bullet = cc.TiledEntity.extend({
  init: function() {
    this._super(s_Bullets, 3, 2);

    this.m_Shadow = cc.TiledEntity.create(s_Bullets, 3, 2);

    this.m_Speed = 500;
    this.m_Power = 20;
  },

  onCreate: function() {
    this._super();
  },
  onDestroy: function() {
    this._super();

    this._parent._parent.m_BulletsCrashes.create();
    this._parent._parent.m_BulletsCrashes.last().setCenterPosition(this.getCenterX(), this.getCenterY());

    cc.AudioEngine.getInstance().playEffect(s_PersonageShootLand);
  },

  setCoordinates: function(x, y, mx, my) {
    this.m_VectorX = x;
    this.m_VectorY = -y;

    this.m_MouseX = mx;
    this.m_MouseY = my;
  },
  setCurrentFrameIndex: function(index) {
    this._super(index);

    if(this.m_Shadow) {
      this.m_Shadow.setCurrentFrameIndex(index);
    }
  },

  onCollide: function(object, description) {
    this.destroy();
  },

  update: function(deltaTime) {
    this._super(deltaTime);

    var vector = vectorNormalize(this.m_VectorX, this.m_VectorY, this.m_Speed * deltaTime);

    this.setCenterPosition(this.getCenterX() + vector[0], this.getCenterY() + vector[1]);

    var angle = Math.atan2(this.m_VectorX, this.m_VectorY) * 180 / Math.PI;

    this.setRotation(angle);
    this.m_Shadow.setRotation(angle);
 
    var padding = this.m_VectorX / Math.sqrt(this.m_VectorX * this.m_VectorX + this.m_VectorY * this.m_VectorY) * 20;

    this.m_Shadow.setCenterPosition(this.getCenterX(), this.getCenterY() - Math.abs(padding)/* - this.mFakeZ*/);

    if(vector[1] > 0) {
      if(this.getCenterY() > this.m_MouseY) {
        this.destroy();
      }
    } else {
      if(this.getCenterY() < this.m_MouseY) {
        this.destroy();
      }
    }
  },

  deepCopy: function() {
    return cc.Bullet.create();
  }
});

cc.BulletCrash = cc.AnimatedEntity.extend({
  init: function() {
    this._super(s_BulletsCrash, 8, 1);
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
    return cc.BulletCrash.create();
  }
});

cc.Bullet.create = function() {
  var entity = new cc.Bullet();
  entity.init();

  return entity;
};

cc.BulletCrash.create = function() {
  var entity = new cc.BulletCrash();
  entity.init();

  return entity;
};