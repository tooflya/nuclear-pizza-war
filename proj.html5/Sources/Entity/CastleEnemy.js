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

    this.m_Speed = 50;
  },

  onCreate: function() {
    this._super();
  },
  onDestroy: function() {
    this._super();
  },

  move: function(deltaTime) {
    var vectorX = this.getCenterX() - CAMERA_CENTER_X;
    var vectorY = this.getCenterY() - CAMERA_CENTER_Y;

    var vector = vectorNormalize(vectorX, vectorY, this.m_Speed * deltaTime);

    this.setCenterPosition(this.getCenterX() - vector[0], this.getCenterY() - vector[1]);
  },

  update: function(deltaTime) {
    this._super(deltaTime);
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