<% asp_web_check_user(); %>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="style/doc.css" type="text/css">
<title>设备管理</title>

<SCRIPT type=text/javascript >
function select_sysinfo()
{
	// 显示界面
	document.getElementById("a_sysinfo").className="a_left_menu_sel";
	document.getElementById("a_time").className="a_left_menu";
	document.getElementById("a_network").className="a_left_menu";
	//document.getElementById("a_serialport").className="a_left_menu";
	document.getElementById("a_user").className="a_left_menu";
}
function select_time()
{
	// 显示界面
	document.getElementById("a_sysinfo").className="a_left_menu";
	document.getElementById("a_time").className="a_left_menu_sel";
	document.getElementById("a_network").className="a_left_menu";
	//document.getElementById("a_serialport").className="a_left_menu";
	document.getElementById("a_user").className="a_left_menu";
}
function select_network()
{
	// 显示界面
	document.getElementById("a_sysinfo").className="a_left_menu";
	document.getElementById("a_time").className="a_left_menu";
	document.getElementById("a_network").className="a_left_menu_sel";
	//document.getElementById("a_serialport").className="a_left_menu";
	document.getElementById("a_user").className="a_left_menu";
}
function select_serialport()
{
	// 显示界面
	document.getElementById("a_sysinfo").className="a_left_menu";
	document.getElementById("a_time").className="a_left_menu";
	document.getElementById("a_network").className="a_left_menu";
	//document.getElementById("a_serialport").className="a_left_menu_sel";
	document.getElementById("a_user").className="a_left_menu";
}
function select_user()
{
	// 显示界面
	document.getElementById("a_sysinfo").className="a_left_menu";
	document.getElementById("a_time").className="a_left_menu";
	document.getElementById("a_network").className="a_left_menu";
	//document.getElementById("a_serialport").className="a_left_menu";
	document.getElementById("a_user").className="a_left_menu_sel";
}
</SCRIPT>

</head>

<BODY onload="select_sysinfo()">
	
<TABLE width="200"  height="100%" border=0 bgcolor="707684">
<TR>
    <TD width="10%"><TD>
	<TD height="12">
	</TD>
</TR>
<TR>
    <TD width="10%"><TD>
	<TD class="leftmenu">
	<img src="images/menu_bar.gif"/>&nbsp;<a id="a_sysinfo" name="a_sysinfo" onClick="select_sysinfo()"  href="sys_info.asp" class="a_left_menu" target="sysMainFrame">系统信息</a>
	</TD>
</TR>
<TR>
    <TD width="10%"><TD>
	<TD class="leftmenu">
	<img src="images/menu_bar.gif"/>&nbsp;<a id="a_time" name="a_time" onClick="select_time()" href="sys_time.asp" class="a_left_menu" target="sysMainFrame">时间设置</a>
	</TD>
</TR>
<TR>
    <TD width="10%"><TD>
	<TD class="leftmenu">
	<img src="images/menu_bar.gif"/>&nbsp;<a id="a_network" name="a_network" onClick="select_network()" href="sys_network.asp" class="a_left_menu" target="sysMainFrame">网络设置</a>
	</TD>
</TR>
<!--
<TR>
    <TD width="10%"><TD>
	<TD class="leftmenu">
	<img src="images/menu_bar.gif"/>&nbsp;<a id="a_serialport" name="a_serialport" onClick="select_serialport()"  href="serialport.asp" class="a_left_menu" target="sysMainFrame">串口设置</a>
	</TD>
</TR>
-->
<TR>
    <TD width="10%"><TD>
	<TD class="leftmenu">
	<img src="images/menu_bar.gif"/>&nbsp;<a id="a_user" name="a_user" onClick="select_user()"  href="sys_user.asp" class="a_left_menu" target="sysMainFrame">用户管理</a>
	</TD>
</TR>

<tr><td height="100%"></td></tr>
</table>
</body>
</html>