<% asp_web_check_user(); %>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="style/doc.css" type="text/css">
<script defer type="text/javascript" src="js/pngfix.js"></script>
<script defer type="text/javascript" src="js/function.js"></script>
<script defer type="text/javascript" src="js/basic.js"></script>
<title>设备管理</title>

<SCRIPT type=text/javascript >
function to_reset()
{
	if( ! confirm("即将重设参数并自动重启设备，是否继续？") )
	{
		return false;
	}

	document.getElementById('set_reset_div').style.display="none";
	document.getElementById('setting_reset_tip_div').style.display="block";
	document.dev_reboot_form.target="_parent";
	//document.form_reset.submit();
	return true;
}
function dev_reboot()
{
	if(confirm("即将重启设备，是否继续？"))
	{
		document.dev_reboot_form.target="_parent";
		return true;
	}
	else
	{
		return false;
	}
}
</SCRIPT>

</head>

<BODY bgColor=#ffffff leftMargin=0 topMargin=0 marginheight="0" marginwidth="0">
<div id="set_reset_div" style="display:block;">

<table width="1080">
  <tr><td>
    <table align="left" width="1080">
      <tr>
        <td class="subtitle">参数重置</td>
      </tr>
	  <tr><td><img src="images/break_bg.gif"></td></tr>
    </table>
  </td></tr>
  <tr><td>
    <table width="1080" border="0" cellpadding="6" align="left">
    <tr>
        <td colspan="2"><img src="images/tip_24.gif"><span class="span_tip">将所有参数恢复成出厂默认?</span></td>
    </tr>
    <tr>
	<form name="form_reset" action="/goform/form_dev_reset" method=POST>
	<td>
        <input type="submit" name="dev_reset_submit" 
		style="border:none;background:url(images/ok_btn.png);width:83px;height:20px;cursor:hand;" 
		onclick="return to_reset();"value=""/>
    </td>
	</form>
	<form name="dev_reboot_form" action="/goform/form_dev_reboot" method=POST>
	<td >
	<!--
        <input type="submit" name="dev_reboot_submit" 
		style="border:none;background:url(images/reboot_btn.png);width:83;height:20;cursor:hand;" 
		onclick="return dev_reboot();" value=""/>
	-->
    </td>
	</form>
	</tr>    
    </table>
  </td></tr>
</table>
</div>

<div id="setting_reset_tip_div" style="display:none;">
<table>
	<tr>
		<td width="512" height="200" bgcolor="#FEF9E9" align="center">
			<img src="images/loading_01.gif">
			<br><br>
			正在应用中,请稍等，勿操作网页......
		</td>
	</tr>
</table>
</div>
</body>
</html>