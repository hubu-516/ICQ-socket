


  var ws = new WebSocket('ws://81.68.123.231:23516');
  ws.onopen = function () {
    console.log('ws onopen');
    ws.send('from client: hello');
  };
  ws.onmessage = function (e) {
    console.log('ws onmessage');
    console.log('from server: ' + e.data);
  };
  
  function client_send() {
    var val = document.getElementById("text2").value
    ws.send(val)
    document.getElementById("text2").value=""
  }
ws.close=function(){
    console.log("disconnected");
}