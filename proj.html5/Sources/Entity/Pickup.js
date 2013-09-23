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

cc.Pickup = cc.TiledEntity.extend({
  init: function() {
    this._super(s_Pickups, 1, 3);

    this.m_Shadow = cc.Entity.create(s_Shadow);

    this.m_AnimationTime = 2;
    this.m_AnimationTimeElapsed = 0;

    this.m_Speed = 25;

    this.m_AnimationReverse = false;

    this.setIgnoreSorting(false);
  },

  onCreate: function() {
    this._super();

    this.setScale(0);
    this.runAction(cc.ScaleTo.create(0.2, 1));

    this.setCurrentFrameIndex(random(0, 3));
  },
  onDestroy: function() {
    this._super();

    cc.AudioEngine.getInstance().playEffect(s_PickupPop);
  },

  onCollide: function(object, description) {
    cc.Level.instance.m_Wealth[this.getCurrentFrameIndex()]++;
    cc.Level.instance.m_StaticLayer.m_WealthManager.update();

    this.destroy();
  },

  follow: function(x, y, deltaTime) {
    var vector = vectorNormalize(this.getCenterX() - x, this.getCenterY() - y, this.m_Speed * deltaTime);

    this.setCenterPosition(this.getCenterX() - vector[0], this.getCenterY() - vector[1]);
  },

  update: function(deltaTime) {
    this._super(deltaTime);

    this.m_AnimationTimeElapsed += deltaTime;

    if(this.m_AnimationTimeElapsed >= this.m_AnimationTime) {
      this.m_AnimationTimeElapsed = 0;

      this.m_AnimationReverse = !this.m_AnimationReverse;
    }

    if(this.m_AnimationReverse) {
      this.removeZ(10 * deltaTime);
    } else {
      this.addZ(10 * deltaTime);
    }

    this.m_Shadow.setCenterPosition(this.getCenterX(), this.getCenterY() - 10 - this.getZ());
  },

  deepCopy: function() {
    return cc.Pickup.create();
  }
});

cc.Pickup.create = function() {
  var entity = new cc.Pickup();
  entity.init();

  return entity;
};