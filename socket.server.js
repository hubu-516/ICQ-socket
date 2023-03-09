//处理网页socket
var app = require('express')();
var server = require('http').Server(app);
var WebSocket = require('ws');
const FileReader = require('FileReader');
const io=require('socket.io')(server);
var wss = new WebSocket.Server({ port: 23516 });
var ws_list=new Array();

//处理与c++主服务端socket
var net = require('net');
var port = 22516;
var host = '127.0.0.1';
var client = new net.Socket();
client.setEncoding('utf-8');
//连接服务器
client.connect(port,host,function(){
      console.log("connected to c++ server");
});

wss.on('connection', function connection(ws) {
    console.log('(js)server: receive connection.'+ws.toString());
    ws_list.push(ws);
    ws.on('message', function incoming(message) {
        console.log(typeof(message));
        //reader.readAsText(message, "UTF-8");
        console.log('(js)server: received: %s', message.toString());
        client.write(message.toString());
        
        
    });

    ws.send('world');
});

app.get('/', function (req, res) {
  res.sendfile(__dirname + '/index.html');
});

app.listen(3000);

//接收服务器数据
client.on('data',function(data){
  console.log(data);
  for(var i=0;i<ws_list.length;i++)
        {
           ws_list[i].send(data.toString());
        }
});

client.on('close',function(){
    console.log("closees safely");
});
function client_send(){
    
}