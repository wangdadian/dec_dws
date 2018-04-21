<% asp_web_check_user(); %>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="style/doc.css" type="text/css">
<script defer type="text/javascript" src="js/pngfix.js"></script>
<script defer type="text/javascript" src="js/function.js"></script>
<script defer type="text/javascript" src="js/basic.js"></script>
<title>设备管理</title>

<script type="text/javascript">
// 时间选择控件，不能单独放在js文件
var str = "";
document.writeln("<div id=\"_contents\" style=\"padding:6px; background-color:#E3E3E3; font-size: 12px; border: 1px solid #777777; position:absolute; left:?px; top:?px; width:?px; height:?px; z-index:1; visibility:hidden\">");
str += "\u65f6<select id=\"_hour\">";
for (h = 0; h <= 9; h++) {
    str += "<option value=\"0" + h + "\">0" + h + "</option>";
}
for (h = 10; h <= 23; h++) {
    str += "<option value=\"" + h + "\">" + h + "</option>";
}
str += "</select> \u5206<select id=\"_minute\">";
for (m = 0; m <= 9; m++) {
    str += "<option value=\"0" + m + "\">0" + m + "</option>";
}
for (m = 10; m <= 59; m++) {
    str += "<option value=\"" + m + "\">" + m + "</option>";
}
str += "</select> \u79d2<select id=\"_second\">";
for (s = 0; s <= 9; s++) {
    str += "<option value=\"0" + s + "\">0" + s + "</option>";
}
for (s = 10; s <= 59; s++) {
    str += "<option value=\"" + s + "\">" + s + "</option>";
}
str += "</select> <input name=\"queding\" type=\"button\" onclick=\"_select()\" value=\"\u786e\u5b9a\" style=\"font-size:12px\" /></div>";
document.writeln(str);
var _fieldname;
String.prototype.TrimFunc = function()
{
	return this.replace(/(^\s*)|(\s*$)/g, "");
}
function _setValue()
{
	var str_time = _fieldname.value;
	str_time = str_time.TrimFunc();
	//alert(str_time);
	if(str_time=="")
	{
		return false;
	}
	var arr_time = new Array();
	arr_time = str_time.split(":");
	if(arr_time.length < 3)
	{
		return false;
	}
	
	var hour = parseInt(arr_time[0]);
	var min  = parseInt(arr_time[1]);
	var sec  = parseInt(arr_time[2]);
	document.getElementById("_hour").selectedIndex = hour;
	document.getElementById("_minute").selectedIndex = min;
	document.getElementById("_second").selectedIndex = sec;
}

function _SetTime(tt) {
    _fieldname = tt;
    var ttop = tt.offsetTop;    //TT控件的定位点高
    var thei = tt.clientHeight;    //TT控件本身的高
    var tleft = tt.offsetLeft;    //TT控件的定位点宽
    while (tt = tt.offsetParent) {
        ttop += tt.offsetTop;
        tleft += tt.offsetLeft;
    }
    document.getElementById("_contents").style.top = ttop + thei + 4;
    document.getElementById("_contents").style.left = tleft;
    document.getElementById("_contents").style.visibility = "visible";
	_setValue();
}

function _select() {
    _fieldname.value = document.getElementById("_hour").value + ":" + document.getElementById("_minute").value + ":" + document.getElementById("_second").value;
    document.getElementById("_contents").style.visibility = "hidden";
}
</script>


<SCRIPT type=text/javascript >
function dev_reboot()
{
	if(confirm("即将重启设备，是否继续？"))
	{
		document.dev_reboot_form.target="_parent";
		location.href="rebooting.asp";
		return true;
	}
	else
	{
		return false;
	}
}

function dev_autoreboot()
{
	var obj_ar_type_list = document.getElementById('ar_type_list');
	var obj_ar_time = document.getElementById('ar_time');
	var obj_ar_enable = document.getElementById("ar_enable");
	var obj_ar_str = document.getElementById("submit_ar_str");
	
	var ar_enable = (obj_ar_enable.checked) ? 1 : 0;
	var ar_type = obj_ar_type_list.selectedIndex;
	var ar_time = obj_ar_time.value;
	
	// "1;1;2:00:00" 使能;模式;时间
	var submit_str = ar_enable + ";" + ar_type + ";" + ar_time + ";";
	obj_ar_str.value = submit_str;
	
	// 界面显示控制
	document.getElementById('set_reboot_div').style.display="none";
	document.getElementById('setting_ar_div').style.display="block";
	return true;
}

