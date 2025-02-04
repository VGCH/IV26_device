const char reb_d[] PROGMEM = R"rawliteral(
   function rebootdev() {
        modal.style.display = "block";
     }
   var t = 60;
   var time = document.getElementsByClassName("clock")[0];
     function fun() {
         t--;
        time.innerHTML = "<b>Оставшееся время: "+ t +" сек.</b>"
       if(t <= 0) {
         location.href = "/";
         clearInterval(inter);
       }
   }
   
  function rebootdev_s() {
      var msg = document.getElementsByClassName("modal-body")[0];
      var req5 = new XMLHttpRequest();
            req5.open('GET','/?page=dev_reboot');
            req5.onreadystatechange = function(){
              if (req5.readyState === 4 && req5.status === 200) {
                     msg.innerHTML ="<br><b>Выполняется перезапуск устройства...</b><br>"
                     var inter = setInterval("fun()", 1000);
              }
            }
        req5.send();
})rawliteral";

//=========================================

const char html[] PROGMEM = R"(
                  body {
                  background: linear-gradient(to bottom, #060345, #023f78, #540110, #013a42, #1f3d6e);
                    }
                  form, div.frame {
                       margin: 20px auto 0;
                       max-width: 500px;
                       padding: 10px;
                       border-radius: 10px;
                       background-color: #fff;
                    }
                  div#response2, div#response21 {
                       margin: 10px auto 0;
                       max-width: 500px;
                       padding: 20px;
                       border-radius: 10px;
                       background: linear-gradient(to bottom right, #9df3f5, #e6e8e7);
                    }
                    label {
                        display: block;
                        color: #5769a1;
                        margin: 10px;
                    }
                  input[type=text], input[type=password], input[type=number], input[type=time], input[type=file], select {
                        width: 100%;
                        padding: 10px;
                        margin-bottom: 15px;
                        border: 1px solid #ccc;
                        border-radius: 4px;
                        box-sizing: border-box;
                      }
                     input[type=submit] {
                        background-color: #3482f7;
                        color: white;
                        padding: 12px 20px;
                        border: none;
                        border-radius: 4px;
                        cursor: pointer;
                     }
                    h2 {
                        text-align: center;
                        margin-top: 10px;
                        font-size: 30px;
                        color: white;
                    }
                    text {
                       text-align: left;
                       margin-top: 5px;
                       font-size: 18px;
                       font-family: Noto Sans;
                       color: #023c52;
                     }
                    div.live {
                       text-align: right;
                       margin-top: 0px;
                       font-size: 30px;
                       font-family: Arial;
                       color: #066094;
                     }
                     div.links {
                       text-align: left;
                       margin-top: 10px;
                       margin-bottom: 10px;
                       margin-left: 10px;
                       font-size: 16px;
                       font-family: Arial;
                       color: #521c02;
                     }
                    div.modal {
                       text-align: left;
                       margin-top: 0px;
                       font-size: 30px;
                       color: #066094;
                     }
                      a {
                       text-align: center;
                       margin-top: 0px;
                       font-size: 16px;
                       text-decoration: none;
                       color: #9ee8e8;
                     }
                     a.mod {
                       text-align: center;
                       margin-top: 0px;
                       font-size: 18px;
                       text-decoration: none;
                       color: #3e5d80;
                     }
                    .spoiler input, .spoiler div  { 
                        display: none; 
                     }
                    .spoiler :checked ~ div {
                     display: block;
                     }
                     footer {
                       text-align: center;
                       margin-top: 10px;
                       font-size: 15px;
                       color: #cbd6f2;
                     }
                      #myBtn {                     
                      background-color: #9C27B0;  
                      color: white; 
                      padding: 12px 16px;
                      font-size: 18px;   
                      font-weight: bold;   
                      border: none;   
                      cursor: pointer;   
                      width: 180px;        
                     }
                      .btn_off {
                       display: inline-block; /* Строчно-блочный элемент */
                       background: #0e8038; /* Серый цвет фона */
                       color: #fff; /* Белый цвет текста */
                       padding: 1rem 1.5rem; /* Поля вокруг текста */
                       text-decoration: none; /* Убираем подчёркивание */
                       border-radius: 3px; /* Скругляем уголки */
                      }  
                       .btn_on {
                       display: inline-block; /* Строчно-блочный элемент */
                       background: #800e1b; /* Серый цвет фона */
                       color: #fff; /* Белый цвет текста */
                       padding: 1rem 1.5rem; /* Поля вокруг текста */
                       text-decoration: none; /* Убираем подчёркивание */
                       border-radius: 3px; /* Скругляем уголки */
                      }                        
                      .modal {
                        display: none; /* Hidden by default */
                        position: fixed; /* Stay in place */
                        z-index: 1; /* Sit on top */
                        padding-top: 250px; /* Location of the box */
                        left: 0;
                        top: 0;
                        width: 100%; /* Full width */
                        height: 100%; /* Full height */
                        overflow: auto; /* Enable scroll if needed */
                        background-color: rgb(0,0,0); /* Fallback color */
                        background-color: rgba(0,0,0,0.4); /* Black w/ opacity */
                        border-radius: 10px;
                    }
                    .modal-content {
                        position: relative;
                        background-color: #97e1f7;
                        margin: auto;
                        padding: 0;
                        border: 0px solid #cdeef7;
                        width: fit-content;
                        border-radius: 10px;
                        box-shadow: 0 4px 8px 0 rgba(0,0,0,0.2),0 6px 20px 0 rgba(0,0,0,0.19);
                        -webkit-animation-name: animatetop;
                        -webkit-animation-duration: 0.4s;
                        animation-name: animatetop;
                        animation-duration: 0.4s;
                    }
                   @-webkit-keyframes animatetop {
                        from {top:-300px; opacity:0}
                        to {top:0; opacity:1}
                    }
                   @keyframes animatetop {
                        from {top:-300px; opacity:0}
                        to {top:0; opacity:1}
                    }
                     .close {
                        color: white;
                        float: right;
                        font-size: 28px;
                        font-weight: bold;
                    }
                    .close:hover,
                    .close:focus {
                        color: #000;
                        text-decoration: none;
                        cursor: pointer;
                    }
                    .modal-header {
                        padding: 5px 16px;
                        color: white;
                        font-size: 12px;
                        text-align: left;
                        border-radius: 10px;
                    }
                    .modal-body {
                        padding: 12px 16px;
                        font-size: 18px;
                        text-align: center;
                    }
                    .modal-footer {
                        padding: 12px 16px;
                        color: #702457;
                        font-size: 16px;
                        text-align: right;
                        border-radius: 10px;
                    }
                    .input-file {
                    position: relative;
                    display: inline-block;
                    padding: 10px 20px;
                    border: none;
                    border-radius: 4px;
                    }
                   .input-file span {
                   position: relative;
                   display: inline-block;
                   cursor: pointer;
                   outline: none;
                   text-decoration: none;
                   font-size: 14px;
                   vertical-align: middle;
                   color: rgb(255 255 255);
                   text-align: center;
                   border-radius: 4px;
                   background-color: #419152;
                   line-height: 22px;
                   height: 40px;
                   padding: 10px 20px;
                   box-sizing: border-box;
                   border: none;
                   margin: 0;
                   transition: background-color 0.2s;
                  }
                  .input-file input[type=file] {
                   position: absolute;
                   margin: 10;
                   z-index: -1;
                   opacity: 0;
                   display: block;
                    width: 0;
                   height: 0;
                    }
                   .hidden {
                      display: none; /* Скрыть элемент */
                    }
                  /* Focus */
                  .input-file input[type=file]:focus + span {
                   box-shadow: 0 0 0 0.2rem rgba(0,123,255,.25);
                    }
 
                  /* Hover/active */
                  .input-file:hover span {
                  background-color: #59be6e;
                   }
                  .input-file:active span {
                  background-color: #2E703A;
                    }
 
                  /* Disabled */
                  .input-file input[type=file]:disabled + span {
                    background-color: #eee;
                  }
                  
                  /* Переключатели*/
                  .switch {
                    position: relative;
                    display: inline-block;
                    width: 60px;
                    height: 34px;
                  }
                  
                  .switch input {display:none;}
                  
                  .slider {
                    position: absolute;
                    cursor: pointer;
                    top: 0;
                    left: 0;
                    right: 0;
                    bottom: 0;
                    background-color: #ccc;
                    -webkit-transition: .4s;
                    transition: .4s;
                  }
                  
                  .slider:before {
                    position: absolute;
                    content: "";
                    height: 26px;
                    width: 26px;
                    left: 4px;
                    bottom: 4px;
                    background-color: white;
                    -webkit-transition: .4s;
                    transition: .4s;
                  }
                  
                  input:checked + .slider {
                    background-color: #2196F3;
                  }
                  
                  input:focus + .slider {
                    box-shadow: 0 0 1px #2196F3;
                  }
                  
                  input:checked + .slider:before {
                    -webkit-transform: translateX(26px);
                    -ms-transform: translateX(26px);
                    transform: translateX(26px);
                  }
                  
                  /* Rounded sliders */
                  .slider.round {
                    border-radius: 34px;
                  }
                  
                  .slider.round:before {
                    border-radius: 50%;
                  }
                  /*progress bar*/
                  #prg {
                    width:0;
                    color:white;
                    margin-bottom: 10px;
                    padding-top: 0px;
                    padding-bottom: 0px;
                    text-align:center;
                    border-radius: 3px;
                    border: none;
                  )";

