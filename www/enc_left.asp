<% asp_web_check_user(); %>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="style/doc.css" type="text/css">
<title>�豸����</title>
<SCRIPT type=text/javascript >
function select_display()
{
	// ��ʾ����
	document.getElementById("a_display").className="a_left_menu_sel";
	document.getElementById("a_video").className="a_left_menu";
	document.getElementById("a_transfer").className="a_left_menu";
	document.getElementById("a_alarm").className="a_left_menu";
	document.getElementById("a_channel").className="a_left_menu";
}

function select_video()
{
	// ��ʾ����
	document.getElementById("a_display").className="a_left_menu";
	document.getElementById("a_video").className="a_left_menu_sel";
	document.getElementById("a_transfer").className="a_left_menu";
	document.getElementById("a_alarm").className="a_left_menu";
	document.getElementById("a_channel").className="a_left_menu";
}

function select_transfer()
{
	// ��ʾ����
	document.getElementById("a_display").className="a_left_menu";
	document.getElementById("a_video").className="a_left_menu";
	document.getElementById("a_transfer").className="a_left_menu_sel";
	document.getElementById("a_alarm").className="a_left_menu";
	document.getElementById("a_channel").className="a_left_menu";
}
function select_alarm()
{
	// ��ʾ����
	document.getElementById("a_display").className="a_left_menu";
	document.getElementById("a_video").className="a_left_menu";
	document.getElementById("a_transfer").className="a_left_menu";
	document.getElementById("a_alarm").className="a_left_menu_sel";
	document.getElementById("a_channel").className="a_left_menu";
}
function select_channel()
{
	// ��ʾ����
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
		<img src="images/menu_bar.gif"/>&nbsp;<a id="a_channel" name="a_channel" onClick="select_channel()" href="enc_channel.asp" class="a_left_menu" target="sysMainFrame">ͨ������</a>
	</TD>
</TR>
<TR>
    <TD width="10%"><TD>
	<TD class="leftmenu">
		<img src="images/menu_bar.gif"/>&nbsp;<a id="a_display" name="a_display" onClick="select_display()" href="enc_display.asp" class="a_left_menu" target="sysMainFrame">�ַ���ʾ����</a>
	</TD>	
</TR>

<TR>
    <TD width="10%"><TD>

	<TD class="leftmenu">
		<img src="images/menu_bar.gif"/>&nbsp;<a id="a_video" name="a_video" onClick="select_video()" href="enc_video.asp" class="a_left_menu" target="sysMainFrame">��Ƶ����</a>
	</TD>
</TR>
<TR>
    <TD width="10%"><TD>

	<TD class="leftmenu">
		<img src="images/menu_bar.gif"/>&nbsp;<a id="a_transfer" name="a_transfer" onClick="select_transfer()" href="enc_transfer.asp" class="a_left_menu" target="sysMainFrame">������������</a>
	</TD>
</TR>
<TR>
    <TD width="10%"><TD>

	<TD class="leftmenu">
		<img src="images/menu_bar.gif"/>&nbsp;<a id="a_alarm" name="a_alarm" onClick="select_alarm()" href="enc_alarm.asp" class="a_left_menu" target="sysMainFrame">��������</a>
	</TD>
</TR>

<tr><td height="100%"></td></tr>
</table>
</body>
</html>

