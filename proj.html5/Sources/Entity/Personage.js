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

cc.Personage = cc.AnimatedEntity.extend({
  init: function(transfer, parent, callback) {
    this._super(s_Personage, 4, 5, parent, function(){});

    this.m_BroadcastTransfer = transfer;

    this.m_EngineParticles = cc.EntityManager.create(5, cc.EngineParticle.create(), this.getParent(), 23);
    this.m_Shadow = cc.Entity.create(s_Shadow);
    this.m_Shockwave = cc.Entity.create(s_PersonageShockwave, this.getParent());
    this.m_Shockwave.setZOrder(22);
    this.m_Shockwave.m_Power = 1;

    this.setCollideable(true);
    this.setIgnoreSorting(false);

    this.m_CommandMove = [false, false, false, false, false];

    this.m_SpeedX = 100;
    this.m_SpeedY = 100;

    this.m_Flying = false;

    this.m_AnimationTime = 0.1;
    this.m_AnimationTimeElapsed = 0;

    this.m_AnimationFrameSide = 0;

    this.m_EngineParticlesAnimationTime = 0.3;
    this.m_EngineParticlesAnimationTimeElapsed = 0;

    this.m_EngineParticlesAnimationTime = 0.3;
    this.m_EngineParticlesAnimationTimeElapsed = 0;

    this.m_JetPackPower = 100;
    this.m_JetPackPowerFull = 100;

    this.m_SpacebarLastPushTime = 0;

    this.m_ShockwaveScale = 1.5;

    this.m_IsShouldFire = false;
    this.m_FireVectorX = 0;
    this.m_FireVectorY = 0;

    this.m_FireTime = 0.45;
    this.m_FireTimeElapsed = 0;

    this.setMaxHealth(10000);

    this.setCurrentFrameIndex(8);

    callback(this);

    if(Connection.isEnabled()) {
      this.m_LoginName = cc.Text.create(Connection._login, 16, this);
    }

    if(Connection.isEnabled() && this.m_BroadcastTransfer) {
      var p = this;

      setInterval(function() {
        Connection.send("update", {
          id: 12,
          session: Connection._sessionId,
          x: p.getCenterX(),
          y: p.getCenterY(),
          i: p.getCurrentFrameIndex()
        });
      }, 500);
    }
  },

  onCreate: function() {
    this._super();
  },
  onDestroy: function() {
    this._super();

    this.m_Shockwave.destroy();
    this._parent.m_Explosions[1].create();
    this._parent.m_Explosions[1].last().setCenterPosition(this.getCenterX(), this.getCenterY() + this._parent.m_Explosions[1].last().getHeight() / 2 - 30);

    cc.AudioEngine.getInstance().playEffect(s_PersonageDestroy);
    cc.Director.getInstance().replaceScene(cc.TransitionFade.create(3.0, cc.GameOver.create()));
  },

  setFireCoordinates: function(x, y) {
    this.m_FireVectorX = x;
    this.m_FireVectorY = y;
  },

  move: function(deltaTime) {
    var x = this.getCenterX();
    var y = this.getCenterY();

    for(var i = 0; i < 4; i++) {
      if(!this.m_CommandMove[i]) continue;

      switch(i) {
        case 0:
          y += this.m_SpeedY * deltaTime;
        break;
        case 1:
          y -= this.m_SpeedY * deltaTime;
        break;
        case 2:
          x -= this.m_SpeedX * deltaTime;
        break;
        case 3:
          x += this.m_SpeedX * deltaTime;
        break;
      }
    }

    var pontencialFrame = this.getCurrentFrameIndex() - this.m_AnimationFrameSide;

    if(this.m_IsShouldFire) {
      var padding1 = 0;
      var padding2 = 50;
      var padding3 = 100;

      var fcx = this.m_FireVectorX + (CAMERA_CENTER_X - this.getCenterX());
      var fcy = -this.m_FireVectorY - (CAMERA_CENTER_Y - this.getCenterY());

      if(fcy > padding1)
      {
        pontencialFrame = 8;

        pontencialFrame += 4;

        if(Math.abs(fcx) > Math.abs(fcy)*2) {
          pontencialFrame -= 4;
        } else if(Math.abs(fcx) > Math.abs(fcy) * 0.75) {
        } else {
          pontencialFrame += 4;
        }
      }
      else if(fcy < padding1)
      {
        pontencialFrame = 8;

        pontencialFrame -= 4;

        if(Math.abs(fcx) > Math.abs(fcy)*2) {
          pontencialFrame += 4;
        } else if(Math.abs(fcx) > Math.abs(fcy) * 0.75) {
        } else {
          pontencialFrame -= 4;
        }
      }

      if(fcx < 0)
      {
        this.setScaleX(1);
      }
      else
      {
        this.setScaleX(-1);
      }
    } else {
      if(this.m_CommandMove[0])
      {
        pontencialFrame = 8;

        pontencialFrame -= 8;

        if(this.m_CommandMove[2] || this.m_CommandMove[3])
        {
          pontencialFrame += 4;
        }
      }
      else if(this.m_CommandMove[1])
      {
        pontencialFrame = 8;

        pontencialFrame += 8;

        if(this.m_CommandMove[2] || this.m_CommandMove[3])
        {
          pontencialFrame -= 4;
        }
      }

      if((this.m_CommandMove[2] || this.m_CommandMove[3]) && !this.m_CommandMove[0] && !this.m_CommandMove[1]) {
        pontencialFrame = 8;
      }

      if(x < this.getCenterX())
      {
        this.setScaleX(1);
      }
      else if(x > this.getCenterX())
      {
        this.setScaleX(-1);
      }
    }

    pontencialFrame += this.m_AnimationFrameSide;

    this.setCurrentFrameIndex(pontencialFrame);

    this.setCenterPosition(x, y);
    this.m_Shockwave.setCenterPosition(x, y - 15);
    this.m_Shadow.setCenterPosition(x, y - 15 - this.getZ());

    if(Connection.isEnabled()) {
      this.m_LoginName.setPosition(this.getWidth() / 2, this.getHeight() / 2 + this.getHeight());
      this.m_LoginName.setScaleX(this.getScaleX());
    }
  },

  startFly: function() {
    if(this.m_JetPackPower < this.m_JetPackPowerFull / 2) return;
    if(this.getZ() > MIN_Z) return;

    this.m_EngineParticlesAnimationTime = 0.1;
    this.m_FlyDownSpeed = 0;

    this.m_Flying = true;
      cc.AudioEngine.getInstance().playEffect(s_PersonageFlying);
  },
  endFly: function() {
    this.m_EngineParticlesAnimationTime = 0.3;
    this.m_Flying = false;
  },
  damage: function() {
    if(this.getZ() < 10) return;
    //if(!Utils::isOnPizza(this)) return;

    this.endFly();
    this.m_FlyDownSpeed = 20;

    this.getParent().shake(0.8, 4.0);

    cc.AudioEngine.getInstance().playEffect(s_PersonageFlyingDamage);
  },

  update: function(deltaTime) {
    this._super(deltaTime);

    this.m_AnimationTimeElapsed += deltaTime;
    this.m_EngineParticlesAnimationTimeElapsed += deltaTime;

    // Simple animation

    if(this.m_AnimationTimeElapsed >= this.m_AnimationTime)
    {
      this.m_AnimationTimeElapsed = 0;

      if(this.m_AnimationFrameSide == 3) {
        this.m_AnimationFrameSide = 0;
      } else {
        this.m_AnimationFrameSide++;
      }
    }

    // Engine particles animation

    if(this.m_EngineParticlesAnimationTimeElapsed >= this.m_EngineParticlesAnimationTime)
    {
      this.m_EngineParticlesAnimationTimeElapsed = 0;

      //if(!this.mIsOutOfTop && !this.mFall)
      {
        this.m_EngineParticles.create();
        this.m_EngineParticles.last().setCenterPosition(this.getCenterX(), this.getCenterY() - 15);
      }
    }

    // Flying

    if(this.m_Flying) {

      this.addZ(120.0 * deltaTime);

      this.m_JetPackPower = this.m_JetPackPower > 0 ? this.m_JetPackPower - 50 * deltaTime : 0;

      if(this.m_JetPackPower <= 0) {
        this.endFly();
      }
    } else {
      if(this.getZ() > MIN_Z) {
        this.m_EngineParticlesAnimationTime = 1000;

        this.m_FlyDownSpeed += 10 * deltaTime;
        this.removeZ((this.m_FlyDownSpeed * 60) * deltaTime);
      } else {
        this.m_EngineParticlesAnimationTime = 0.3;

        this.m_Flying = false;

        this.m_JetPackPower = this.m_JetPackPower >= this.m_JetPackPowerFull ? this.m_JetPackPowerFull : this.m_JetPackPower + 20 * deltaTime;

        if(this.m_FlyDownSpeed >= 10.0)
        {
          this.m_Shockwave.setScale(0);
          this.m_Shockwave.create();
          this.m_Shockwave.runAction(cc.ScaleTo.create(0.2, this.m_ShockwaveScale));

          this.m_FlyDownSpeed = 0;
          this.m_ShockwaveTimeElapsed = 0;
        }
      }
    }

    // Shockwave

    this.m_ShockwaveTimeElapsed += deltaTime;

    if(this.m_ShockwaveTimeElapsed >= 0.2 && this.m_Shockwave.isVisible()) {
      this.m_Shockwave.destroy();
    }

    // Fire Time

    if(this.m_IsShouldFire) {
      this.m_FireTimeElapsed += deltaTime;

      if(this.m_FireTimeElapsed >= this.m_FireTime) {
        this.m_FireTimeElapsed = 0;

        this.fire();
      }
    }

    this.move(deltaTime);
  },

  onKeyUp: function(e) {
    switch(e) {
      case cc.KEY.up:
      case cc.KEY.w:
        this.m_CommandMove[0] = false;
      break;
      case cc.KEY.down:
      case cc.KEY.s:
        this.m_CommandMove[1] = false;
      break;
      case cc.KEY.left:
      case cc.KEY.a:
        this.m_CommandMove[2] = false;
      break;
      case cc.KEY.right:
      case cc.KEY.d:
        this.m_CommandMove[3] = false;
      break;
      case cc.KEY.space:
        this.m_CommandMove[4] = false;

        this.endFly();
      break;
    }

    if(Connection.isEnabled() && this.m_BroadcastTransfer) {
      Connection.send("update", {
        id: 11,
        session: Connection._sessionId,
        e: e
      });
    }
  },
  onKeyDown: function(e) {
    switch(e) {
      case cc.KEY.up:
      case cc.KEY.w:
        this.m_CommandMove[0] = true;
      break;
      case cc.KEY.down:
      case cc.KEY.s:
        this.m_CommandMove[1] = true;
      break;
      case cc.KEY.left:
      case cc.KEY.a:
        this.m_CommandMove[2] = true;
      break;
      case cc.KEY.right:
      case cc.KEY.d:
        this.m_CommandMove[3] = true;
      break;
      case cc.KEY.space:
        if(this.m_CommandMove[4]) return;
        this.m_CommandMove[4] = true;

        if(new Date().getTime() - this.m_SpacebarLastPushTime < 300) {
            this.damage();
        } else {
          this.startFly();
        }

        this.m_SpacebarLastPushTime = new Date().getTime();
      break;
    }

    if(Connection.isEnabled() && this.m_BroadcastTransfer) {
      Connection.send("update", {
        id: 10,
        session: Connection._sessionId,
        e: e
      });
    }
  },

  onMouseDown: function(e) {
    this.m_IsShouldFire = true;

    if(Connection.isEnabled() && this.m_BroadcastTransfer) {
      Connection.send("update", {
        id: 13,
        session: Connection._sessionId,
        e: e
      });
    }
  },
  onMouseUp: function(e) {
    this.m_IsShouldFire = false;

    if(Connection.isEnabled() && this.m_BroadcastTransfer) {
      Connection.send("update", {
        id: 14,
        session: Connection._sessionId,
        e: e
      });
    }
  },
  onMouseMoved: function(e) {
    if(this.m_BroadcastTransfer) {
      var location = this.getParent().convertToNodeSpace(cc.p(e._point.x, e._point.y));
    } else {
      var location = cc.p(e.location_custom.x, e.location_custom.y);
    }

    this.setFireCoordinates((location.x - CAMERA_CENTER_X), (location.y - CAMERA_CENTER_Y));

    this.m_MouseX = e._point.x + this.getCenterX() - CAMERA_CENTER_X;
    this.m_MouseY = e._point.y + this.getCenterY() - CAMERA_CENTER_Y;

    if(this.m_BroadcastTransfer) {
      e.location_custom = cc.p(location.x, location.y);
    }

    if(Connection.isEnabled() && this.m_BroadcastTransfer) {
      Connection.send("update", {
        id: 15,
        session: Connection._sessionId,
        e: e
      });
    }
  },
  onMouseDragged: function(e) {
    if(this.m_BroadcastTransfer) {
      var location = this.getParent().convertToNodeSpace(cc.p(e._point.x, e._point.y));
    } else {
      var location = cc.p(e.location_custom.x, e.location_custom.y);
    }

    this.setFireCoordinates((location.x - CAMERA_CENTER_X), (location.y - CAMERA_CENTER_Y));

    this.m_MouseX = e._point.x + this.getCenterX() - CAMERA_CENTER_X;
    this.m_MouseY = e._point.y + this.getCenterY() - CAMERA_CENTER_Y;

    if(this.m_BroadcastTransfer) {
      e.location_custom = cc.p(location.x, location.y);
    }

    if(Connection.isEnabled() && this.m_BroadcastTransfer) {
      Connection.send("update", {
        id: 16,
        session: Connection._sessionId,
        e: e
      });
    }
  },

  fire: function() {
    this.getParent().m_Bullets.create();

    var x = this.m_FireVectorX + (CAMERA_CENTER_X - this.getCenterX());
    var y = -this.m_FireVectorY - (CAMERA_CENTER_Y - this.getCenterY());

    this.getParent().m_Bullets.last().setCurrentFrameIndex(0);
    this.getParent().m_Bullets.last().setCoordinates(x, y, this.m_MouseX, this.m_MouseY);
    this.getParent().m_Bullets.last().setCenterPosition(this.getCenterX(), this.getCenterY());
    this.getParent().m_Bullets.last().by = "personage";

    cc.AudioEngine.getInstance().playEffect(s_PersonageShoot);
  },

  onCollide: function(object, description) {
    switch(description) {
      case "pickup":
      break;
      case "enemy":
        this._super();

        this.m_Health -= 10;
      break;
      case "bullet":
        this._super();

        this.m_Health -= object.m_Power;
      break;
    }
  }
});

cc.Personage.create = function(transfer, parent, callback) {
  var entity = new cc.Personage();
  entity.init(transfer, parent, callback);

  return entity;
};