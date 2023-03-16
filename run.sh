#!/bin/bash
screen -R server bash -c './server';
send "\01";
send "d";
screen -R socket bash -c 'node socket.server.js';
send "\01";
send "d";