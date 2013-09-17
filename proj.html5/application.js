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

(function () {
  var d = document;
  var c = {
    COCOS2D_DEBUG: 2,
    box2d: false,
    chipmunk: false,
    showFPS: true,
    loadExtension: false,
    frameRate: 1200,
    tag: 'canvas',
    engineDir: 'Library/cocos2d/',
    appFiles: [
      'Sources/resource.js',
      'Sources/Utils/Utils.js',
      'Sources/Utils/Options.js',
      'Sources/Utils/Random.js',
      'Sources/Entity/Entity.js',
      'Sources/Entity/TiledEntity.js',
      'Sources/Entity/AnimatedEntity.js',
      'Sources/Entity/Button.js',
      'Sources/Entity/Star.js',
      'Sources/Entity/Castle.js',
      'Sources/Entity/Personage.js',
      'Sources/Entity/EngineParticle.js',
      'Sources/Entity/Slice.js',
      'Sources/Entity/Bubble.js',
      'Sources/Entity/Bullet.js',
      'Sources/Entity/Pickup.js',
      'Sources/Entity/Text.js',
      'Sources/Entity/BaseEnemy.js',
      'Sources/Entity/FollowEnemy.js',
      'Sources/Entity/CastleEnemy.js',
      'Sources/Entity/FiredEnemy.js',
      'Sources/Entity/BigEnemy.js',
      'Sources/Entity/Explosion.js',
      'Sources/Entity/LongExplosion.js',
      'Sources/Entity/MineExplosion.js',
      'Sources/Enemy/EnemyWave.js',
      'Sources/Enemy/EnemyGroup.js',
      'Sources/Screens/Screen.js',
      'Sources/Screens/Preloader.js',
      'Sources/Screens/CyberHipposSplashScreen.js',
      'Sources/Screens/MojangSplashScreen.js',
      'Sources/Screens/Menu.js',
      'Sources/Screens/Level.js',
      'Sources/Managers/EntityManager.js'
    ]
  };

  window.addEventListener('DOMContentLoaded', function() {
    this.removeEventListener('DOMContentLoaded', arguments.callee, false);

    var s = d.createElement('script');
    s.src = c.engineDir + 'platform/jsloader.js';

    d.body.appendChild(s);
    document.ccConfig = c;
  });
})();