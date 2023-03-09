
  var socket = io('81.68.123.231:23516');
  socket.on('say', function (data)
  {
    console.log('from server: ' + data);
    document.getElementById("text1").value=document.getElementById("text1").value+data+"\n" 
  })
  
  function client_send() {
    var a = document.getElementById("text2").value
    if(a!=0)
    {
        var val = document.getElementById("text2").value;
        socket.emit('say',val);
        document.getElementById("text2").value="";
    }
    else
    {
        document.getElementById('war').innerHTML='输入不能为空';
        setTimeout(2000);
        document.getElementById('war').innerHTML='';
        
    }
  }
