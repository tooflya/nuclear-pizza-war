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

cc.Text = cc.LabelTTF.extend({
  init: function(string, size, parent, callback) {
    this._super();

    this.setString(string);
    this.setFontSize(size);
    this.setFontName(s_Font);

    parent.addChild(this);

    if(callback) {
      callback(this);
    }
  }
});

cc.Text.create = function(string, size, parent, callback) {
  var entity = new cc.Text();
  entity.init(string, size, parent, callback);

  return entity;
};