<% asp_web_check_user(); %>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="style/doc.css" type="text/css">
<title>设备管理</title>
<SCRIPT type=text/javascript >
function select_setting()
{
	// 显示界面
	document.getElementById("a_setting").className="a_left_menu_sel";
	document.getElementById("a_state").className="a_left_menu";
	document.getElementById("a_ping").className="a_left_menu";
	document.getElementById("a_reset").className="a_left_menu";
	document.getElementById("a_upgrade").className="a_left_menu";
	document.getElementById("a_reboot").className="a_left_menu";
}
function select_state()
{
	// 显示界面
	document.getElementById("a_setting").className="a_left_menu";
	document.getElementById("a_state").className="a_left_menu_sel";
	document.getElementById("a_ping").className="a_left_menu";
	document.getElementById("a_reset").className="a_left_menu";
	document.getElementById("a_upgrade").className="a_left_menu";
	document.getElementById("a_reboot").className="a_left_menu";
}
function select_ping()
{
	// 显示界面
	document.getElementById("a_setting").className="a_left_menu";
	document.getElementById("a_state").className="a_left_menu";
	document.getElementById("a_ping").className="a_left_menu_sel";
	document.getElementById("a_reset").className="a_left_menu";
	document.getElementById("a_upgrade").className="a_left_menu";
	document.getElementById("a_reboot").className="a_left_menu";
}
function select_reset()
{
	// 显示界面
	document.getElementById("a_setting").className="a_left_menu";
	document.getElementById("a_state").className="a_left_menu";
	document.getElementById("a_ping").className="a_left_menu";
	document.getElementById("a_reset").className="a_left_menu_sel";
	document.getElementById("a_upgrade").className="a_left_menu";
	document.getElementById("a_reboot").className="a_left_menu";
}
function select_upgrade()
{
	// 显示界面
	document.getElementById("a_setting").className="a_left_menu";
	document.getElementById("a_state").className="a_left_menu";
	document.getElementById("a_ping").className="a_left_menu";
	document.getElementById("a_reset").className="a_left_menu";
	document.getElementById("a_upgrade").className="a_left_menu_sel";
	document.getElementById("a_reboot").className="a_left_menu";
}
function select_reboot()
{
	// 显示界面
	document.getElementById("a_setting").className="a_left_menu";
	document.getElementById("a_state").className="a_left_menu";
	document.getElementById("a_ping").className="a_left_menu";
	document.getElementById("a_reset").className="a_left_menu";
	document.getElementById("a_upgrade").className="a_left_menu";
	document.getElementById("a_reboot").className="a_left_menu_sel";
}
</SCRIPT>
</head>

<BODY onLoad="select_setting()">
	
<TABLE width="200"  height="100%" border=0 bgcolor="707684">
<TR>
    <TD width="10%"><TD>
	<TD height="12">
	</TD>
</TR>
<TR>
    <TD width="10%"><TD>
	<TD class="leftmenu">
	<img src="images/menu_bar.gif"/>&nbsp;<a id="a_setting" name="a_setting" onClick="select_setting()" href="dev_setting.asp" class="a_left_menu" target="sysMainFrame">设备管理</a>
	</TD>
</TR>
<TR>
    <TD width="10%"><TD>
	<TD class="leftmenu">
	<img src="images/menu_bar.gif"/>&nbsp;<a id="a_state" name="a_state" onClick="select_state()" href="dev_state.asp" class="a_left_menu" target="sysMainFrame">设备状态</a>
	</TD>
</TR>
<TR>
    <TD width="10%"><TD>
	<TD class="leftmenu">
	<img src="images/menu_bar.gif"/>&nbsp;<a id="a_ping" name="a_ping" onClick="select_ping()" href="dev_ping.asp?ping_ip=" class="a_left_menu" target="sysMainFrame">ping测试</a>
	</TD>
</TR>
<TR>
    <TD width="10%"><TD>
	<TD class="leftmenu">
	<img src="images/menu_bar.gif"/>&nbsp;<a id="a_reset" name="a_reset" onClick="select_reset()" href="dev_reset.asp" class="a_left_menu" target="sysMainFrame">参数重置</a>
	</TD>
</TR>
<TR>
    <TD width="10%"><TD>
	<TD class="leftmenu">
	<img src="images/menu_bar.gif"/>&nbsp;<a id="a_upgrade" name="a_upgrade" onClick="select_upgrade()" href="dev_update.asp" class="a_left_menu" target="sysMainFrame">设备升级</a>
	</TD>
</TR>

<TR>
    <TD width="10%"><TD>
	<TD class="leftmenu">
	<img src="images/menu_bar.gif"/>&nbsp;<a id="a_reboot" name="a_reboot" onClick="select_reboot()" href="dev_reboot.asp" class="a_left_menu" target="sysMainFrame">设备维护</a>
	</TD>
</TR>

<tr><td height="100%"></td></tr>
</table>
</body>
</html>