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

  cc.AnimatedEntity = cc.TiledEntity.extend({
    init: function(fileName, horizontalFramesCount, verticalFramesCount, parent, callback) {
      this._super(fileName, horizontalFramesCount, verticalFramesCount, parent, callback);

      this.m_AnimationTime = 0;
      this.m_AnimationTimeElapsed = 0;

      this.m_IsAnimationRunning = false;
    },

    animate: function(animationTime, animationsCount) {
      this.setCurrentFrameIndex(0);

      this.m_IsAnimationRunning = true;

      this.m_AnimationTime = animationTime;
      this.m_AnimationsCount = animationsCount ? animationsCount : -1;
    },
    onAnimationEnd: function() {
      this.m_IsAnimationRunning = false;
    },

    update: function(deltaTime) {
      this._super(deltaTime);

      if(this.m_IsAnimationRunning) {
        this.m_AnimationTimeElapsed += deltaTime;

        if(this.m_AnimationTimeElapsed >= this.m_AnimationTime) {
          this.m_AnimationTimeElapsed = 0;

          if(this.getCurrentFrameIndex() < this.m_FramesCount - 1) {
            this.nextFrameIndex();
          } else {
            if(--this.m_AnimationsCount > 0 || this.m_AnimationsCount < 0) {
              this.nextFrameIndex();
            } else {
              this.onAnimationEnd();
            }
          }
        }
      }
    },

    deepCopy: function() {
      return cc.AnimatedEntity.create(this.textureFileName, this.horizontalFramesCount, this.verticalFramesCount, this.getParent());
    }
});

cc.AnimatedEntity.create = function(fileName, horizontalFramesCount, verticalFramesCount, parent, callback) {
  var entity = new cc.AnimatedEntity();
  entity.init(fileName, horizontalFramesCount, verticalFramesCount, parent, callback);

  return entity;
};