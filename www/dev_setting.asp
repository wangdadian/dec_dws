<% asp_web_check_user(); %>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="style/doc.css" type="text/css">
<script defer type="text/javascript" src="js/pngfix.js"></script>
<script defer type="text/javascript" src="js/function.js"></script>
<script defer type="text/javascript" src="js/basic.js"></script>
<title>�豸����</title>

<SCRIPT type=text/javascript >
function fun_dev_setting()
{
	/*if( ! confirm("�������ò������Ͽ�������ʱ�䣬�Ƿ������") )
	{
		return false;
	}*/
	var model = document.getElementById('model_list').selectedIndex;
	document.getElementById('submit_dev_model').value = model;

	document.getElementById('set_setting_div').style.display="none";
	document.getElementById('setting_setting_tip_div').style.display="block";
	return true;
}
function MyLoad()
{
	// �����豸����
	var model = document.getElementById('get_dev_model').value;
	var model_int = parseInt(model);
	document.getElementById('model_list').selectedIndex = model_int;
	//
}
function dev_restart_svr()
{
	document.getElementById('set_setting_div').style.display="none";
	document.getElementById('setting_setting_tip_div').style.display="block";
	return true;
}
</SCRIPT>

</head>

<BODY bgColor=#ffffff leftMargin=0 topMargin=0 marginheight="0" marginwidth="0" onLoad="MyLoad()">
<div id="set_setting_div" style="dispaly:block;">
<table width="1080">
  <tr><td>
    <table align="left">
      <tr>
        <td class="subtitle">�豸����</td>
      </tr>
	  <tr><td><img src="images/break_bg.gif"></td></tr>
    </table>
  </td></tr>
</table>
 
<form name="dev_setting_form" action="/goform/form_dev_setting" method=POST>
<input type="hidden" id="get_dev_model" name="get_dev_model" value="<%asp_get_dev_model();%>">
<input type="hidden" id="submit_dev_model" name="submit_dev_model" value="">
  <table width="1080">
	<tr>
	<td class="lable">�豸����</td>
	<td>
	  <select name="model_list" id="model_list" style="width: 120px;">
		<option value="0">�������</option>
	    <option value="1">�������</option>
		<option value="2">��Ƶ����</option>
        <option value="3">����&ת��</option>
	  </select>
	</td>
	</tr>
	<tr>
	  <td>
	    <input type="submit" name="dev_setting_submit" 
			style="border:none;background:url(images/save_btn.png);width:83px;height:20px;cursor:hand;" 
			onclick="return fun_dev_setting();" value=""/>
	  </td>
	  <td></td>
	</tr>
</table>
</form>

<form name="dev_restart_svr_form" action="/goform/form_restart_svr" method=POST>
<table width="1080">
  <tr><td>
    <table align="left">
      <tr>
        <td class="subtitle">��������</td>
      </tr>
	  <tr><td><img src="images/break_bg.gif"></td></tr>
    </table>
  </td></tr>
  <tr><td>
    <table border="0" cellpadding="6" align="left">
    <tr>
      <td><img src="images/tip_24.gif"><span>�Ƿ������������</span></td>
    </tr>
    <tr>
      <td>
        <input type="submit" name="dev_restart_svr_submit" onClick="return dev_restart_svr();" 
		style="border:none;background:url(images/ok_btn.png);width:83;height:20;cursor:hand;"  
		value=""/>
      </td>
    </tr>
    </table>
  </td></tr>
</table>
</form>

</div>
<div id="setting_setting_tip_div" style="display:none;">
<table>
	<tr>
		<td width="512" height="200" bgcolor="#FEF9E9" align="center">
			<img src="images/loading_01.gif">
			<br><br>
			����Ӧ����,�����ĵȴ����������ҳ......
		</td>
	</tr>
</table>
</div>

</body>
</html>