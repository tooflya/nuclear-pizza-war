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

cc.EngineParticle = cc.AnimatedEntity.extend({
  init: function() {
    this._super(s_EngineParticles, 4, 1);
  },

  onCreate: function() {
    this._super();

    this.animate(0.1, 1);
  },
  onDestroy: function() {
    this._super();
  },

  onAnimationEnd: function() {
    this._super();

    this.destroy();
  },

  update: function(deltaTime) {
    this._super(deltaTime);
  },

  deepCopy: function() {
    return cc.EngineParticle.create();
  }
});

cc.EngineParticle.create = function() {
  var entity = new cc.EngineParticle();
  entity.init();

  return entity;
};