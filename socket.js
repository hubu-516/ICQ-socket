


  var ws = new WebSocket('ws://81.68.123.231:23516');
  ws.onopen = function () {
    console.log('ws onopen');
  };
  
  ws.onmessage = function (e) {
    console.log('ws onmessage');
    console.log('from server: ' + e.data);
    document.getElementById("text1").value=document.getElementById("text1").value+e.data+"\n" 
  };
  
  function client_send() {
  
    var a = document.getElementById("text2").value
    if(a!=0)
    {
        var val = document.getElementById("text2").value
        ws.send(val)
        document.getElementById("text2").value=""
    }
    else
    {
        document.getElementById('war').innerHTML='输入不能为空';
        setTimeout(2000);
        document.getElementById('war').innerHTML='';
        
    }
  }
ws.close=function(){
    console.log("disconnected");
}