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

cc.BaseEnemy = cc.AnimatedEntity.extend({

  onCreate: function() {
    this._super();

    this.animate(0.1);
    this.setCollideable(true);

    this.m_Healthfull = 100;
  },
  onDestroy: function() {
    this._super();

    if(this.getParent()) {
      this.getParent().getParent().m_EnemiesCount--;
    }
  },

  onCollide: function(object, description) {
    switch(description) {
      case "bullet":
        this.m_Health -= object.m_Power;
      break;
    }
  },

  update: function(deltaTime) {
    this._super(deltaTime);

    this.move(deltaTime);
  }
});