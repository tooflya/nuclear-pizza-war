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

cc.Level = cc.Screen.extend({
  init: function() {
    this._super();

    this.m_EnemiesCount = 0;

    this.m_StaticLayer = cc.StaticLayer.create();
    this.m_MainLayer = cc.MainLayer.create();

    this.addChild(this.m_MainLayer, 0);
    this.addChild(this.m_StaticLayer, 1);

    if(document.ccConfig.COCOS2D_DEBUG >= 2) {
      this.mDebugText = cc.Text.create("", 14, this.m_StaticLayer, function(entity) {
        entity.setFontName("Sans Serif");
        entity.setColor(new cc.Color3B(0.0, 255.0, 0.0));
        entity.setZOrder(1000);
      });
      this.mDebugUpdateTimeElapsed = 0;
    }
  },

  update: function(deltaTime) {
    this._super(deltaTime);

    var x = -this.m_MainLayer.m_Personages[0].getCenterX() + CAMERA_CENTER_X;
    var y = -this.m_MainLayer.m_Personages[0].getCenterY() + CAMERA_CENTER_Y;

    if(y < 300 && y > -300) {
      this.m_MainLayer.setPosition(this.m_MainLayer.getPosition().x, y);
    }

    if(x < 500 && x > -500) {
      this.m_MainLayer.setPosition(x, this.m_MainLayer.getPosition().y);
    }

    if(document.ccConfig.COCOS2D_DEBUG >= 2) {
      this.mDebugUpdateTimeElapsed += deltaTime;

      if(this.mDebugUpdateTimeElapsed > 0.1) {
        this.mDebugUpdateTimeElapsed = 0;

        this.mDebugText.setString(
        "Debug Information:\n\n"
        + "Camera width: " + CAMERA_WIDTH + "\n"
        + "Camera height: " + CAMERA_HEIGHT + "\n"
        + "Frames per second: " + Math.round(1.0 / director.getDeltaTime()) + "\n"
        + "Camera position: \n"
        + "\tx: " + Math.round(this.m_MainLayer.getPosition().x) + "\n"
        + "\ty: " + Math.round(this.m_MainLayer.getPosition().y) + "\n"
        + "Draw calls: " + "undefinied" + "\n"
        + "Total children count: " + this.m_MainLayer.getTotalChildrenCount() + "\n"
        + "Total visible children count: " + this.m_MainLayer.getTotalChildrenCount(true) + "\n"
        + "Total circles: " + this.m_MainLayer.m_CircleOperations + "\n"
        + "");
        this.mDebugText.setPosition(10 + this.mDebugText.getWidth() / 2, CAMERA_HEIGHT - this.mDebugText.getHeight() / 2 - 10);
      }
    }
  }
});

