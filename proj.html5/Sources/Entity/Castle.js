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

  cc.Castle = cc.AnimatedEntity.extend({
    init: function(parent, callback) {
      this._super(s_Castle, 8, 1, parent, callback);

      this.m_Wall1 = cc.Entity.create(s_Wall1, this);
      this.m_Wall2 = cc.Entity.create(s_Wall2, this);
      this.m_Wall3 = cc.Entity.create(s_Wall3, this);

      this.m_Wall1.create();
      this.m_Wall2.create();

      this.m_Wall1.setCenterPosition(this.getWidth() / 2 - 4, this.getHeight() / 2 - 30);
      this.m_Wall2.setCenterPosition(this.getWidth() / 2 - 4, this.getHeight() / 2 - 30);
      this.m_Wall3.setCenterPosition(this.getWidth() / 2 - 4, this.getHeight() / 2 - 30);

      this.animate(0.1);
    },

    onCreate: function() {
      this._super();
    },

    update: function(deltaTime) {
      this._super(deltaTime);
    }
});

cc.Castle.create = function(parent, callback) {
  var entity = new cc.Castle();
  entity.init(parent, callback);

  return entity;
};