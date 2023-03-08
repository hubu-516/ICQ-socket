var net = require('net');
var port = 22516;
var host = '127.0.0.1';
var client = new net.Socket();
client.setEncoding('binary');
//连接服务器
client.connect(port,host,function(){
    while(1)
    {
        var a=prompt("发送消息:");
        client.write(a);
    }  
    
});
//接收服务器数据
client.on('data',function(data){
    console.log("server say:"+ data);
});
client.on('close',function(){
    console.log("closees safely");
});