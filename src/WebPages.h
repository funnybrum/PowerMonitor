#define PROGMEM ICACHE_RODATA_ATTR

const char CONFIG_PAGE[] PROGMEM = R"=====(
<HTML>
	<HEAD>
      <TITLE>%s power monitor</TITLE>
	</HEAD>
  <BODY>
    <form action="/settings" method="get">
      %s<br><br>
      %s<br><br>
      <fieldset style='display: inline-block; width: 300px'>
        <legend>Power sensor settings</legend>
        Power correction coefficient:<br> 
        <input type="text" name="pcoef" value="%f"><br>
        <small><em>1.00 for no correction, [0.8, 1.2]</em></small><br><br>
        Voltage correction coefficient:<br>
        <input type="text" name="vcoef" value="%f"><br>
        <small><em>1.00 for no correction, [0.8, 1.2]</em></small><br><br>
        Voltage correction coefficient:<br>
        <input type="text" name="ccoef" value="%f"><br>
        <small><em>1.00 for no correction, [0.8, 1.2]</em></small><br><br>
      </fieldset>
      <br><br>
      <input type="submit" value="Save" style='width: 150px;'>
      &nbsp;&nbsp;&nbsp;
      <a href="/reboot">
        <button type="button" style='width: 150px;'>Restart</button>
      </a>
    </form>
  </BODY>
</HTML>
)=====";

const char GET_JSON[] PROGMEM = R"=====({
  "voltage":%.1f,
  "current":%.2f,
  "power":%.1f,
  "power_factor": %.2f
})=====";