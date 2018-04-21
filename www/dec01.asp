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
function onclick_sysinfo()
{
	var obj_name = document.getElementById('dev_name');
	var obj_mac = document.getElementById('dev_mac');
	var value_hostname = obj_name.value;
	var value_mac = obj_mac.value;
	// 去掉两边空格
	value_hostname = value_hostname.Trim();
	value_mac = value_mac.Trim();
	if( IsHostnameOk(value_hostname) == false )
	{
		alert("主机名称错误！");
		obj_name.focus();
		obj_name.select();
		return false;
	}
	if( IsMacOk(value_mac) == false )
	{
		alert("设备地址错误！");
		obj_mac.focus();
		obj_mac.select();
		return false;
	}
	//if( confirm("即将设置系统信息，是否继续？") )
	{
		obj_name.value = value_hostname;
		obj_mac.value=value_mac;
		document.getElementById('set_dec_div').style.display="none";
		document.getElementById('setting_dec_tip_div').style.display="block";
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
function MACtobig()
{
	document.getElementById("dev_mac").value=document.getElementById("dev_mac").value.toUpperCase();
}

</SCRIPT>

</head>

<BODY bgColor=#ffffff leftMargin=0 topMargin=0 marginheight="0" marginwidth="0">
<div id="set_dec_div" style="dispaly:block;">
<table width="1080">
  <tr><td>
    <table align="left" width="1080">
      <tr>
        <td class="subtitle">系统信息</td>
      </tr>
	  <tr>
        <td><img src="images/break_bg.gif"></td>
      </tr>
    </table>
  </td></tr>
  <tr><td>
    <table width="1080" border="0" cellpadding="6" align="left">
	<form action="/goform/form_set_sysinfo" method=POST>
	<input type="hidden" id="pathname" name="pathname" value="dec01.asp">
	<tr>
	  <td class="lable">设备名称</td>
      <td>
        <input type="text" id="dev_name" name="dev_name" disabled="disabled" readonly value=<%asp_get_dev_hostname();%> size="32" />
      </td>
    </tr>
    <tr>	
      <td class="lable">设备地址</td>
      <td>
        <input type="text" id="dev_mac"  name="dev_mac" onBlur="MACtobig()" value="<%asp_get_dev_mac();%>" size="32" />
      </td>
    </tr>
	<tr>
      <td class="lable">设备序列号</td>
      <td>
        <input type="text" id="dev_sn" name="dev_sn"  value="<%asp_get_dev_sn();%>" size="32" />
      </td>
    </tr>
<!--
    <tr>
      <td class="lable">设备型号</td>
      <td>
        <input type="text" id="dev_model" name="dev_model" disabled="disabled" readonly="readonly" value="<asp_get_dev_model();>" size="32" />
      </td>
    </tr>
-->
    <tr>
      <td class="lable">主控版本</td>
      <td>
        <input type="text" id="dev_ver" name="dev_ver" disabled="disabled" readonly value="<%asp_get_dev_ver();%>" size="32" />
      </td>
    </tr>
	<tr>
      <td class="lable">创建时间</td>
      <td>
        <input type="text" id="dev_buildtime" name="dev_buildtime" disabled="disabled" readonly value="<%asp_get_dev_buildtime();%>" size="32" />
      </td>
    </tr>
    <tr>
      <td >
        <input type="submit" name="sysinfo_submit" 
		style="border:none;background:url(images/save_btn.png);width:83px;height:20px;cursor:hand;" 
		onclick="return onclick_sysinfo();" value=""/>
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
<br><br>
<span style="color:#FF0000;font-weight:bold;"><%asp_get_sysinfo_ret();%></span>
</div>

<div id="setting_dec_tip_div" style="display:none;">
<table>
	<tr>
		<td width="512" height="200" bgcolor="#FEF9E9" align="center">
			<img src="images/loading_01.gif">
			<br><br>
			正在应用中,请耐心等待，勿操作网页......
		</td>
	</tr>
</table>
</div>

</body>
</html>