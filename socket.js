var ws = new WebSocket('ws://81.68.123.231:23516');

ws.onopen = function () {
  console.log('ws onopen');
  mes.nick = "Admin:";
  mes.text = "加入了服务器";
  ws.send(JSON.stringify(mes));
};

ws.onmessage = function (e) {
  console.log('ws onmessage');
  console.log('from server: ' + e.data);
  const data = JSON.parse(e.data);
  const message = document.createElement('p');
  const nickSpan = document.createElement('span');
  const textSpan = document.createElement('span');
  nickSpan.innerText = data.nick + ": ";
  nickSpan.classList.add('nick');
  textSpan.innerText = data.text;
  textSpan.classList.add('text');
  message.appendChild(nickSpan);
  message.appendChild(textSpan);
  document.getElementById('text1').appendChild(message);
  //将聊天框拖到最下方
  text1.scrollTop = text1.scrollHeight;
};

function client_send() {
  var mes = {
    nick: "",
    text: ""
  };
  var a = document.getElementById("text2").value;
  if (a !== '') {
    mes.nick = document.getElementById("text3").value;
    mes.text = document.getElementById("text2").value;
    ws.send(JSON.stringify(mes));
    document.getElementById("text2").value = "";
  } else {
  
    const war_ = document.createElement("span");
    war_.innerText = "输入不能为空";
    war_.classList.add('war');
    document.getElementById('text1').appendChild(war_);
  }
}

ws.onclose = function () {
  console.log("disconnected");
};
