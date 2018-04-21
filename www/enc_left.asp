<% asp_web_check_user(); %>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="style/doc.css" type="text/css">
<title>设备管理</title>
<SCRIPT type=text/javascript >
function select_display()
{
	// 显示界面
	document.getElementById("a_display").className="a_left_menu_sel";
	document.getElementById("a_video").className="a_left_menu";
	document.getElementById("a_transfer").className="a_left_menu";
	document.getElementById("a_alarm").className="a_left_menu";
	document.getElementById("a_channel").className="a_left_menu";
}

function select_video()
{
	// 显示界面
	document.getElementById("a_display").className="a_left_menu";
	document.getElementById("a_video").className="a_left_menu_sel";
	document.getElementById("a_transfer").className="a_left_menu";
	document.getElementById("a_alarm").className="a_left_menu";
	document.getElementById("a_channel").className="a_left_menu";
}

function select_transfer()
{
	// 显示界面
	document.getElementById("a_display").className="a_left_menu";
	document.getElementById("a_video").className="a_left_menu";
	document.getElementById("a_transfer").className="a_left_menu_sel";
	document.getElementById("a_alarm").className="a_left_menu";
	document.getElementById("a_channel").className="a_left_menu";
}
function select_alarm()
{
	// 显示界面
	document.getElementById("a_display").className="a_left_menu";
	document.getElementById("a_video").className="a_left_menu";
	document.getElementById("a_transfer").className="a_left_menu";
	document.getElementById("a_alarm").className="a_left_menu_sel";
	document.getElementById("a_channel").className="a_left_menu";
}
function select_channel()
{
	// 显示界面
	document.getElementById("a_display").className="a_left_menu";
	document.getElementById("a_video").className="a_left_menu";
	document.getElementById("a_transfer").className="a_left_menu";
	document.getElementById("a_alarm").className="a_left_menu";
	document.getElementById("a_channel").className="a_left_menu_sel";
}
</SCRIPT>
</head>

<BODY onload="select_channel()">
	
<TABLE width="200"  height="100%" border=0 bgcolor="707684">
<TR>
    <TD width="10%"><TD>
	<TD height="12">
	</TD>
</TR>
<TR>
    <TD width="10%"><TD>

	<TD class="leftmenu">
		<img src="images/menu_bar.gif"/>&nbsp;<a id="a_channel" name="a_channel" onClick="select_channel()" href="enc_channel.asp" class="a_left_menu" target="sysMainFrame">通道设置</a>
	</TD>
</TR>
<TR>
    <TD width="10%"><TD>
	<TD class="leftmenu">
		<img src="images/menu_bar.gif"/>&nbsp;<a id="a_display" name="a_display" onClick="select_display()" href="enc_display.asp" class="a_left_menu" target="sysMainFrame">字符显示设置</a>
	</TD>	
</TR>

<TR>
    <TD width="10%"><TD>

	<TD class="leftmenu">
		<img src="images/menu_bar.gif"/>&nbsp;<a id="a_video" name="a_video" onClick="select_video()" href="enc_video.asp" class="a_left_menu" target="sysMainFrame">视频设置</a>
	</TD>
</TR>
<TR>
    <TD width="10%"><TD>

	<TD class="leftmenu">
		<img src="images/menu_bar.gif"/>&nbsp;<a id="a_transfer" name="a_transfer" onClick="select_transfer()" href="enc_transfer.asp" class="a_left_menu" target="sysMainFrame">码流传输设置</a>
	</TD>
</TR>
<TR>
    <TD width="10%"><TD>

	<TD class="leftmenu">
		<img src="images/menu_bar.gif"/>&nbsp;<a id="a_alarm" name="a_alarm" onClick="select_alarm()" href="enc_alarm.asp" class="a_left_menu" target="sysMainFrame">报警设置</a>
	</TD>
</TR>

<tr><td height="100%"></td></tr>
</table>
</body>
</html>

