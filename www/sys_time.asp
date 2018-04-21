<% asp_web_check_user(); %>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="style/doc.css" type="text/css">
<script defer type="text/javascript" src="js/pngfix.js"></script>
<script defer type="text/javascript" src="js/function.js"></script>
<script defer type="text/javascript" src="js/basic.js"></script>
<script language="javascript" src="js/calendar_cn.js" type="text/javascript"></script>
<title>设备管理</title>

<SCRIPT type=text/javascript >
function check_ip(obj)
{
	var value = obj.value;
	if(value.Trim() == "")
	{
		return false;
	}
	var retval = IsIpOk(value);
	if(retval == true)
	{
		return true;
	}
	else
	{
		obj.focus();
		obj.select();
		return false;
	}
	return true;
}
function getlocaltime()
{
    var today = new Date();
    var yearNow = today.getFullYear();
    var monthNow = today.getMonth()+1;
    var dateNow = today.getDate();
    var hourNow = today.getHours();
    var minNow = today.getMinutes();
    var secNow = today.getSeconds();

    if(monthNow<10) monthNow = "0" + monthNow;
    if(dateNow<10) dateNow = "0" + dateNow;
    if(hourNow<10) hourNow = "0" + hourNow;
    if(minNow<10) minNow = "0" + minNow;
    if(secNow<10) secNow = "0" + secNow;

    var time_str = yearNow + "-" + monthNow + "-" + dateNow + " "
    			   + hourNow + ":" + minNow + ":" + secNow;
    document.clock_form.time.value = time_str;
    return true;
}
function fun_chk_ntp()
{
	var obj_ntpip = document.getElementById('ntp_svrip');
	var obj_ntpenable = document.getElementById('ntp_enable');
	var obj_ntpinterval = document.getElementById('ntp_interval');
	
	if(obj_ntpenable.checked)
	{
		obj_ntpip.disabled = false;
		obj_ntpinterval.disabled = false;
	}
	else
	{
		obj_ntpip.disabled = true;
		obj_ntpinterval.disabled = true;
	}
}
function fun_setntp_submit()
{
	var obj_ntpip = document.getElementById('ntp_svrip');
	var obj_ntpenable = document.getElementById('ntp_enable');
	var obj_ntpinterval = document.getElementById('ntp_interval');
	
	var ntp_enable = 0;
	if( obj_ntpenable.checked )
	{
		ntp_enable = 1;
	}
	else
	{
		ntp_enable = 0;
	}
	
	var ntp_ip = obj_ntpip.value;
	if( obj_ntpenable.checked )
	{
		if(check_ip(obj_ntpip)==false || ntp_ip=="")
		{
			alert("NTP服务器设置错误！");
			obj_ntpip.focus();
			obj_ntpip.select();
			return false;
		}
	}
	else
	{
		if(ntp_ip=="")
		{
			ntp_ip=" ";
		}
	}
	
	var ntp_interval = obj_ntpinterval.value;
	if( isNaN(ntp_interval) || ntp_interval=="" || ntp_interval<1 || ntp_interval>600)
	{
		alert("校时间隔数值错误！");
		obj_ntpinterval.focus();
		obj_ntpinterval.select();
		return false;
	}

	var submit_str = ntp_enable + ";" + ntp_ip + ";" + ntp_interval + ";";
	document.getElementById('submit_ntp_str').value = submit_str;
	//
	// 界面显示控制
	document.getElementById('set_time_div').style.display="none";
	document.getElementById('setting_time_tip_div').style.display="block";
	return true;
}
function SetNtpInfo()
{
	var obj_ntpip = document.getElementById('ntp_svrip');
	var obj_ntpenable = document.getElementById('ntp_enable');
	var obj_ntpinterval = document.getElementById('ntp_interval');
	
	// "1;192.168.2.3;5;" 使能;NTP服务器IP;教室间隔
	var str = document.getElementById('get_ntp_str').value;
	var strs = new Array();
	strs = str.split(";");
	
	var ntp_enable = parseInt(strs[0]);
	var ntp_ip = strs[1];
	var ntp_interval = parseInt(strs[2]);
	
	if(ntp_enable == 1)
	{
		obj_ntpenable.checked = true;
	}
	else
	{
		obj_ntpenable.checked = false;
	}
	obj_ntpip.value = ntp_ip;
	obj_ntpinterval.value = ntp_interval;
	
	fun_chk_ntp();
}
function OnWebLoad()
{
	//设置NTP信息
	SetNtpInfo();
	return true;
}
</SCRIPT>

</head>

<BODY OnLoad="OnWebLoad()">
<div id="set_time_div" style="dispaly:block;">
<form id="clock_form" name="clock_form" action="/goform/form_set_time" method="post"> 
<table width="1080">
  <tr><td>
    <table>
    <tr>
      <td class="subtitle">设置时间</td>
    </tr>
	<tr><td><img src="images/break_bg.gif"></td></tr>
    </table>
  </td></tr>
  <tr><td>
    <table width="1080" border="0" cellpadding="6" align="left">
	  <tr>
        <td class="lable">时间</td>
        <td>
		<input type="text" size="24" value=<%asp_get_time();%>
		 id="time" name="time" onClick="SelectDate(this,'yyyy-MM-dd hh:mm:ss',0,0)" readonly />
		<input type="button" id="localtime" name="localtime" onClick="return getlocaltime();" value=" 同步本机时间 " />
		</td>
      </tr>
	  <tr >
        <td colspan="2"><input type="submit" name="submit" 
		style="border:none;background:url(images/save_btn.png);width:83px;height:20px;cursor:hand;" 
		value="" /></td>
	  </tr>
    </table>
  </td></tr>
</table>
</form>

<form id="ntp_form" name="ntp_form" action="/goform/form_set_ntp" method="post"> 
<input type="hidden" id="submit_ntp_str" name="submit_ntp_str" value="">
<input type="hidden" id="submit_ntp_str" name="get_ntp_str" value="<%asp_get_ntp();%>">
<table width="1080">
  <tr><td>
    <table>
    <tr>
      <td class="subtitle">NTP校时</td>
    </tr>
	<tr><td><img src="images/break_bg.gif"></td></tr>
    </table>
  </td></tr>
  <tr><td>
    <table width="1080" border="0" cellpadding="6" align="left">
	  <tr>
        <td class="lable">NTP校时使能</td>
        <td>
		<input type="checkbox" id="ntp_enable" name="ntp_enable"  value="" onClick="fun_chk_ntp()">
		</td>
      </tr>
	  <tr>
        <td class="lable">NTP服务器</td>
        <td>
		<input type="text" size="24" id="ntp_svrip" name="ntp_svrip" value="">
		</td>
      </tr>
<!--
	  <tr>
        <td class="lable">NTP端口</td>
        <td>
		<input type="text" size="24" id="ntp_port" name="ntp_port" value="">
		</td>
      </tr>
-->
	  <tr>
        <td class="lable">校时间隔</td>
        <td>
		<input type="text" size="12" id="ntp_interval" name="ntp_interval" value="">分钟(1-600)
		</td>
      </tr>
	  <tr>
        <td colspan="2"><input type="submit" name="submit_ntp_btn" 
		style="border:none;background:url(images/save_btn.png);width:83px;height:20px;cursor:hand;" 
		value="" onClick="return fun_setntp_submit();"/></td>
	  </tr>
    </table>
  </td></tr>
</table>
</form>
</div>

<div id="setting_time_tip_div" style="display:none;">
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