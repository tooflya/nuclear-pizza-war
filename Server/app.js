var express = require('express');
var app = express();

var io = require('socket.io').listen(82, {log: false});

app.configure(function() {
  app.use(express.static('public'));
  app.use(express.logger());
  app.use(express.favicon());
  app.set('views', 'views');
  app.set('view engine', "jade");
});

io.sockets.on('connection', function(socket) {
  socket.broadcast.emit('message', 'New user is connected.');

  socket.emit('message', 'Welcome to the first server ever.');

  socket.on('login', function(data) {
    socket.set('login', data.login, function() {
      socket.emit("info", {
        message: "Login was set successfully. (" + data.login + ")"
      });

      socket.emit("info", {
        message: "You have join to the room: " + data.room
      });

      var clients = io.sockets.clients(data.room);

      socket.emit("settings", {
        id: 0,
        session: socket.id,
        server: clients.length <= 0,
        client: clients.length >= 1
      });

      for(var i = 0; i < clients.length; i++) {      console.log(clients[i]);
        socket.emit("settings", {
          id: 1,
          session: clients[i].id,
          name: clients[i].store.data.login
        });
      }

      io.sockets.in(data.room).emit("announcement", {
        message: data.login + " have joined to the room."
      });

      io.sockets.in(data.room).emit("update", {
        id: 0,
        session: socket.id,
        name: data.login
      });

      socket.join(data.room);
    });
  });

  socket.on('update', function(data) {
      socket.broadcast.to(data.room).emit("update", data);
  });
});

app.listen(80);