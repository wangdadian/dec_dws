<% asp_web_check_user(); %>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="style/doc.css" type="text/css">
<title>设备管理</title>
<SCRIPT type=text/javascript >
function select_chnset()
{
	// 显示界面
	document.getElementById("a_chnset").className="a_left_menu_sel";
	document.getElementById("a_dyn").className="a_left_menu";
    document.getElementById("a_res").className="a_left_menu";
}
function select_res()
{
	// 显示界面
    document.getElementById("a_chnset").className="a_left_menu";
	document.getElementById("a_res").className="a_left_menu_sel";
	document.getElementById("a_dyn").className="a_left_menu";
}

function select_dyn()
{
	// 显示界面
    document.getElementById("a_chnset").className="a_left_menu";
	document.getElementById("a_res").className="a_left_menu";
	document.getElementById("a_dyn").className="a_left_menu_sel";
}

</SCRIPT>
</head>

<BODY onload="select_res()">
	
<TABLE width="200"  height="100%" border=0 bgcolor="707684">
<TR>
    <TD width="10%"><TD>
	<TD height="12">
	</TD>
</TR>

<TR>
    <TD width="10%"><TD>
	<TD class="leftmenu">
		<img src="images/menu_bar.gif"/>&nbsp;<a id="a_chnset" name="a_chnset" onClick="select_chnset()" href="dec_channelset.asp" class="a_left_menu" target="sysMainFrame">通道设置</a>
	</TD>	
</TR>

<TR>
    <TD width="10%"><TD>
	<TD class="leftmenu">
		<img src="images/menu_bar.gif"/>&nbsp;<a id="a_res" name="a_res" onClick="select_res()" href="dec_resolution.asp" class="a_left_menu" target="sysMainFrame">分辨率设置</a>
	</TD>	
</TR>

<TR>
    <TD width="10%"><TD>

	<TD class="leftmenu">
		<img src="images/menu_bar.gif"/>&nbsp;<a id="a_dyn" name="a_dyn" onClick="select_dyn()" href="dec_dynamic.asp" class="a_left_menu" target="sysMainFrame">动态解码</a>
	</TD>
</TR>
<tr><td height="100%"></td></tr>
</table>
</body>
</html>

