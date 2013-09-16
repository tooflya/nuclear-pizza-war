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

cc.BigEnemy = cc.BaseEnemy.extend({
  init: function() {
    this._super(s_BigEnemy, 4, 1);

    this.m_Shadow = cc.Entity.create(s_LargeShadow);

    this.m_Speed = 50;

    this.m_VectorX = -1;
    this.m_VectorY = -1;
  },

  onCreate: function() {
    this._super();
  },
  onDestroy: function() {
    this._super();
  },

  move: function(deltaTime) {
    if(this.m_VectorX < 0 || (Math.abs(this.getCenterX() - this.m_VectorX) < 10 && Math.abs(this.getCenterY() - this.m_VectorY) < 10)) {
      var pos = pizzaPositionFromRad(randomf(0.0, 1.0) * Math.PI * 2.0, 0.25 + randomf(0.0, 1.0) * 0.6);
      
      this.m_VectorX = pos[0];
      this.m_VectorY = pos[1];
    }

    var vector = vectorNormalize(this.getCenterX() - this.m_VectorX, this.getCenterY() - this.m_VectorY, this.m_Speed * deltaTime);

    this.setCenterPosition(this.getCenterX() - vector[0], this.getCenterY() - vector[1]);
    this.m_Shadow.setCenterPosition(this.getCenterX(), this.getCenterY() - 15);
  },

  update: function(deltaTime) {
    this._super(deltaTime);
  },

  deepCopy: function() {
    return cc.BigEnemy.create();
  }
});

cc.BigEnemy.create = function() {
  var entity = new cc.BigEnemy();
  entity.init();

  return entity;
};