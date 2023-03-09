(function(){function r(e,n,t){function o(i,f){if(!n[i]){if(!e[i]){var c="function"==typeof require&&require;if(!f&&c)return c(i,!0);if(u)return u(i,!0);var a=new Error("Cannot find module '"+i+"'");throw a.code="MODULE_NOT_FOUND",a}var p=n[i]={exports:{}};e[i][0].call(p.exports,function(r){var n=e[i][1][r];return o(n||r)},p,p.exports,r,e,n,t)}return n[i].exports}for(var u="function"==typeof require&&require,i=0;i<t.length;i++)o(t[i]);return o}return r})()({1:[function(require,module,exports){
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
},{"net":2}],2:[function(require,module,exports){

},{}]},{},[1]);