//================================================
const char divcode[] PROGMEM = R"rawliteral(
    <div id="myModal" class="modal">
  <div class="modal-content">
    <div class="modal-header">
      <span class="close">&times;</span>
      <text>Перезагрузка устройства</text>
    </div>
    <div class="modal-body">
     <br>
      <a class ="btn_on" href="#" onclick="rebootdev_s()"><b>Перезагрузить устройство</b></a>
      <br>
    </div>
    <div class="modal-footer">
      <span class = "clock"> <br></span>
    </div>
  </div>
</div>
 <script>
 var modal = document.getElementById("myModal");
 var span = document.getElementsByClassName('close')[0];
 span.onclick = function() {
     modal.style.display = "none";
 }
  window.onclick = function(event) {
     if(event.target == modal) {
         modal.style.display = "none";
     }
   }
  </script>)rawliteral";
  
 //==============================================
 // Скрипт для формы конфигурации
const char config_js[] PROGMEM = R"rawliteral(
  <script>
        const form = document.getElementById('config-form');
              form.addEventListener('submit', (event) => {
                    event.preventDefault();
                    const formData = new FormData(form);
                    const xhr = new XMLHttpRequest(); 
                          xhr.open('POST', '/?page=indata');  
                          xhr.addEventListener('load', () => {
                           if (xhr.status === 200) {
                                  document.getElementById('response').innerHTML = xhr.responseText;
                                    }else{
                                       document.getElementById('response').innerHTML = 'Ошибка отправки';
                                          }
                                    });
                          xhr.send(formData);
                       });
   </script>
   <script>
          document.getElementById('switch').addEventListener('change', function() {
                  var status_s = this.checked ? 'on' : 'off';
                  var xhr = new XMLHttpRequest();
                  xhr.open('POST', '?page=indata', true);
                  xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
                  xhr.onreadystatechange = function() {
                   if (this.readyState === XMLHttpRequest.DONE && this.status === 200) {
                            document.getElementById('response2').innerHTML = xhr.responseText;
                          //console.log('Данные успешно отправлены на сервер' + status_s);
                        }
                    };
                  xhr.send('switch=' + status_s);
                });
  </script>
  )rawliteral";
 //========================================
 //JS смены пароля
 const char pass_js[] PROGMEM = R"rawliteral(
  <script>
       const form = document.getElementById('config-form');
             form.addEventListener('submit', (event) => {
                  event.preventDefault();
                  const formData = new FormData(form);
                  const xhr = new XMLHttpRequest();
                        xhr.open('POST', '?page=indata');
                        xhr.addEventListener('load', () => {
                              if (xhr.status === 200) { 
                                    document.getElementById('response').innerHTML = xhr.responseText; 
                                   }else{
                                    document.getElementById('response').innerHTML = 'Ошибка отправки';
                                 }
                            });
                   var newPassword = document.getElementById("password").value;
                   var confirmNewPassword = document.getElementById("newpassword").value;
                      if (newPassword != confirmNewPassword) {
                               document.getElementById('response').innerHTML = 'Пароли не совпадают!';
                               return false;
                             }else{
                               xhr.send(formData);
                              }
                          });
  </script>)rawliteral";

  //====================================
  //Update js
  const char update_js[] PROGMEM = R"rawliteral(
    <script>
         const form = document.getElementById('config-form');
               form.addEventListener('submit', (event) => {
               prg.style.backgroundColor = 'blue';
               event.preventDefault();
               const formData = new FormData(form);
               const xhr = new XMLHttpRequest();
                     xhr.open('POST', '/update');
                     xhr.upload.addEventListener('progress', p=>{
                      let w = Math.round(p.loaded/p.total*100) + '%';
                          if(p.lengthComputable){
                            prg.innerHTML = w;
                            prg.style.width = w;
                            prg.style.paddingTop = '10px';
                            prg.style.paddingBottom = '10px';
                            }
                         if(w == '100%') prg.style.backgroundColor = 'green';
                         });    
                     xhr.addEventListener('load', () => {
                  if (xhr.status === 200) {
                         document.getElementById('response').innerHTML = xhr.responseText.replace('Update Success! Rebooting...','<text>Обновление выполнено успешно! Выполняется перезагрузка устройства, подождите...</text>'); 
                      }else{
                         document.getElementById('response').innerHTML = '<text>Ошибка отправки</text>'; 
                       }
               });
                     document.getElementById('response').innerHTML = '<text>Выполняется процесс обновления прошивки... Пожалуйста, не покидайте страницу в процессе обновления!</text>';
                     xhr.send(formData);
            });
   </script>)rawliteral";
