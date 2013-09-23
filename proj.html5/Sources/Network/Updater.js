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

Updater = cc.Class.extend({
  update: function(data) {
    var game = TEMP.m_MainLayer;

    if(!game.m_Personages[0].isVisible()) return;

    switch(data.id) {
      case 0:
        game.addPersonage(data);
      break;
      case 10:
        game.m_Personages.getBySessionId(data.session).onKeyDown(data.e);
      break;
      case 11:
        game.m_Personages.getBySessionId(data.session).onKeyUp(data.e);
      break;
      case 12:
        game.m_Personages.getBySessionId(data.session).setCenterPosition(data.x, data.y);
        game.m_Personages.getBySessionId(data.session).setCurrentFrameIndex(data.i);
        game.m_Personages.getBySessionId(data.session).m_Health = data.h;

        if(!game.m_Personages.getBySessionId(data.session).isVisible()) {
          if(data.h > 0) {
            game.m_Personages.getBySessionId(data.session).onCreatePrivate();
          }
        }
      break;
      case 13:
        game.m_Personages.getBySessionId(data.session).onMouseDown(data.e);
      break;
      case 14:
        game.m_Personages.getBySessionId(data.session).onMouseUp(data.e);
      break;
      case 15:
        game.m_Personages.getBySessionId(data.session).onMouseMoved(data.e);
      break;
      case 16:
        game.m_Personages.getBySessionId(data.session).onMouseDragged(data.e);
      break;
      case 17:
        game.m_Personages.getBySessionId(data.session).fire(data);
      break;
      case 18:
        game.m_Personages.getBySessionId(data.session).reset();
      break;
      case 1456:
        game.m_Bubbles.create();
        game.m_Bubbles.last().setCenterPosition(data.x, data.y);
      break;
    }
  }
});