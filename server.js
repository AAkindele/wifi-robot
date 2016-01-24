var express = require('express');
var WebSocketServer = require('ws').Server;
var http = require('http');
var app = express();
var port = process.env.PORT || 5000;
var server = http.createServer(app);
var webSocketServer = new WebSocketServer({ server: server });
var redis = require("redis");
var redisClient = redis.createClient();

app.set('view engine', 'html');
app.use(express.static(__dirname));

var KEY_MAP = {
  87: 'w',
  65: 'a',
  83: 's',
  68: 'd'
};

webSocketServer.on('connection', function(webSocket) {
  webSocket.on('message', function(message) {
    var parsedMessage = parseInt(message);
    if(parsedMessage) {
      var letterCommand = KEY_MAP[parsedMessage];
      if(letterCommand) {
        redisClient.rpush('commands', letterCommand);
      }
    }
  });
});

app.get('/', function(request, response) {
  response.sendFile('index.html');
});

app.get('/commands', function(request, response) {
  var commands;
  redisClient.lrange('commands', 0, -1, function(_err, commandList){
    commands = commandList.join('');
    redisClient.ltrim('commands', 1, 0);
    response.send(commands || '');
  });
});

server.listen(port, function() { console.log('app is running on port', port); });