const char api_js[] PROGMEM = R"rawliteral(
             <script>
      function api_genkey(){
         var api_gen = new XMLHttpRequest();
             api_gen.open('POST', '?page=indata',true);
             api_gen.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
             api_gen.onreadystatechange = function(){
          if (api_gen.readyState === 4 && api_gen.status === 200) {
                var data = api_gen.responseText;
                var Array = data.split("|");
                document.getElementById("APIKEY").innerHTML       = Array[0];
                document.getElementById("status_link").innerHTML  = Array[1];
                document.getElementById("channel_link").innerHTML = Array[2];
                document.getElementById("apibut").innerHTML       = "<center><a href=\"#\" class=\"btn_off\" onclick=\"api_genkey()\">Сгенерировать новый ключ</a></center>";
                 }
              }
             document.getElementById("apibut").innerHTML  = "<center>Секундочку...</center>";
             api_gen.send('genkey=' + "ok");
           }
        </script>)rawliteral";
//==============================================
const char js[] PROGMEM = R"rawliteral(
       <script>
       setInterval(server_time, 1000);
      function server_time(){
         var worktime = new XMLHttpRequest();
             worktime.open("GET","?page=time",true);
             worktime.onreadystatechange = function(){
          if (worktime.readyState === 4 && worktime.status === 200) {
                const obj = JSON.parse(worktime.responseText);
                document.getElementById("timew").innerHTML   = obj.time;
                document.getElementById("MQTT").innerHTML    = obj.MQTT;
                document.getElementById("DTM").innerHTML     = obj.DTM;
                document.getElementById("bright").innerHTML  = obj.bright;
                document.getElementById("data").innerHTML    = obj.temp;
                }
              }
             worktime.send();
           }
          </script>
          <script>
       var flying = document.getElementById('flying');
           flying.addEventListener('input', function() {
               var value = flying.value;
               var xhrs = new XMLHttpRequest();
               xhrs.open('POST', '?page=indata', true);
               xhrs.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
               xhrs.onreadystatechange = function() {
                  if (xhrs.readyState === 4 && xhrs.status === 200) {
                    document.getElementById('response').innerHTML = xhrs.responseText;
                  }
             };
             xhrs.send('flevel=' + encodeURIComponent(value));
        });
        </script>
        <script>
        var colorp = document.getElementById('colorPicker');
            colorp.addEventListener('input', function() {
               var valuec = colorp.value;
               var xhrc = new XMLHttpRequest();
               xhrc.open('POST', '?page=indata', true);
               xhrc.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
               xhrc.onreadystatechange = function() {
                  if (xhrc.readyState === 4 && xhrc.status === 200) {
                    console.log('Данные успешно отправлены на сервер ' + xhrc.responseText);
                  }
             };
             xhrc.send('color=' + encodeURIComponent(valuec));
        });
        </script>
        <script>
      function switch_b(radio){
            var value = radio;
              var xhr = new XMLHttpRequest();
                  xhr.open('POST', '?page=indata', true);
                  xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
                  xhr.onreadystatechange = function() {
                   if (xhr.readyState === 4 && xhr.status === 200) {
                          console.log('Данные успешно отправлены на сервер' + value);
                        }
                    };
                  xhr.send('switch_auto=' + value);
                }

        </script>)rawliteral";
