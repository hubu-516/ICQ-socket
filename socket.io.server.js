var app = require('express')();
var reader = require('FileReader');
var server = require('http').Server(app);
var WebSocket = require('ws');

var wss = new WebSocket.Server({ port: 23516 });

wss.on('connection', function connection(ws) {
    console.log('server: receive connection.');
    ws.on('message', function incoming(message) {
        console.log('server: received: %s', message);
        reader.readAsText(message, 'utf-8');
        reader.onload = function (e) {
        
        }
        ws.send(reader.result);
    });

    ws.send('world');
});

app.get('/', function (req, res) {
  res.sendfile(__dirname + '/index.html');
});

app.listen(3000);