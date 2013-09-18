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

      FORTIFICATION_LEVEL = 2;

      this.m_FortnessHealth = [];
      this.m_Wall = [];

      this.m_FortnessHealth[0] = 10;
      this.m_FortnessHealth[1] = 10;
      this.m_FortnessHealth[2] = 10;

      this.m_Wall[0] = cc.Entity.create(s_Wall1, this);
      this.m_Wall[1] = cc.Entity.create(s_Wall2, this);
      this.m_Wall[2] = cc.Entity.create(s_Wall3, this);

      this.m_Wall[0].create();
      this.m_Wall[1].create();

      this.m_Wall[0].setCenterPosition(this.getWidth() / 2 - 4, this.getHeight() / 2 - 30);
      this.m_Wall[1].setCenterPosition(this.getWidth() / 2 - 4, this.getHeight() / 2 - 30);
      this.m_Wall[2].setCenterPosition(this.getWidth() / 2 - 4, this.getHeight() / 2 - 30);

      this.animate(0.1);

      this.setMaxHealth(50);
    },

    onCreate: function() {
      this._super();
    },

    onCollide: function(object, description) {
      this.removeHealth(object.m_Power);
    },

    removeHealth: function(value) {
      if(FORTIFICATION_LEVEL <= 0) {
        this.m_Health -= value;
      } else {
        this.m_FortnessHealth[FORTIFICATION_LEVEL - 1] -= value;
        if(this.m_FortnessHealth[FORTIFICATION_LEVEL - 1] <= 0) {
          this.m_Wall[FORTIFICATION_LEVEL - 1].destroy();

          FORTIFICATION_LEVEL--;
        }
      }
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