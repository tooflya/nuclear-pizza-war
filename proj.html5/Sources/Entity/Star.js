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

cc.Star = cc.TiledEntity.extend({
  init: function() {
    this._super(s_BackgroundStars, 3, 2);

    this.m_Speed = randomf(1.0, 100.0);

    this.m_X1 = 0;
    this.m_X2 = CAMERA_WIDTH;

    this.m_Y1 = CAMERA_HEIGHT + this.getHeight();
    this.m_Y2 = 0;
  },

  onCreate: function() {
    this._super();

    this.setCurrentFrameIndex(random(0, 6));
    this.setCenterPosition(randomf(this.m_X1, this.m_X2), this.m_Y1);
    this.setBlendFunc(gl.ONE, gl.ZERO);
  },

  update: function(deltaTime) {
    this._super(deltaTime);

    this.setCenterPosition(this.getCenterX(), this.getCenterY() - this.m_Speed * deltaTime);

    if(this.getCenterY() < this.m_Y2 - this.getHeight()) {
      this.destroy();
      this.create();
    }
  },

  setCoordinates: function(x1, x2, y1, y2) {
    this.m_X1 = x1;
    this.m_X2 = x2;

    this.m_Y1 = y1;
    this.m_Y2 = y2;
  },

  deepCopy: function() {
    return cc.Star.create();
  }
});

cc.Star.create = function() {
  var entity = new cc.Star();
  entity.init();

  return entity;
};