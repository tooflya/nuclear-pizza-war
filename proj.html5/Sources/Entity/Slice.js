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

cc.Slice = cc.Entity.extend({
  init: function() {
    this._super(s_Slice);

    this.m_Shadow = cc.Entity.create(s_Slice);

    this.m_VectorX = 1;
    this.m_VectorY = 1;
  },

  onCreate: function() {
    this._super();

    this.m_Speed = random(150, 350);

    this.setCenterPosition(probably(50) ? -500 : CAMERA_WIDTH + 500, probably(50) ? -300 : CAMERA_HEIGHT + 300);

    if(this.getCenterX() > CAMERA_CENTER_X) {
      this.setScaleX(1);
    } else {
      this.setScaleX(-1);
    }

    cc.AudioEngine.getInstance().playEffect(s_SliceCreated);
  },
  onDestroy: function() {
    this._super();
  },

  setCoordinates: function(x, y) {
    this.m_VectorX = this.getCenterX() - x;
    this.m_VectorY = this.getCenterY() - y;
  },

  update: function(deltaTime) {
    this._super(deltaTime);

    var vector = vectorNormalize(this.m_VectorX, this.m_VectorY, this.m_Speed * deltaTime);

    var x = this.getCenterX() - vector[0];
    var y = this.getCenterY() - vector[1];

    this.setCenterPosition(x, y);
    this.m_Shadow.setCenterPosition(x, y - 200);

    if(this.isOutOfScreen()) {
      this.destroy();
    }
  },

  deepCopy: function() {
    return cc.Slice.create();
  }
});

cc.Slice.create = function() {
  var entity = new cc.Slice();
  entity.init();

  return entity;
};