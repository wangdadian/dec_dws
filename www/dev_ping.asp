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
function fun_dev_ping()
{
	document.getElementById('ping_dev_div').style.display="none";
	document.getElementById('ping_dev_tip_div').style.display="block";
	return true;
}
function MyLoad()
{
	var gets=new Array;
	gets = getArgs();
	document.getElementById('host_ip').value = gets["ping_ip"];

	// 设置设备类型
	var model = document.getElementById('get_dev_model').value;
	var model_int = parseInt(model);
	document.getElementById('model_list').selectedIndex = model_int;
	//
}
</SCRIPT>

</head>

<BODY bgColor=#ffffff leftMargin=0 topMargin=0 marginheight="0" marginwidth="0" onLoad="MyLoad()">
<div id="ping_dev_div" style="dispaly:block;">
<table width="1080">
  <tr><td>
    <table align="left">
      <tr>
        <td class="subtitle">ping测试</td>
      </tr>
	  <tr><td><img src="images/break_bg.gif"></td></tr>
    </table>
  </td></tr>
</table>

<form name="dev_ping_form" action="/goform/form_dev_ping" method=POST>
<table width="1080">
	<tr>
	<td class="lable">对端IP地址</td>
	<td>
	  <input type="text" id="host_ip" name="host_ip" maxlength="15" size="20" value="" />
	  <input type="submit" name="dev_ping_submit" 
			style="border:none;background:url(images/ok_btn.png);width:83px;height:20px;cursor:hand;" 
			onclick="return fun_dev_ping();" value=""/>
	</td>
	</tr>
</table>
<table width="1080">
	<tr>
	  <td>
	  <pre style="font:14px;color:#666666;"><%get_ping_ret();%></pre>
	  </td>
	</tr>
</table>
</form>
</div>
<div id="ping_dev_tip_div" style="display:none;">
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