cc.StaticLayer = cc.Layer.extend({
  init: function() {
    this._super();

    this.m_PrepareForBattle = cc.Text.create(s_PrepareForBattle, 65, this, function(text) {
      text.setPosition(CAMERA_CENTER_X, CAMERA_CENTER_Y + 200);
      text.setOpacity(0);
    });
    this.m_StartLevel = cc.Text.create("", 48, this, function(text) {
      text.setPosition(CAMERA_CENTER_X, CAMERA_CENTER_Y - 200);
      text.setOpacity(0);
    });
    this.m_StartLevelTime = cc.Text.create("", 36, this, function(text) {
      text.setPosition(CAMERA_CENTER_X, CAMERA_CENTER_Y + 90);
      text.setOpacity(0);
    });
    this.m_WarningLowHealth = cc.Text.create(s_WarningLowHealth, 65, this, function(text) {
      text.setPosition(CAMERA_CENTER_X, CAMERA_CENTER_Y + 130);
      text.setColor(new cc.Color3B(255, 0, 0));
      text.setOpacity(0);
    });

    this.m_GameStartTime = 3;
    this.m_GameStartTimeElapsed = 0;

    this.m_LevelStartTime = 3;
    this.m_LevelStartTimeElapsed = 0;

    this.m_GameStartCount = 0;
    this.m_LevelStartCount = 0;
    this.m_CurrentLevel = 1;

    this.m_IsGameRunning = false;
    this.m_IsLevelRunning = false;

    this.scheduleUpdate();
  },

  update: function(deltaTime) {
    this._super(deltaTime);

    // Textes

    if(!this.m_IsGameRunning) {
      this.m_GameStartTimeElapsed += deltaTime;

      if(this.m_GameStartTimeElapsed >= this.m_GameStartTime) {
        this.m_GameStartTimeElapsed = 0;

        switch(++this.m_GameStartCount) {
          case 1:
            this.m_PrepareForBattle.runAction(cc.FadeIn.create(this.m_GameStartTime));
          break;
          case 2:
          break;
          case 3:
            this.m_PrepareForBattle.runAction(cc.FadeOut.create(this.m_GameStartTime));
          break;
          case 4:
            this.m_IsGameRunning = true;
          break;
        }
      }
    } else {
      if(this.m_IsLevelRunning) {
        if(this.getParent().m_EnemiesCount <= 0) {
          this.m_LevelStartTimeElapsed += deltaTime;

          if(this.m_LevelStartTimeElapsed >= this.m_LevelStartTime) {
            this.m_LevelStartTimeElapsed = 0;

            switch(++this.m_LevelStartCount) {
              case 1:
                this.m_StartLevel.setString("Level cleared!");
                this.m_StartLevel.runAction(cc.FadeIn.create(this.m_LevelStartTime));
              break;
              case 3:
                this.m_StartLevel.runAction(cc.FadeOut.create(this.m_LevelStartTime));
              break;
              case 4:
                this.m_LevelStartCount = 0;
                this.m_IsLevelRunning = false;
                this.m_CurrentLevel++;
                this.m_LevelStartTime = 1;
              break;
            }
          }
        }
      } else {
        this.m_LevelStartTimeElapsed += deltaTime;

        if(this.m_LevelStartTimeElapsed >= this.m_LevelStartTime) {
          this.m_LevelStartTimeElapsed = 0;

          if(this.m_CurrentLevel == 1) {
            switch(++this.m_LevelStartCount) {
              case 1:
                this.m_StartLevel.setString("Level " + this.m_CurrentLevel);
                this.m_StartLevel.runAction(cc.FadeIn.create(this.m_LevelStartTime));
              break;
              case 2:
              break;
              case 3:
                this.m_StartLevel.runAction(cc.FadeOut.create(this.m_LevelStartTime));
              break;
              case 4:
                this.m_LevelStartCount = 0;
                this.m_IsLevelRunning = true;

                this.getParent().m_MainLayer.startLevel(this.m_CurrentLevel);
              break;
            }
          } else {
            switch(++this.m_LevelStartCount) {
              case 1:
                this.m_StartLevelTime.setString("Level {0} will begin in {1} seconds...".format(this.m_CurrentLevel, 6 - this.m_LevelStartCount));
                this.m_StartLevelTime.runAction(cc.FadeIn.create(this.m_LevelStartTime));
              break;
              case 6:
                this.m_LevelStartTime = 3;
              case 2:
              case 3:
              case 4:
              case 5:
                this.m_StartLevelTime.setString("Level {0} will begin in {1} seconds...".format(this.m_CurrentLevel, 6 - this.m_LevelStartCount));
              break;
              case 7:
                this.m_StartLevelTime.runAction(cc.FadeOut.create(this.m_LevelStartTime));
              break;
              case 8:
                this.m_StartLevel.setString("Level " + this.m_CurrentLevel);
                this.m_StartLevel.runAction(cc.FadeIn.create(this.m_LevelStartTime));
              break;
              case 9:
              break;
              case 10:
                this.m_StartLevel.runAction(cc.FadeOut.create(this.m_LevelStartTime));
              break;
              case 11:
                this.m_LevelStartCount = 0;
                this.m_IsLevelRunning = true;

                this.getParent().m_MainLayer.startLevel(this.m_CurrentLevel);
              break;
            }
          }
        }
      }
    }
  }
});

