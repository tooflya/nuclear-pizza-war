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

Settings = cc.Class.extend({
  update: function(data) {
    var game = TEMP.m_MainLayer;

    switch(data.id) {
      case 0:
        Connection._server = data.server;
        Connection._client = data.client;
        Connection._pvp = data.pvp;
        Connection._sessionId = data.session;

        game.m_Personages[0].m_LoginName.setString(Connection._login);
        game.m_Personages[0]._sessionId = data.session;
      break;
      case 1:
        game.addPersonage(data);
      break;
    }
  }
});