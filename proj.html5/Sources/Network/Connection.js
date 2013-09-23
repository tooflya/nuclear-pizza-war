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

    this._url = '37.229.129.226';
    this._port = '82';

    this._server = false;
    this._client = false;

    this._login = "";
    this._room = "";
    this._pvp = false;

    this.m_Updater = new Updater();
    this.m_Settings = new Settings();

    this._sessionId = -1;

    this.connection = io.connect('http://' + this._url + ':' + this._port);

    this.connection.on("connect", function() {
      Connection._login = document.getElementById('login').value;
      Connection._room = document.getElementById('room').value;
      Connection._pvp = document.getElementById('pvp').checked;

      this.emit("login", {
        login: Connection._login,
        room: Connection._room,
        pvp: Connection._pvp
      });
    });

    this.connection.on("disconnect", function() {
      console.log("Connection was disconnected.");
    });

    this.connection.on("settings", function(data) {
      this.m_Settings.update(data);
    });

    this.connection.on("update", function(data) {
      this.m_Updater.update(data);
    });

    this.connection.on("announcement", function(data) {
      var game = TEMP.m_StaticLayer;

      game.announcement(data);
    });
  },

  announcement: function(data) {
    if(!this.isServer()) {
      //return false;
    }

    this.send("announcement", data);
  },

  isEnabled: function() {
   return document.ccConfig.multiplayer;
  },
  isServer: function() {
    return (this._server || !document.ccConfig.multiplayer);
  },
  isPVP: function() {
    return this.isEnabled() && this._pvp;
  },

  send: function(name, data) {
    if(document.ccConfig.multiplayer) {
      data.room = this._room;

      this.connection.emit(name, data);
    }
  }
});