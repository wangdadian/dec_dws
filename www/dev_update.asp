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
 
function Upgrade_Confirm()
{
    var msg = "升级后系统需要重启生效，是否继续？";
	if( confirm(msg) )
	{	
		document.getElementById('update_div').style.display="none";
		document.getElementById('updating_tip_div').style.display="block";
		return true;
	}
    return false;
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

<div id="update_div">
<table width="1080" border="0">
  <tr>
    <td>
      <table align="left">
        <tr>
          <td class="subtitle">设备升级</td>
        </tr>
	    <tr>
          <td>
            <img src="images/break_bg.gif">
          </td>
        </tr>
      </table>
    </td>
  </tr>
  <tr>
    <td>
      <table border="0" cellpadding="6" align="left">
      <tr>
	  <form action="/goform/form_dev_update" method=POST enctype="multipart/form-data">
        <td class="lable">选择升级文件</td>
        <td>
          <input type="file" id="dev_update_file" name="dev_update_file" size=40 accept=".img" value=""/>
        </td>
      </tr>
      <tr>
        <td>
          <input type="submit" name="dev_update_submit" 
		style="border:none;background:url(images/upgrade_btn.png);width:83px;height:20px;cursor:hand;" 
		onclick="return Upgrade_Confirm();" value=""/>
        </td>
	  </form>

	  <form name="dev_reboot_form" action="/goform/form_dev_reboot" method=POST>
	    <td >
          <input type="submit" name="dev_reboot_submit" 
		style="border:none;background:url(images/reboot_btn.png);width:83px;height:20px;cursor:hand;" 
		onclick="return dev_reboot();" value=""/>
        </td>
	  </form>
	  </tr>
      </table>
    </td>
  </tr>
</table>
<br>
<br>
<span style="color:#FF0000;font-weight:bold;"><%asp_get_upgrade_ret();%></span>
</div>

<div id="updating_tip_div" style="display:none;">
<table>
	<tr>
		<td width="512" height="200" bgcolor="#FEF9E9" align="center">
			<img src="images/loading_01.gif">
			<br><br>
			设备升级中，这大概需要5分钟时间。<br>
			请耐心等待，切勿操作网页......
		</td>
	</tr>
</table>
</div>

</body>
</html>