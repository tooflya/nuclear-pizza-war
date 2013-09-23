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

cc.WealthManager = cc.EntityManager.extend({
  init: function(capacity, entity, parent) {
    this._super(capacity, entity, parent, 1, true);

    this.m_Textes = [];
    this.m_Textes[0] = cc.Text.create("x", 24, parent);
    this.m_Textes[1] = cc.Text.create("x", 24, parent);
    this.m_Textes[2] = cc.Text.create("x", 24, parent);

    this.m_Textes[0].setVisible(false);
    this.m_Textes[1].setVisible(false);
    this.m_Textes[2].setVisible(false);
  },

  update: function() {
    this.clear();

    var x = 160;
    var y = 20;

    var count = 0;

    for(var i = 0; i < 3; i++) {
      var c = 0;
      var elements = cc.Level.instance.m_Wealth[i];

      if(elements >= 10) {
        this.create();
        this.last().setCurrentFrameIndex(i);
        this.last().setCenterPosition(x, y);

        x += 35;

        this.m_Textes[i].setVisible(true);
        this.m_Textes[i].setString("x" + elements);
        this.m_Textes[i].setPosition(x, y);

        x += this.m_Textes[i].getWidth() + 25;

        count++;
      } else {
        this.m_Textes[i].setVisible(false);

        for(var j = 0; j < elements; j++) {
          this.create();
          this.last().setCurrentFrameIndex(i);
          this.last().setCenterPosition(x, y);

          x += 10;

          count++;
          c++;
        }
      }

      if(c > 0) {
        x += 25;
      }
    }

    cc.Level.instance.m_StaticLayer.m_WealthText.setVisible(count > 0);
  }
});

cc.WealthManager.create = function(capacity, entity, parent) {
  var manager = new cc.WealthManager();
  manager.init(capacity, entity, parent);

  return manager;
};