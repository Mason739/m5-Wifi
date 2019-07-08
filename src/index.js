<script>
const url='http://192.168.4.1/go';
const url2='http://192.168.4.1/stop';
const url3='http://192.168.4.1/reverse';
const url4='http://192.168.4.1/left';
const url5='http://192.168.4.1/right';
window.onkeydown = function(event) {
  console.log("Key pressed");
  var Http = new XMLHttpRequest();
   if (event.keyCode == 87) {
     Http.open("GET", url);
   } else  if (event.keyCode == 83) {
     Http.open("GET", url3);
   } else if (event.keyCode == 65) {
     Http.open("GET", url4);
   } else  if (event.keyCode == 68) {
     Http.open("GET", url5);
   }
   Http.send();
}

window.onkeyup = function(event) {
     var Http2 = new XMLHttpRequest();
     Http2.open("GET", url2);
    Http2.send();
}

</script>
