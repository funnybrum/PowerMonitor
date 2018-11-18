#define PROGMEM ICACHE_RODATA_ATTR

const char CONFIG_PAGE[] PROGMEM = R"=====(
<HTML>
	<HEAD>
      <TITLE>%s power monitor</TITLE>
	</HEAD>
  <BODY>
    <form action="/settings" method="get">
      Hostname:<br>
      <input type="text" name="hostname" value="%s"><br>
      <small><em>from 4 to 63 characters lenght, can contain chars, digits and '-'</em></small><br>
      <br>
      Power correction coefficient:<br>
      <input type="text" name="pcoef" value="%f"><br>
      <small><em>1.00 for no correction, [0.8, 1.2]</em></small><br>
      <br>
      Voltage correction coefficient:<br>
      <input type="text" name="vcoef" value="%f"><br>
      <small><em>1.00 for no correction, [0.8, 1.2]</em></small><br>
      <br>
      Voltage correction coefficient:<br>
      <input type="text" name="ccoef" value="%f"><br>
      <small><em>1.00 for no correction, [0.8, 1.2]</em></small><br>
      <br>
      <input type="submit" value="Save">
    </form> 	
  </BODY>
</HTML>
)=====";

const char GET_JSON[] PROGMEM = R"=====({
  "voltage":%.0f,
  "current":%.2f,
  "power":%.0f,
  "power_factor": %.2f
})=====";