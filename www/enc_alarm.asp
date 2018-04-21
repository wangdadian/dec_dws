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
function fun_enc_alarm_submit()
{
	var obj_alarmin_no = document.getElementById("enc_alarmin_no");
	var obj_alarmout_no = document.getElementById("enc_alarmout_no");
	var obj_alarmin_enable = document.getElementById("chk_enablealarm");
	var obj_alarmin_id = document.getElementById("alarminid");
	var obj_alarmin_type = document.getElementById("enc_alarmtype");
	var obj_alarmout_stable = document.getElementById("stabletime");
	var obj_alarmout_id = document.getElementById("alarmoutid");
	var obj_alarmin_delay = document.getElementById("outdelay");
	var submit_str = "";
	
	var alarmin_no = obj_alarmin_no.selectedIndex + 1;
	var alarmin_enable = 0;
	if(obj_alarmin_enable.checked == true)
	{
		alarmin_enable = 1;
	}
	else
	{
		alarmin_enable = 0;
	}
	var alarmin_id = obj_alarmin_id.value;
	if( alarmin_id == "" )
	{
		alarmin_id = " ";
	}
	var alarmin_type = obj_alarmin_type.selectedIndex;
	var alarmin_stable = obj_alarmout_stable.value;
	if(isNaN(alarmin_stable) || alarmin_stable<0 || alarmin_stable>600)
	{
		alert("ȥ����ʱ����ֵ��Χ��0-600");
		obj_alarmout_stable.focus();
		obj_alarmout_stable.select();
		return false;
	}
	var alarmin_out = obj_alarmout_no.selectedIndex;
	if(alarmin_out == 0)
		alarmin_out = -1;
	var alarmout_id = obj_alarmout_id.value;
	if(alarmout_id=="")
		alarmout_id = " ";
	var alarmin_delay = obj_alarmin_delay.value;
	if(isNaN(alarmin_delay) || alarmin_delay<0 || alarmin_delay>300)
	{
		alert("�����ʱ��ֵ��Χ��0-300");
		obj_alarmin_delay.focus();
		obj_alarmin_delay.select();
		return false;
	}
	// "1;1;10000000000001;1;100;1;20000000000001;10;";
	//��������ͨ����;�Ƿ�ʹ��;���;����;ȥ����ʱ��;�����������ͨ����;�������ͨ�����;�����ʱʱ��;
	submit_str = alarmin_no + ";" + alarmin_enable + ";" + alarmin_id + ";" + alarmin_type + ";" + alarmin_stable + ";";
	submit_str += alarmin_out + ";" + alarmout_id + ";" + alarmin_delay + ";";
	
	document.getElementById("submit_str").value = submit_str;
	// ������ʾ����
	document.getElementById('set_alarm_div').style.display="none";
	document.getElementById('setting_alarm_tip_div').style.display="block";
	return true;
}
function OnAlarmoutnoChange()
{
	var obj_alarmout_no = document.getElementById("enc_alarmout_no");
	var alarmout_no  = obj_alarmout_no.selectedIndex;
	onSelectAlarmoutno(alarmout_no);
}
function onSelectAlarmoutno(num)
{
	var obj_alarmout_no = document.getElementById("enc_alarmout_no");
	var obj_alarmout_id = document.getElementById("alarmoutid");
	var obj_alarmin_enable = document.getElementById("chk_enablealarm");
	
	if(num <= 0)
	{
		obj_alarmout_id.value = " ";
		obj_alarmout_id.disabled = true;
		return;
	}
	var obj_str = "alarmout_" + num + "_str";
	// "1;1;20000000000001";//�������ͨ����;�Ƿ�ʹ��;���;
	var str = document.getElementById(obj_str).value;
	
	var strs = new Array();
	strs = str.split(";");
	
	//�������ͨ����
	
	//�Ƿ�ʹ��
	var alarmout_enable = parseInt(strs[1]);
	//���
	var alarmout_id = strs[2];
	
	obj_alarmout_id.value = alarmout_id;
	if( obj_alarmin_enable.checked == false )
	{
		obj_alarmout_id.disabled = true;
	}
	else
	{
		obj_alarmout_id.disabled = false;
	}
}
function OnEnableAlarmin()
{
	var obj_alarmout_no = document.getElementById("enc_alarmout_no");
	var obj_alarmin_enable = document.getElementById("chk_enablealarm");
	var obj_alarmin_id = document.getElementById("alarminid");
	var obj_alarmin_type = document.getElementById("enc_alarmtype");
	var obj_alarmout_stable = document.getElementById("stabletime");
	var obj_alarmout_id = document.getElementById("alarmoutid");
	var obj_alarmin_delay = document.getElementById("outdelay");
	
	//������ʾ����
	if( obj_alarmin_enable.checked == false )
	{
		obj_alarmout_no.disabled = true;
		obj_alarmin_id.disabled = true;
		obj_alarmin_type.disabled = true;
		obj_alarmout_stable.disabled = true;
		obj_alarmout_id.disabled = true;
		obj_alarmin_delay.disabled = true;
	}
	else
	{
		obj_alarmout_no.disabled = false;
		obj_alarmin_id.disabled = false;
		obj_alarmin_type.disabled = false;
		obj_alarmout_stable.disabled = false;
		obj_alarmout_id.disabled = false;
		obj_alarmin_delay.disabled = false;
	}
}
function OnAlarminnoChange()
{
	var obj_alarminno = document.getElementById("enc_alarmin_no");
	var alarminno  = obj_alarminno.selectedIndex + 1;
	OnSelectAlarminno(alarminno);
}
function OnSelectAlarminno(num)
{
	var obj_alarmin_no = document.getElementById("enc_alarmin_no");
	var obj_alarmout_no = document.getElementById("enc_alarmout_no");
	var obj_alarmin_enable = document.getElementById("chk_enablealarm");
	var obj_alarmin_id = document.getElementById("alarminid");
	var obj_alarmin_type = document.getElementById("enc_alarmtype");
	var obj_alarmout_stable = document.getElementById("stabletime");
	var obj_alarmout_id = document.getElementById("alarmoutid");
	var obj_alarmin_delay = document.getElementById("outdelay");

	var obj_str = "alarmin_" + num + "_str";
	// "1;1;10000000000001;1;100;1;10;";
	//��������ͨ����;�Ƿ�ʹ��;���;����;ȥ����ʱ��;�����������ͨ����;�����ʱʱ��;
	var str = document.getElementById(obj_str).value;
	
	var strs = new Array();
	strs = str.split(";");
	//��������ͨ����
	
	//�Ƿ�����
	var alarmin_enable = parseInt(strs[1]);
	//���
	var alarmin_id = strs[2];
	//����
	var alarmin_type = parseInt(strs[3]);
	//ȥ����ʱ��
	var alarmin_stable = parseInt(strs[4]);
	//���������
	var alarmin_out = parseInt(strs[5]);
	//�����ʱ
	var alarmin_delay = parseInt(strs[6]);
	
	//������ʾ����
	if( alarmin_enable == 0 )
	{
		obj_alarmin_enable.checked = false;
		
		obj_alarmout_no.disabled = true;
		obj_alarmin_id.disabled = true;
		obj_alarmin_type.disabled = true;
		obj_alarmout_stable.disabled = true;
		obj_alarmout_id.disabled = true;
		obj_alarmin_delay.disabled = true;
	}
	else
	{
		obj_alarmin_enable.checked = true;
		
		obj_alarmout_no.disabled = false;
		obj_alarmin_id.disabled = false;
		obj_alarmin_type.disabled = false;
		obj_alarmout_stable.disabled = false;
		obj_alarmout_id.disabled = false;
		obj_alarmin_delay.disabled = false;
	}
	obj_alarmin_id.value = alarmin_id;
	obj_alarmin_type.selectedIndex = alarmin_type;
	obj_alarmout_stable.value = alarmin_stable;
	obj_alarmout_no.selectedIndex = alarmin_out;
	onSelectAlarmoutno(alarmin_out);
	obj_alarmin_delay.value = alarmin_delay;
}
</SCRIPT>

