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

cc.EnemyGroup = cc.Node.extend({
  init: function(parent, time) {
    this._super();

    parent.addChild(this);

    this.m_Time = time;
    this.m_TimeElapsed = 0;

    this.m_Emmiters = [];
    this.m_Emmiters[0] = cc.p(200,   -30);
    this.m_Emmiters[1] = cc.p(-250,  350);
    this.m_Emmiters[2] = cc.p(200,   630);
    this.m_Emmiters[3] = cc.p(800,   20);
    this.m_Emmiters[4] = cc.p(800,   580);
    this.m_Emmiters[5] = cc.p(1050,   350);

    this.m_Groups = [];

    this.scheduleUpdate();

    if(document.ccConfig.COCOS2D_DEBUG >= 2) {
      var e = this;
      for(var i = 0; i < this.m_Emmiters.length; i++) {
        cc.Entity.create(s_Debug, cc.Level.instance.m_MainLayer, function(entity) {
          entity.create();
          entity.setZOrder(20);
          entity.setCenterPosition(e.m_Emmiters[i].x, e.m_Emmiters[i].y);

          var text = cc.Text.create(i, 20, entity);
          text.setPosition(entity.getWidth() / 2, entity.getHeight() / 2);
        });
      }
    }
  },

  addEnemy: function(count, type, level) {
    this.m_Groups.push([count, type, level]);

    return this;
  },

  update: function(deltaTime) {
    this.m_TimeElapsed += deltaTime;

    if(this.m_TimeElapsed >= this.m_Time)
    {
      this.m_TimeElapsed = 0;

      for(var i = 0; i < this.m_Groups.length; i++)
      {
        var params = this.m_Groups[i];
        var r = random(0, this.m_Emmiters.length);

        var x = this.m_Emmiters[r].x;
        var y = this.m_Emmiters[r].y;

        for(var j = 0; j < params[0]; j++)
        {
          if(j % 4 == 0 && j != 0)
          {
            x = this.m_Emmiters[r].x;
            y -= 16;
          }

          x += 16;

          var enemy = this.getParent().m_Enemies[params[1]];

          enemy.create();
          enemy = enemy.last();

          enemy.setCenterPosition(x, y);

          switch(params[1])
          {
            case 0:
              switch(params[2])
              {
                case 0:
                  enemy.setMaxHealth(100.0);
                  enemy.setSpeed(40.0);
                break;
                case 1:
                  enemy.setMaxHealth(200);
                  enemy.setSpeed(60.0);
                break;
                case 2:
                  enemy.setMaxHealth(300);
                  enemy.setSpeed(90.0);
                break;
              }
            break;
            case 1:
              switch(params[2])
              {
                case 0:
                  enemy.setMaxHealth(100);
                  enemy.setSpeed(30.0);
                break;
                case 1:
                  enemy.setMaxHealth(200);
                  enemy.setSpeed(40.0);
                break;
                case 2:
                  enemy.setMaxHealth(100);
                  enemy.setSpeed(60.0);
                break;
              }
            break;
            case 2:
              switch(params[2])
              {
                case 0:
                  enemy.setMaxHealth(150);
                  enemy.setSpeed(30.0);
                  enemy.setFireTime(randomf(3.0, 15.0));
                  enemy.setFirePower(5);
                  enemy.setFireCount(1);
                break;
                case 1:
                  enemy.setMaxHealth(300);
                  enemy.setSpeed(40.0);
                  enemy.setFireTime(randomf(3.0, 10.0));
                  enemy.setFirePower(15);
                  enemy.setFireCount(3);
                break;
                case 2:
                  enemy.setMaxHealth(450);
                  enemy.setSpeed(50.0);
                  enemy.setFireTime(randomf(3.0, 7.0));
                  enemy.setFirePower(20);
                  enemy.setFireCount(3);
                break;
              }
            break;
            case 3:
              switch(params[2])
              {
                case 0:
                  enemy.setMaxHealth(600);
                  //enemy.setFireTime(randomf(3.0, 15.0));
                  enemy.setSpeed(20.0);

                  //((BigEnemy*) enemy).mShootsCount = 7;
                break;
                case 1:
                  enemy.setMaxHealth(1000);
                  //enemy.setFireTime(randomf(3.0, 10.0));
                  enemy.setSpeed(15.0);
                  
                  //((BigEnemy*) enemy).mShootsCount = 10;
                break;
                case 2:
                  enemy.setMaxHealth(1200);
                 // enemy.setFireTime(randomf(3.0, 7.0));
                  enemy.setSpeed(10.0);
                  
                  //((BigEnemy*) enemy).mShootsCount = 12;
                break;
              }
                          break;
            case 4:
              switch(params[2])
                          {
                              case 0:
                                  enemy.setMaxHealth(600);
                                  enemy.setSpeed(40.0);
                              break;
                              case 1:
                                  enemy.setMaxHealth(1000);
                                  enemy.setSpeed(60.0);
                break;
                              case 2:
                                  enemy.setMaxHealth(1200);
                                  enemy.setSpeed(80.0);
                break;
                          }
                      break;
          }
        }
      }

      this.unscheduleUpdate();
      this.removeFromParent();
    }
  }
});

cc.EnemyGroup.create = function(parent, time) {
  var group = new cc.EnemyGroup();
  group.init(parent, time);

  return group;
}