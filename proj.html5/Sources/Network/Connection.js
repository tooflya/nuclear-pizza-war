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

Connection = cc.Class.extend({
  connect: function() {
    if(!document.ccConfig.multiplayer) {
      return;
    }

    this._url = '127.0.0.1';
    this._port = '82';

    this._server = false;
    this._client = false;

    this._login = "";
    this._room = "";

    this._sessionId = -1;

    this.connection = io.connect('http://' + this._url + ':' + this._port);

    this.connection.on("connecting", function() {
      console.log("Client is trying to connecting to the server...");
    });

    this.connection.on("connect", function() {
      console.log("Connection was opened.");

      Connection._login = document.getElementById('login').value;
      Connection._room = document.getElementById('room').value;

      this.emit("login", {
        login: Connection._login,
        room: Connection._room
      });
    });

    this.connection.on("disconnect", function() {
      console.log("Connection was disconnected.");
    });

    this.connection.on("settings", function(data) {
      console.log("Setting received: " + data.id);

      var game = TEMP.m_MainLayer;

      switch(data.id) {
        case 0:
          Connection._server = data.server;
          Connection._client = data.client;
          Connection._sessionId = data.session;

          game.m_Personages[0].m_LoginName.setString(Connection._login);
          game.m_Personages[0]._sessionId = data.session;

          console.log("Settings is stored. Game is now set to " + (Connection._server ? "server" : "client"));
        break;
        case 1:
          game.addPersonage(data);
        break;
      }
    });

    this.connection.on("info", function(data, callback) {
      console.log(data.message);
    });

    this.connection.on("update", function(data) {
      var game = TEMP.m_MainLayer;
      switch(data.id) {
        case 0:
          game.addPersonage(data);
        break;
      }
      switch(data.id) {
        case 10:
          game.m_Personages.getBySessionId(data.session).onKeyDown(data.e);
        break;
        case 11:
          game.m_Personages.getBySessionId(data.session).onKeyUp(data.e);
        break;
        case 12:
          game.m_Personages.getBySessionId(data.session).setCenterPosition(data.x, data.y);
          game.m_Personages.getBySessionId(data.session).setCurrentFrameIndex(data.i);
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
      }
      switch(data.id) {
        case 1456:
          game.m_Bubbles.create();
          game.m_Bubbles.last().setCenterPosition(data.x, data.y);
        break;
      }
    });

    this.connection.on("announcement", function(data) {
      console.log(data.message);
    });
  },

  isEnabled: function() {
   return document.ccConfig.multiplayer;
  },
  isServer: function() {
    return (this._server || !document.ccConfig.multiplayer);
  },

  send: function(name, data) {
    data.room = this._room;

    this.connection.emit(name, data);
  }
});