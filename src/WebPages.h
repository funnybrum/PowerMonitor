#include "PowerMonitor.h"

const char CONFIG_PAGE[] PROGMEM = R"=====(
<HTML>
	<HEAD>
      <TITLE>%s power monitor</TITLE>
	</HEAD>
  <BODY>
    <form action="/settings" method="get">
      %s<br><br>
      %s<br><br>
      %s<br><br>
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