// 使用 express 框架
//const res = require('response');
var app = require('express')();
var express = require("express");
const { message } = require('statuses');
var server = require('http').Server(app);
var http = require('http');
const { response } = require('express');
// 引入 socket.io
var io = require('socket.io')(server);
// 监听 23516 端口
server.listen(23516);
console.log('listening');
// 开启静态资源服务
app.use(express.static("./static"));
// io 各种事件
//response.setHeader("Access-Control-Allow-Origin", "*");

io.on('connection', (io)=> {
    console.log('server: receive connection.');
    io.on('say', (message) => {
        console.log(typeof(message));
        console.log('server: received: %s', message.toString());
        io.broadcast.emit(message.toString());        
    });
  
});