</head>

<BODY bgColor=#ffffff leftMargin=0 topMargin=0 marginheight="0" marginwidth="0" onLoad="OnSelectAlarminno(1)">
<div id="set_alarm_div" style="dispaly:block;">
<table width="1080">
  <tr><td>
    <table align="left">
      <tr>
        <td class="subtitle">��������</td>
      </tr>
	  <tr><td><img src="images/break_bg.gif"></td></tr>
    </table>
  </td></tr>
</table>

<form name="enc_alarm_form" action="/goform/form_enc_alarm" method=POST>
  <p>
    
<input type="hidden" name="submit_str" value="">
<!---->
<input type="hidden" id="alarmin_1_str" name="alarmin_1_str" value="<%asp_get_alarmin(1);%>">
<input type="hidden" id="alarmin_2_str" name="alarmin_2_str" value="<%asp_get_alarmin(2);%>">
<input type="hidden" id="alarmin_3_str" name="alarmin_3_str" value="<%asp_get_alarmin(3);%>">
<input type="hidden" id="alarmin_4_str" name="alarmin_4_str" value="<%asp_get_alarmin(4);%>">
<input type="hidden" id="alarmout_1_str" name="alarmout_1_str" value="<%asp_get_alarmout(1);%>">
	</p>
  <table width="1080" cellspacing="5">
	<tr><td class="lable">ѡ�񱨾�����ͨ��</td>
	<td>
		<select name="enc_alarmin_no" id="enc_alarmin_no" style="width: 120px;" onChange="OnAlarminnoChange()">
	    <option value="1">����01</option>
		<option value="2">����02</option>
		<option value="3">����03</option>
		<option value="4">����04</option>
		</select>
	</td>
	</tr>
	<tr><td class="lable">�Ƿ�ʹ��</td>
	<td>
	  <input id="chk_enablealarm" name="chk_enablealarm" type="checkbox" value="" onClick="OnEnableAlarmin()">ʹ��
	</td>
	</tr>
	<tr>
	<td class="lable">����������</td>
	<td>
	  <input type="text" id="alarminid" name="alarminid" value="" size="32"/>
	</td>
	</tr>
	<tr><td class="lable">����</td>
	<td>
		<select name="enc_alarmtype" id="enc_alarmtype" style="width: 120px;" onChange="">
	    <option value="1">������</option>
		<option value="2">������</option>
		</select>
	</td>
	</tr>	
    <tr>
	<td class="lable">ȥ����</td>
	<td>
	  <input type="text" id="stabletime" name="stabletime" value="" size="6"/>�루0-600��
	</td>
	</tr>
	<tr><td class="lable">�����������ͨ��</td>
	<td>
		<select name="enc_alarmout_no" id="enc_alarmout_no" style="width: 120px;" onChange="OnAlarmoutnoChange()">
		<option value="0">δ����</option>
	    <option value="1">���01</option>
		</select>
	</td>
	</tr>
	<tr>
	<td class="lable">����������</td>
	<td>
	  <input type="text" id="alarmoutid" name="alarmoutid" value="" size="32"/>
	</td>
	</tr>
    <tr>
	<td class="lable">�����ʱ</td>
	<td>
	  <input type="text" id="outdelay" name="outdelay" value="" size="6"/>�루0-300��
	</td>
	</tr>
	<tr>
	  <td>
	    <input type="submit" name="enc_alarm_submit" 
			style="border:none;background:url(images/save_btn.png);width:83px;height:20px;cursor:hand;" 
			onclick="return fun_enc_alarm_submit();" value=""/>
	  </td>
	  <td></td>
	</tr>
</table>
</form>
</div>
<div id="setting_alarm_tip_div" style="display:none;">
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