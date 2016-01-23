var express = require('express');
var WebSocketServer = require('ws').Server;
var http = require('http');
var app = express();
var port = process.env.PORT || 5000;
var server = http.createServer(app);
var webSocketServer = new WebSocketServer({ server: server });

app.set('view engine', 'html');
app.use(express.static(__dirname));

webSocketServer.on("connection", function(webSocket) {
  webSocket.on("message", function(message) {
    console.log('from client:', message);
    webSocket.send('echo: ' + message);
  });
});

app.get('/', function(request, response) {
  response.sendFile('index.html');
});

server.listen(port, function() { console.log('app is running on port', port); });