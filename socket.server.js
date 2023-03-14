//处理网页socket
var app = require('express')();
var server = require('http').Server(app);
var WebSocket = require('ws');
const FileReader = require('FileReader');
const io=require('socket.io')(server);
var wss = new WebSocket.Server({ port: 23516 });
var ws_list=new Array();
//定义历史消息数组
var log=new Array();
var count_log=0;
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
    ws.send("已连接到服务器");
    ws_list.push(ws);
    for (var i = 0; i < count_log; i++)
    {
    ws.send(log[i].toString());
    }
    ws.on('message', function incoming(message) {
        console.log(typeof(message));
        //reader.readAsText(message, "UTF-8");
        console.log('(js)server: received: %s', message.toString());
        client.write(message.toString());
        
        
    });

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
  //是否半重置历史
  if (count_log<999) log[count_log]=data.toString();
        else
        {
            for (var i = 0; i < 500; i++)
            {
                log[i]=log[i+500];
                log[i+500]="\0";
            }
            count_log=500;
            log[count_log]=data.toString();
            
        }
  count_log++;
});

client.on('close',function(){
    console.log("closees safely");
});
