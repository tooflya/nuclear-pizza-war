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

    this.m_VectorX = 0;
    this.m_VectorY = 0;

    this.m_ShootPadding = 0;

    this.animate(0.1);
    this.setCollideable(true);
  },
  onDestroy: function() {
    this._super();
    
    this.getParent().getParent().m_EnemiesCount--;

    if(this.getParent().getParent().m_EnemiesCount + 1 > 0) {
      this.getParent().m_Explosions[0].create();
      this.getParent().m_Explosions[0].last().setCenterPosition(this.getCenterX(), this.getCenterY());

      this.getParent().shake(0.5, 3.0);
    }

    cc.AudioEngine.getInstance().playEffect(s_EnemyDestroy);
  },

  onCollide: function(object, description) {
    this._super();

    switch(description) {
      case "bullet":
        this.m_VectorX = object.m_VectorX;
        this.m_VectorY = object.m_VectorY;

        this.m_ShootPadding = 20;
        this.m_ShootPaddingSpeed = 100;

        this.m_Health -= object.m_Power;
      break;
    }
  },

  update: function(deltaTime) {
    this._super(deltaTime);

    if(this.m_ShootPadding > 0) {
      var vector = vectorNormalize(this.m_VectorX, this.m_VectorY, this.m_ShootPaddingSpeed * deltaTime);

      this.setCenterPosition(this.getCenterX() + vector[0], this.getCenterY() + vector[1]);

      this.m_ShootPadding -= this.m_ShootPaddingSpeed * deltaTime;
    } else {
      this.move(deltaTime);
    }

    this.m_Shadow.setCenterPosition(this.getCenterX(), this.getCenterY() - 15);
  }
});