cc.MainLayer = cc.Layer.extend({
  init: function() {
    this._super();

    this.m_Enemies = [];
    this.m_Explosions = [];
    this.m_Personages = [];

    this.m_BackgroundStars = cc.EntityManager.create(100, cc.Star.create(), this);
    this.m_Slices = cc.EntityManager.create(2, cc.Slice.create(), this, 500);
    this.m_Bubbles = cc.EntityManager.create(2, cc.Bubble.create(), this, 22, false);
    this.m_Pickups = cc.EntityManager.create(10, cc.Pickup.create(), this, 23, false);
    this.m_Bullets = cc.EntityManager.create(100, cc.Bullet.create(), this, 23);
    this.m_BulletsCrashes = cc.EntityManager.create(100, cc.BulletCrash.create(), this, 23);

    this.m_Enemies[0] = cc.EntityManager.create(100, cc.FollowEnemy.create(), this, 24, false);
    this.m_Enemies[1] = cc.EntityManager.create(100, cc.CastleEnemy.create(), this, 24, false);
    this.m_Enemies[2] = cc.EntityManager.create(100, cc.FiredEnemy.create(), this, 24, false);
    this.m_Enemies[3] = cc.EntityManager.create(100, cc.BigEnemy.create(), this, 24, false);

    this.m_Explosions[0] = cc.EntityManager.create(10, cc.Explosion.create(), this, 25);
    this.m_Explosions[1] = cc.EntityManager.create(10, cc.LongExplosion.create(), this, 25);
    this.m_Explosions[2] = cc.EntityManager.create(10, cc.MineExplosion.create(), this, 25);

    this.m_Background = cc.Entity.create(s_Platform, this, function(entity) {
      entity.setCenterPosition(CAMERA_CENTER_X, CAMERA_CENTER_Y);
      entity.setZOrder(18);
    });

    this.generatePizzaDecorations();

    this.m_Castle = cc.Castle.create(this, function(entity) {
      entity.create();
      entity.setCenterPosition(CAMERA_CENTER_X, CAMERA_CENTER_Y);
      entity.setZOrder(21);
    });

    this.m_Personages[0] = cc.Personage.create(true, this, function(entity) {
      entity.create();
      entity.setCenterPosition(CAMERA_CENTER_X, CAMERA_CENTER_Y - 150);
      entity.setZOrder(24);
    });

    for(var i = 0; i < 100; i++) {
      this.m_BackgroundStars.create();
      this.m_BackgroundStars.last().setCoordinates(-500, CAMERA_WIDTH + 500, CAMERA_WIDTH + 300, -300);
      this.m_BackgroundStars.last().setCenterPosition(randomf(-500, CAMERA_WIDTH + 500), randomf(-300, CAMERA_WIDTH + 300));
    }

    this.m_SliceTime = 0;
    this.m_SliceTimeElapsed = 0;

    this.m_BubbleAppearTime = 1;
    this.m_BubbleAppearTimeElapsed = 0;

    this.m_Shaking = false;

    this.setKeyboardEnabled(true);
    this.setMouseEnabled(true);

    this.scheduleUpdate();
  },

  generatePizzaDecorations: function() {
    var decorations = cc.EntityManager.create(75, cc.TiledEntity.create(s_Decorations, 2, 2), this, 19);

    for (var i = 0; i < 75; i++)
    {
      var x;
      var y;

      var angle;
      var distance;

      var ok = true;
      var iterations = 0;
      var maxIterations = 50000;

      do
      {
        angle = randomf(0.0, 1.0) * Math.PI * 2.0;
        distance = (0.3 + randomf(0.0, 1.0) * 0.7) * this.m_Background.getWidth() * 0.40 * 0.95;
        x = CAMERA_CENTER_X + Math.cos(angle) * distance;
        y = CAMERA_CENTER_Y - Math.sin(angle) * distance * 0.5;

        var collides = 0;

        for(var j = 0; j < decorations.getCount(); j++)
        {
          if(decorations.get(j).circlesCollideWithCoordinates(x, y, 1.0))
          {
            collides++;

            break;
          } else {
            iterations++;
          }
        }

        if(collides == 0)
        {
          ok = false;
        }

      } while (ok && iterations < maxIterations);

      decorations.create();
      decorations.last().setCurrentFrameIndex(random(0, 4));
      decorations.last().setCenterPosition(x, y);
    }
  },

  update: function(deltaTime) {
    this._super(deltaTime);

    this.m_CircleOperations = 0;

    this.m_SliceTimeElapsed += deltaTime;

    // Slices

    if(this.m_SliceTimeElapsed >= this.m_SliceTime) {
      this.m_SliceTimeElapsed = 0;

      this.m_SliceTime = random(10, 30);

      if(this.m_Slices.getCount() < 2) {
        this.m_Slices.create();
        this.m_Slices.last().setCoordinates(this.m_Personages[0].getCenterX(), this.m_Personages[0].getCenterY());
      }
    }

    // Bubbles

    if(Connection.isServer()) {
      if(this.m_Bubbles.getCount() < 2)
      {
        this.m_BubbleAppearTimeElapsed += deltaTime;

        if(this.m_BubbleAppearTimeElapsed >= this.m_BubbleAppearTime)
        {
          this.m_BubbleAppearTimeElapsed = 0;
          this.m_BubbleAppearTime = 5.0 + randomf(0.0, 10.0);

          var location = getSafePizzaPosition();
          this.m_Bubbles.create();
          this.m_Bubbles.last().setCenterPosition(location[0], location[1]);

          Connection.send("update", {
            id: 1456,
            x: location[0],
            y: location[1]
          });
        }
      }
    }

    // Collisions

    this.checkCollisions(deltaTime);

    // Unpacking

    this.unpacking();

    // Sort Z Order

    this.sortZOrder();

    // Update shake

    this.updateShake(deltaTime);
  },

  onKeyUp: function(e) {
    this.m_Personages[0].onKeyUp(e);
  },
  onKeyDown: function(e) {
    this.m_Personages[0].onKeyDown(e);
  },

  onMouseDown: function(e) {
    this.m_Personages[0].onMouseDown(e);
  },
  onMouseUp: function(e) {
    this.m_Personages[0].onMouseUp(e);
  },
  onMouseMoved: function(e) {
    this.m_Personages[0].onMouseMoved(e);
  },
  onMouseDragged: function(e) {
    this.m_Personages[0].onMouseDragged(e);
  },

  shake: function(d, i)
  {
    this.m_Shaking = true;
    this.m_ShakeDuration = d;
    this.m_ShakeIntensity = i;

    this.m_ShakeDurationElapsed = 0;
  },

  updateShake: function(deltaTime)
  {
    if(this.m_Shaking)
    {
      this.m_ShakeDurationElapsed += deltaTime;

      if(this.m_ShakeDurationElapsed > this.m_ShakeDuration)
      {
        this.m_Shaking = false;
        this.m_ShakeDuration = 0;

        this._parent.runAction(cc.MoveTo.create(0.2, cc.p(0, 0)));
      }
      else
      {
        var sentitX = 1;
        var sentitY = 1;
          
        if(randomf(0, 1) < 0.5) sentitX = -1;
        if(randomf(0, 1) < 0.5) sentitY = -1;

        this.getParent().setPosition(this.getParent().getPosition().x + randomf(0, 1) * this.m_ShakeIntensity * sentitX, this.getParent().getPosition().y + randomf(0, 1) * this.m_ShakeIntensity * sentitY);
      }
    }
  },

  checkCollisions: function(deltaTime) {
    for(var i = 0; i < this.m_Bubbles.getCount(); i++) {
      var bubble = this.m_Bubbles.get(i);

      for(var p = 0; p < this.m_Personages.length; p++) {
        if(bubble.collideWith(this.m_Personages[p].m_Shockwave, 1.2)) {
          bubble.onCollide(this.m_Personages[p].m_Shockwave, "shockwave");
        }

        this.m_CircleOperations++;
      }

      for(var j = 0; j < this.m_Bullets.getCount(); j++) {
        var bullet = this.m_Bullets.get(j);

        if(bullet.collideWith(bubble)) {
          bullet.onCollide(bubble, "bubble");
          bubble.onCollide(bullet, "bullet");
        }

        this.m_CircleOperations++;
      }

      for(var k = 0; k < 4; k++) {
        for(var m = 0; m < this.m_Enemies[k].getCount(); m++) {
          var enemy = this.m_Enemies[k].get(m);

          obstacle(enemy, bubble.getCenterX(), bubble.getCenterY(), 17, 50);

          this.m_CircleOperations++;
        }

        this.m_CircleOperations++;
      }

      for(var p = 0; p < this.m_Personages.length; p++) {
        obstacle(this.m_Personages[p], bubble.getCenterX(), bubble.getCenterY(), 17, 50);

        this.m_CircleOperations++;
      }

      this.m_CircleOperations++;
    }

    for(var i = 0; i < 4; i++) {
      for(var j = 0; j < this.m_Enemies[i].getCount(); j++) {
        var enemy = this.m_Enemies[i].get(j);

        for(var p = 0; p < this.m_Personages.length; p++) {
          if(enemy.collideWith(this.m_Personages[p])) {
            this.m_Personages[p].onCollide(enemy, "enemy");
          }

          if(enemy.collideWith(this.m_Personages[p].m_Shockwave, 1.2)) {
            enemy.onCollide(this.m_Personages[p].m_Shockwave, "shockwave");
          }

          this.m_CircleOperations++;
        }

        for(var k = 0; k < this.m_Bullets.getCount(); k++) {
          var bullet = this.m_Bullets.get(k);

          switch(bullet.by)
          {
            case "personage":
              if(enemy.collideWith(bullet)) {
                bullet.onCollide(enemy, "enemy");
                enemy.onCollide(bullet, "bullet");
              }
            break;
            case "enemy":
              for(var p = 0; p < this.m_Personages.length; p++) {
                if(this.m_Personages[p].collideWith(bullet)) {
                  bullet.onCollide(this.m_Personages[p], "personage");
                  this.m_Personages[p].onCollide(bullet, "bullet");
                }

                this.m_CircleOperations++;
              }
            break;
          }

          this.m_CircleOperations++;
        }

        this.m_CircleOperations++;
      }

      this.m_CircleOperations++;
    }

    for(var i = 0; i < this.m_Pickups.getCount(); i++) {
      var pickup = this.m_Pickups.get(i);

      for(var p = 0; p < this.m_Personages.length; p++) {
      if(this.m_Personages[p].collideWith(pickup, 5)) {
        pickup.follow(this.m_Personages[p].getCenterX(), this.m_Personages[p].getCenterY(), deltaTime);
      }

      if(this.m_Personages[p].collideWith(pickup)) {
        this.m_Personages[p].onCollide(pickup, "pickup");
        pickup.destroy();
      }

      this.m_CircleOperations++;
      }

      this.m_CircleOperations++;
    }
  },
  unpacking: function() {
    var padding = 0.1;

    for(var i = 0; i < 4; i++) {
      for(var j = 0; j < this.m_Enemies[i].getCount(); j++) {
        var enemy1 = this.m_Enemies[i].get(j);

        for(var k = 0; k < 4; k++) {
          for(var m = 0; m < this.m_Enemies[k].getCount(); m++) {
            var enemy2 = this.m_Enemies[k].get(m);

            if((i + 1) * (j + 1) == (k + 1) * (m + 1)) continue;

            if(enemy1.m_Shadow.collideWith(enemy2.m_Shadow, 1.0))
            {
              var x1 = enemy1.getCenterX();
              var x2 = enemy2.getCenterX();

              var y1 = enemy1.getCenterY();
              var y2 = enemy2.getCenterY();

              enemy1.setCenterPosition(x1 + (x1 > x2 ? padding : -padding), y1 + (y1 > y2 ? padding : -padding));
              enemy2.setCenterPosition(x2 + (x2 > x1 ? padding : -padding), y2 + (y2 > y1 ? padding : -padding));
            }

            this.m_CircleOperations++;
          }

          this.m_CircleOperations++;
        }

        this.m_CircleOperations++;
      }

      this.m_CircleOperations++;
    }
  },
  sortZOrder: function() {
    var i;

    for(var j = 0; j < this.getChildrenCount(); j++) {
      var entity1 = this.getChildren()[j];

      if(entity1.m_IsIgnoreSorting || !entity1.m_TextureFileName) {
        continue;
      }

      for(i = j - 1; i >= 0; i--) {
        var entity2 = this.getChildren()[i];

        if(entity2.m_IsIgnoreSorting || !entity2.m_TextureFileName) {
          continue;
        }

        if(entity2.getCenterY() - entity2.getHeightScaled() - entity2.getZ() <= entity1.getCenterY() - entity1.getHeightScaled() - entity1.getZ()) {
          this.getChildren().swapAtIndex(i + 1, entity2);
        }

        this.m_CircleOperations++;
      }

      this.m_CircleOperations++;
    }
  },

  onEnter: function() {
    this._super();
  },
  onExit: function() {
    this._super();
  },

  startLevel: function(index) {return;
    this.m_EnemiesWave = cc.EnemyWave.create();

    switch(index)
    {
      case 1:
        this.m_EnemiesWave.addGroup(cc.EnemyGroup.create(this, 0).addEnemy(1, 0, 0).addEnemy(5, 0, 0));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 0)).addEnemy(8, 2, 0));

        this.getParent().m_EnemiesCount = 6;
      break;
      case 2:
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 0)).addEnemy(5, 0, 0).addEnemy(5, 0, 0));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 15)).addEnemy(5, 0, 0).addEnemy(5, 0, 0));

        this.getParent().m_EnemiesCount = 20;
      break;
      case 3:
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 0)).addEnemy(10, 0, 0));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 15)).addEnemy(8, 0, 0).addEnemy(8, 0, 0));

        this.getParent().m_EnemiesCount = 26;
      break;
      case 4:
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 0)).addEnemy(5, 1, 0));

        this.getParent().m_EnemiesCount = 5;
      break;
      case 5:
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 0)).addEnemy(10, 0, 0));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 10)).addEnemy(5, 1, 0).addEnemy(5, 1, 0));

        this.getParent().m_EnemiesCount = 20;
      break;
      case 6:
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 0)).addEnemy(8, 2, 0));

        this.getParent().m_EnemiesCount = 8;
      break;
      case 7:
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 0)).addEnemy(8, 2, 0));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 10)).addEnemy(5, 1, 0).addEnemy(8, 2, 0).addEnemy(8, 2, 0));

        this.getParent().m_EnemiesCount = 29;
      break;
      case 8:
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 0)).addEnemy(10, 0, 0).addEnemy(10, 0, 0));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 5)).addEnemy(8, 1, 0));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 10)).addEnemy(8, 2, 0).addEnemy(8, 2, 0));

        this.getParent().m_EnemiesCount = 44;
      break;
      case 9:
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 0)).addEnemy(20, 0, 1));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 10)).addEnemy(5, 2, 1).addEnemy(5, 2, 1).addEnemy(5, 1, 1).addEnemy(5, 0, 1).addEnemy(3, 2, 1).addEnemy(7, 2, 1).addEnemy(20, 0, 1));

        this.getParent().m_EnemiesCount = 70;
      break;
      case 10:
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 0)).addEnemy(1, 3, 0));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 10)).addEnemy(1, 3, 0).addEnemy(1, 3, 0).addEnemy(1, 3, 0).addEnemy(1, 3, 0).addEnemy(1, 3, 0));

        this.getParent().m_EnemiesCount = 6;
      break;
      case 11:
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 0)).addEnemy(20, 1, 1));

        this.getParent().m_EnemiesCount = 20;
      break;
      case 12:
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 0)).addEnemy(2, 3, 0));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 10)).addEnemy(3, 1, 0).addEnemy(3, 1, 0).addEnemy(3, 1, 0));

        this.getParent().m_EnemiesCount = 11;
      break;
      case 13:
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 0)).addEnemy(20, 0, 1));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 10)).addEnemy(5, 2, 2).addEnemy(5, 2, 2).addEnemy(5, 1, 2).addEnemy(5, 0, 2).addEnemy(3, 2, 2).addEnemy(7, 2, 2).addEnemy(20, 0, 1));

        this.getParent().m_EnemiesCount = 70;
      break;
      case 14:
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 0)).addEnemy(12, 2, 1).addEnemy(12, 2, 1));

        this.getParent().m_EnemiesCount = 24;
      break;
      case 15:
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 0)).addEnemy(10, 0, 2));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 25)).addEnemy(2, 3, 1).addEnemy(2, 3, 1).addEnemy(2, 3, 1));

        this.getParent().m_EnemiesCount = 16;
      break;
      case 16:
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 0)).addEnemy(10, 1, 2).addEnemy(10, 2, 2));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 20)).addEnemy(15, 2, 1).addEnemy(10, 1, 2));

        this.getParent().m_EnemiesCount = 45;
      break;
      case 17:
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 0)).addEnemy(1, 3, 3));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 10)).addEnemy(10, 0, 2).addEnemy(10, 0, 2));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 20)).addEnemy(5, 1, 3));

        this.getParent().m_EnemiesCount = 26;
      break;
      case 18:
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 0)).addEnemy(1, 3, 3));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 3)).addEnemy(1, 0, 3).addEnemy(1, 1, 3).addEnemy(1, 2, 3).addEnemy(1, 1, 3).addEnemy(1, 1, 3).addEnemy(1, 1, 3).addEnemy(1, 3, 3).addEnemy(1, 0, 3).addEnemy(1, 0, 3)
          .addEnemy(1, 2, 3).addEnemy(1, 2, 3).addEnemy(1, 2, 3).addEnemy(1, 1, 3).addEnemy(1, 1, 3).addEnemy(1, 1, 3));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 10)).addEnemy(20, 1, 3));

        this.getParent().m_EnemiesCount = 36;
      break;
      case 19:
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 0)).addEnemy(4, 0, 2).addEnemy(4, 1, 2).addEnemy(4, 2, 2).addEnemy(4, 3, 1));

        this.getParent().m_EnemiesCount = 16;
      break;
      case 20:
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 0)).addEnemy(30, 1, 2));

        this.getParent().m_EnemiesCount = 30;
      break;
      case 21:
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 0)).addEnemy(8, 2, 2));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 10)).addEnemy(8, 2, 2).addEnemy(8, 2, 2));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 15)).addEnemy(3, 3, 3));

        this.getParent().m_EnemiesCount = 27;
      break;
      case 22:
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 0)).addEnemy(30, 0, 2));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 30)).addEnemy(10, 1, 3));

        this.getParent().m_EnemiesCount = 40;
      break;
      case 23:
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 0)).addEnemy(15, 1, 2));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 10)).addEnemy(20, 0, 2).addEnemy(20, 2, 2).addEnemy(5, 2, 3).addEnemy(5, 2, 3).addEnemy(5, 2, 3).addEnemy(5, 2, 3));

        this.getParent().m_EnemiesCount = 75;
      break;
      case 24:
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 0)).addEnemy(2, 3, 2).addEnemy(2, 3, 2).addEnemy(2, 3, 2).addEnemy(2, 3, 2));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 20)).addEnemy(30, 1, 3));

        this.getParent().m_EnemiesCount = 38;
      break;
      case 25:
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 0)).addEnemy(10, 0, 3));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 10)).addEnemy(10, 1, 3));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 10)).addEnemy(10, 2, 3));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 10)).addEnemy(10, 1, 3));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 10)).addEnemy(10, 2, 3));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 10)).addEnemy(10, 2, 3));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 10)).addEnemy(10, 2, 3));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 10)).addEnemy(10, 1, 3));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 10)).addEnemy(10, 1, 3));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 10)).addEnemy(20, 0, 3));
        this.m_EnemiesWave.addGroup((cc.EnemyGroup.create(this, 10)).addEnemy(10, 3, 3));

        this.getParent().m_EnemiesCount = 120;
      break;
      case 26:
        //AppDelegate::screens.set(3.0f, 1, 2);

        this.getParent().m_EnemiesCount = 100;
      break;
    }
  },

  // NETWORKING

  addPersonage: function(data) {
    var personage = cc.Personage.create(false, this, function(entity) {
      entity.create();
      entity.setCenterPosition(CAMERA_CENTER_X, CAMERA_CENTER_Y - 150);
      entity.setZOrder(24);
    });
    personage.m_LoginName.setString(data.name);
    personage._sessionId = data.session;

    this.m_Personages.push(personage);
  }
});

cc.Level.create = function() {
  var screen = new cc.Level();
  screen.init();

  return screen;
};

cc.MainLayer.create = function() {
  var screen = new cc.MainLayer();
  screen.init();

  return screen;
}

cc.StaticLayer.create = function() {
  var screen = new cc.StaticLayer();
  screen.init();

  return screen;
}