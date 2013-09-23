var express = require('express');
var app = express();

var io = require('socket.io').listen(82, {log: false});

app.configure(function() {
  app.use(express.static('public'));
  app.set('views', 'views');
  app.set('view engine', "ejs");
});

io.sockets.on('connection', function(socket) {
  socket.broadcast.emit('message', 'New user is connected.');

  socket.emit('message', 'Welcome to the first server ever.');

  socket.on('login', function(data) {
    socket.set('login', data.login, function() {
      var clients = io.sockets.clients(data.room);
      var server = clients.length <= 0;

      if(server) {
        socket.set('pvp', data.pvp);
      }

      socket.emit("settings", {
        id: 0,
        session: socket.id,
        pvp: (server ? data.pvp : clients[0].store.data.pvp),
        server: server,
        client: !server
      });

      for(var i = 0; i < clients.length; i++) {
        socket.emit("settings", {
          id: 1,
          session: clients[i].id,
          name: clients[i].store.data.login
        });
      }

      io.sockets.in(data.room).emit("update", {
        id: 0,
        session: socket.id,
        name: data.login
      });

      socket.join(data.room);
    });
  });

  socket.on('announcement', function(data) {
    io.sockets.in(data.room).emit("announcement", data);
  });

  socket.on('update', function(data) {
    socket.broadcast.to(data.room).emit("update", data);
  });
});

app.get('/', function(req, res) {
  res.render('index.html');
});

app.listen(81);