function fun_chk_ar()
{
	var obj_ar_type_list = document.getElementById('ar_type_list');
	var obj_ar_time = document.getElementById('ar_time');
	var obj_ar_enable = document.getElementById("ar_enable");
	
	if(obj_ar_enable.checked)
	{
		obj_ar_type_list.disabled = false;
		obj_ar_time.disabled = false;
	}
	else
	{
		obj_ar_type_list.disabled = true;
		obj_ar_time.disabled = true;
	}
	return true;
}

// 设置自动重启AR信息
function SetARInfo()
{
	var obj_ar_type_list = document.getElementById('ar_type_list');
	var obj_ar_time = document.getElementById('ar_time');
	var obj_ar_enable = document.getElementById("ar_enable");
	
	// "1;1;2:00:00" 使能;模式;时间
	var str = document.getElementById('get_ar_str').value;
	var strs = new Array();
	strs = str.split(";");
	if(strs.length < 3)
	{
		return false;
	}
	
	var ar_enable = parseInt(strs[0]);
	var ar_type = parseInt(strs[1]);
	var ar_time = strs[2]; 
	
	if(ar_enable == 1)
	{
		obj_ar_enable.checked = true;
	}
	else
	{
		obj_ar_enable.checked = false;
	}
	
	obj_ar_type_list.selectedIndex = ar_type;
	obj_ar_time.value = ar_time;
	
	return fun_chk_ar(); 
}

function OnWebLoad()
{
	//设置NTP信息
	SetARInfo();
	return true;
}
</SCRIPT>

</head>

<BODY bgColor=#ffffff leftMargin=0 topMargin=0 marginheight="0" marginwidth="0" onLoad="OnWebLoad()">
<div id="set_reboot_div" style="dispaly:block;">
<form name="dev_reboot_form" action="/goform/form_dev_reboot" method=POST>
<table width="1080">
  <tr><td>
    <table align="left">
      <tr>
        <td class="subtitle">设备重启</td>
      </tr>
	  <tr><td><img src="images/break_bg.gif"></td></tr>
    </table>
  </td></tr>
  <tr><td>
    <table border="0" cellpadding="6" align="left">
    <tr>
      <td><img src="images/tip_24.gif"><span>是否手动重启设备？</span></td>
    </tr>
    <tr>
      <td>
        <input type="submit" name="dev_reboot_submit" onClick="return dev_reboot();" 
		style="border:none;background:url(images/ok_btn.png);width:83px;height:20px;cursor:hand;"  
		value=""/>
      </td>
    </tr>
    </table>
  </td></tr>
</table>
</form>

<form name="dev_ar_form" action="/goform/form_ar" method=POST>
<input type="hidden" id="submit_ar_str" name="submit_ar_str" value="">
<input type="hidden" id="get_ar_str" name="get_ar_str" value="<%get_ar_info();%>">
<table width="1080">
  <tr><td>
    <table align="left">
      <tr>
        <td class="subtitle">自动重启</td>
      </tr>
	  <tr><td><img src="images/break_bg.gif"></td></tr>
    </table>
  </td></tr>
  <tr><td>
    <table border="0" cellpadding="6" cellspacing="8" align="left">
    <tr>
      <td colspan="3"><img src="images/tip_24.gif"><span>使能自动重启设置，并选择自动重启模式及时间。</span></td>
    </tr>
    <tr>
      <td>
        <input type="checkbox" id="ar_enable" name="ar_enable" value="" onClick="fun_chk_ar()">开启自动重启
      </td>
      <td>
        模式选择：
        <select name="ar_type_list" id="ar_type_list" style="width: 80px;">
		  <option value="0">每天</option>
	      <option value="1">每周一</option>
		  <option value="2">每周二</option>
          <option value="3">每周三</option>
          <option value="4">每周四</option>
          <option value="5">每周五</option>
          <option value="6">每周六</option>
          <option value="7">每周日</option>
	    </select>
      </td>
      <td>
        时间选择：
        <input type="text" size="10" value="02:00:00" id="ar_time" name="ar_time" onClick="_SetTime(this)" readonly />
      
      </td>
    </tr>
    <tr>
      <td colspan="3">
        <input type="submit" name="dev_ar_submit" onClick="return dev_autoreboot();" 
		style="border:none;background:url(images/save_btn.png);width:83px;height:20px;cursor:hand;"  
		value=""/>
      </td>
    </tr>
    </table>
  </td></tr>
</table>
</form>
</div>

<div id="setting_ar_div" style="display:none;">
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