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

  cc.Entity = cc.Sprite.extend({
    init: function(fileName, parent, callback) {
      this.initWithFile(fileName);

      this.m_TextureFileName = fileName;

      this.m_Z = MIN_Z;

      this.m_Width = this.getTextureRect().size.width;
      this.m_Height = this.getTextureRect().size.height;

      this.setAnchorPoint(cc.p(0.5, 0.5));

      this.m_IsCollidable = false;
      this.m_IsOutOfTop = false;

      this.m_HealthFull = 1;
      this.m_Health = this.m_HealthFull;

      this.m_IsRed = false;
      this.m_RedTime = 0.4;
      this.m_RedTimeElapsed = 0;

      this.m_BarWidth = 25;
      this.m_BarHeight = 5;
      this.m_Fall = false;

      this.m_RectangleVerticles1 = [];
      this.m_RectangleVerticles2 = [];

      this.R1 = 0;
      this.G1 = 255;
      this.B1 = 0;

      if(parent) {
        parent.addChild(this);
      }

      if(callback) {
        callback(this);
      } else {
        this.onDestroyPrivate();
      }
    },

    create: function(callback) {
      this.onCreate();

      if(callback) {
        callback();
      }
    },

    destroy: function(callback) {
      this.onDestroy();

      if(callback) {
        callback();
      }
    },

    onCreate: function() {
      this.onCreatePrivate();
    },
    onDestroy: function() {
      this.onDestroyPrivate();
    },

    onCreatePrivate: function() {
      this.setVisible(true);

      if(this.m_Shadow) {
        if(!this.m_Shadow.getParent()) {
          this.getParent().addChild(this.m_Shadow);
          this.m_Shadow.setIsShadow();
        }

        this.m_Shadow.create();
      }

      this.scheduleUpdate();
    },
    onDestroyPrivate: function() {
      this.setVisible(false);

      if(this.m_Shadow) {
        this.m_Shadow.destroy();
      }

      if(this.m_Manager) {
        this.m_Manager.destroy(this.id);
      }

      this.unscheduleUpdate();
    },

    setCenterPosition: function(centerX, centerY) {
      this.setPosition(cc.p(centerX, centerY));
    },

    getCenterX: function() {
      return this.getPosition().x;
    },
    getCenterY: function() {
      return this.getPosition().y;
    },

    getWidth: function() {
      return this.m_Width;
    },
    getHeight: function() {
      return this.m_Height;
    },
    getWidthScaled: function() {
      return this.m_Width * this.getScaleX();
    },
    getHeightScaled: function() {
      return this.m_Height * this.getScaleY();
    },

    setManager: function(manager) {
      this.m_Manager = manager;
    },
    setID: function(id) {
      this.id = id;
    },

    setIsShadow: function() {
      this.setZOrder(22);
      this.setColor(cc.c3(0.0, 0.0, 0.0));
      this.setOpacity(150);
    },

    getZ: function() {
      return this.m_Z;
    },
    setZ: function(z) {
      this.m_Z = z;

      if(this.m_Shadow)
      {
        this.m_Shadow.setScale(1.0 - this.m_Z / MAX_Z);
      }
    },
    addZ: function(z) {
      if(this.m_Z - z >= MAX_Z) return;

      this.setZ(this.m_Z + z);

      this.setCenterPosition(this.getCenterX(), this.getCenterY() + z);
    },
    removeZ: function(z) {
      if(this.m_Z - z <= MIN_Z)
      {
        this.m_Z = MIN_Z;

        return;
      }

      this.setZ(this.m_Z - z);

      this.setCenterPosition(this.getCenterX(), this.getCenterY() - z);
    },

    setMaxHealth: function(health) {
      this.m_HealthFull = health;
      this.m_Health = this.m_HealthFull;
    },
    setSpeed: function(speed) {
      this.m_Speed = speed;
    },

    setCollideable: function(value) {
      this.m_IsCollidable = value;
    },

    isOutOfScreen: function() {
      var x = this.getCenterX();
      var y = this.getCenterY();

      return x < -500 - this.getWidth() / 2 || x > CAMERA_WIDTH + 500 + this.getWidth() / 2 || y < -300 - this.getHeight() / 2 || y > CAMERA_HEIGHT + 300 + this.getHeight() / 2;
    },

    collideWidth: function(entity, factor) {
      if(!factor) factor = 0.5;
      if(!this.isVisible() || !entity.isVisible()) return false;
      if(this.getZ() > entity.getHeight() || entity.getZ() > this.getHeight()) return false;

      if (this.getCenterX() - (this.getWidth() / 2) * factor < entity.getCenterX() + (entity.getWidth() / 2) * factor &&
        this.getCenterX() + (this.getWidth() / 2) * factor > entity.getCenterX() - (entity.getWidth() / 2) * factor &&
        this.getCenterY() - (this.getHeight() / 2) * factor < entity.getCenterY() + (entity.getHeight() / 2) * factor &&
        this.getCenterY() + (this.getHeight() / 2) * factor > entity.getCenterY() - (entity.getHeight() / 2) * factor &&
        this.getZ() <= (entity.getZ() + entity.getHeight()) * factor)
      {
        return true;
      }

      return false;
    },
    circlesCollideWithCoordinates: function(px, py, factor) {
      var x = this.getCenterX() - px;
      var y = this.getCenterY() - py;

      var d = Math.max(this.m_Width, this.m_Height) / 2 + factor;

      return x * x + y * y < d * d;
    },
    circlesCollideCoordinatesWith: function(x1, y1, x2, y2, radius) {
      var x = x1 - x2;
      var y = y1 - y2;

      var d = Math.max(this.getWidth(), this.getHeight()) / 2 + radius;

      return x * x + y * y < d * d;
    },

    onCollide: function() {
      this.setRed();
    },
    setRed: function() {
      this.m_IsRed = true;
      this.m_RedTimeElapsed = 0;

      this.setColor(new cc.Color3B(255, 0, 0));
    },

    update: function(deltaTime) {
      this._super();
  
      if(this.m_IsCollidable)
      {
        var magnet;
        var radius;

        switch(2/*Options::FORTIFICATION_LEVEL*/)
        {
          case 0:
            magnet = 50.0;
            radius = 135.0;
          break;
          case 1:
            magnet = 60.0;
            radius = 160.0;
          break;
          case 2:
            magnet = 70.0;
            radius = 185.0;
          break;
          case 3:
            magnet = 80.0;
            radius = 210.0;
          break;
        }

        obstacle(this, CAMERA_CENTER_X, CAMERA_CENTER_Y, magnet, radius);

        if((!isOnPizza(this) && this.getZ() <= MIN_Z) || (this.getZ() <= MIN_Z && this.getZOrder() == 1))
        {
          if(this.getCenterY() > CAMERA_CENTER_Y)
          {
            this.setZOrder(1);

            this.m_IsOutOfTop = true;
          }
          else
          {
            this.m_IsOutOfTop = false;
          }

          this.setCenterPosition(this.getCenterX(), this.getCenterY() - 300 * deltaTime);

          this.m_Shadow.setVisible(false);

          this.m_Health -= 0.5;
          
          this.setRed();

          this.m_Fall = true;
        }
        else
        {
          if(this.getZOrder() == 1)
          {
            this.setZOrder(24);
          }

          this.m_Shadow.setVisible(true);

          this.m_Fall = false;
          this.m_IsOutOfTop = false;
        }
      }

      if(this.m_IsRed)
      {
        this.m_RedTimeElapsed += deltaTime;

        if(this.m_RedTimeElapsed >= this.m_RedTime)
        {
          this.m_IsRed = false;
          this.m_RedTimeElapsed = 0;

          this.setColor(new cc.Color3B(255, 255, 255));
        }
      }
    },
    draw: function() {
      this._super();

      if(this.m_Health < this.m_HealthFull && this.m_Health > 0) {
        this.R1 = this.m_Health < 75 ? 255 : 0;
        this.G1 = this.m_Health > 45 ? 255 : 0;
        this.B1 = 0;

        var x1;
        var x2;
        var y1;
        var y2;

        x1 = (this.getWidth() - this.m_BarWidth) / 2;
        x2 = this.getWidth() - x1 + 1 * 2;

        y1 = -5;
        y2 = y1 - this.m_BarHeight;

        this.m_RectangleVerticles1[0] = cc.p(x1, y1);
        this.m_RectangleVerticles1[1] = cc.p(x2, y1);
        this.m_RectangleVerticles1[2] = cc.p(x2, y2);
        this.m_RectangleVerticles1[3] = cc.p(x1, y2);

        x1 = x1 + 1;
        x2 = x1 + (((x2 - x1) - 1) * (this.m_Health) / this.m_HealthFull);

        y1 = y1 - 1;
        y2 = y1 - this.m_BarHeight + 1 * 2;

        if(this.getScaleX() < 0)
        {
          var padding = this.m_BarWidth - this.m_BarWidth * (this.m_Health / this.m_HealthFull);

          x1 += padding;
          x2 += padding;
        }

        this.m_RectangleVerticles2[0] = cc.p(x1, y1);
        this.m_RectangleVerticles2[1] = cc.p(x2, y1);
        this.m_RectangleVerticles2[2] = cc.p(x2, y2);
        this.m_RectangleVerticles2[3] = cc.p(x1, y2);

        cc.drawingUtil.setDrawColor4B(0, 0, 0, 255);
        cc.drawingUtil.drawSolidPoly(this.m_RectangleVerticles1, 4, cc.Color4B(0, 0, 0, 1));

        cc.drawingUtil.setDrawColor4B(this.R1, this.G1, this.B1, 255);
        cc.drawingUtil.drawSolidPoly(this.m_RectangleVerticles2, 4, cc.Color4B(0, 0, 0, 1));
      } else if(this.m_Health <= 0) {
        this.destroy();
      }
    },

    deepCopy: function() {
      return cc.Entity.create(this.m_TextureFileName);
    }
});

cc.Entity.create = function(fileName, parent, callback) {
  var entity = new cc.Entity();
  entity.init(fileName, parent, callback);

  return entity;
};