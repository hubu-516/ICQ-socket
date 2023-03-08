var net = require('net');
var port = 22516;
var host = '127.0.0.1';
var client = new net.Socket();
client.setEncoding('binary');
//连接服务器
client.connect(port,host,function(){
      console.log("connected to server");
});
//接收服务器数据
client.on('data',function(data){
    console.log("server say:"+ data);
    document.getElementById("text1").value=document.getElementById("text1").value+data+"\n";
});
client.on('close',function(){
    console.log("closees safely");
});
function client_send(){
    client.write(document.getElementById("text2").value);
}