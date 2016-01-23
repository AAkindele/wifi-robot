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

webSocketServer.on('connection', function(webSocket) {
  webSocket.on('message', function(message) {
    var parsedMessage = parseInt(message);
    if(parsedMessage) {
      console.log('from client:', parsedMessage);
      redisClient.rpush('commands', parsedMessage);
    }
  });
});

app.get('/', function(request, response) {
  response.sendFile('index.html');
});

server.listen(port, function() { console.log('app is running on port', port); });