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
function fun_enc_channel_submit()
{
	var obj_chnno = document.getElementById("enc_chn_no_list");
	var obj_name = document.getElementById("chn_name");
	var obj_id = document.getElementById("chn_id");
	
	var chnno = obj_chnno.selectedIndex + 1;
	var name = obj_name.value;
    name = name.Trim();
	if(name=="")
		name = " ";
	var id = obj_id.value;
    id = id.Trim();
	if(id=="")
		id = " ";
	var submit_str = chnno + ";" + name + ";" + id + ";";
	document.getElementById("submit_str").value = submit_str;
	
	// ������ʾ����
	document.getElementById('set_channel_div').style.display="none";
	document.getElementById('setting_channel_tip_div').style.display="block";
	return true;
}
function fun_ptzport_submit()
{
	var obj_baude = document.getElementById('ptzport_baude_list');
	var obj_databit = document.getElementById('ptzport_databit_list');
	var obj_parity = document.getElementById('ptzport_parity_list');
	var obj_stopbits = document.getElementById('ptzport_stopbits_list');
	
	var submit__str = obj_baude.selectedIndex + ";" + obj_databit.selectedIndex + ";" + obj_parity.selectedIndex + ";" + obj_stopbits.selectedIndex + ";" ;
	document.getElementById('submit_ptzport_str').value = submit__str;
	
	// ������ʾ����
	document.getElementById('set_channel_div').style.display="none";
	document.getElementById('setting_channel_tip_div').style.display="block";
	return true;
}
function LoadPtzPortInfo()
{
	var obj_str = document.getElementById('ptzport_str');
	var obj_baude = document.getElementById('ptzport_baude_list');
	var obj_databit = document.getElementById('ptzport_databit_list');
	var obj_parity = document.getElementById('ptzport_parity_list');
	var obj_stopbits = document.getElementById('ptzport_stopbits_list');
	
	var str = obj_str.value;
	var strs = new Array();
	//"1;3;0;0;"// ������;����λ;��żУ��;ֹͣλ
	strs = str.split(";");
	if(strs.length < 4)
	{
		return;
	}
	
	var baude = parseInt(strs[0]);
	obj_baude.selectedIndex = baude;
	var databit = parseInt(strs[1]);
	obj_databit.selectedIndex = databit;
	var parity = parseInt(strs[2]);
	obj_parity.selectedIndex = parity;
	var stopbits = parseInt(strs[3]);
	obj_stopbits.selectedIndex = stopbits;
	return true;
}
function OnEncChnnoChange()
{
	var obj_chnno = document.getElementById("enc_chn_no_list");
	var index_chnno  = obj_chnno.selectedIndex + 1;
	OnSelectEncChnno(index_chnno);
}
function OnSelectEncChnno(num)
{
	var obj_chnno = document.getElementById("enc_chn_no_list");
	var obj_name = document.getElementById("chn_name");
	var obj_id = document.getElementById("chn_id");
	
	var obj_str = "chnno" + num + "_str";
	//var str = "1;Channel01;20001234;";
	var str =  document.getElementById(obj_str).value;
	
	var strs = new Array();
	strs = str.split(";");
	//ͨ����
	var chnno = parseInt(strs[0]);
	obj_chnno.selectedIndex = chnno-1;
	// ����
	var name = strs[1];
	obj_name.value = name;
	// ID
	var id = strs[2];
	obj_id.value = id;
}

function LoadForwardportInfo()
{
	var obj_str = document.getElementById('forwardport_str');
    var obj_enable = document.getElementById('enable');
	var obj_protolist = document.getElementById('proto_list');
	var obj_port = document.getElementById('port');

	var str = obj_str.value;
	var strs = new Array();
	//"1;1;3032;"// �Ƿ�����;��������;�˿ں�
	strs = str.split(";");
	if(strs.length < 3)
	{
		return;
	}
    
	var enabled = parseInt(strs[0]);
    if(enabled>0)
    {
        obj_enable.checked=true;
        obj_protolist.disabled=false;
        obj_port.disabled=false;
    }
    else
    {
        obj_enable.checked=false;
		obj_protolist.disabled=true;
        obj_port.disabled=true;
    }
	var proto = parseInt(strs[1]);
	obj_protolist.selectedIndex = proto;
	var port = strs[2];
	obj_port.value = port;
	return true;
}

function fun_enable_forwardport()
{
    var obj_enable = document.getElementById('enable');
	var obj_protolist = document.getElementById('proto_list');
	var obj_port = document.getElementById('port');
    if ( obj_enable.checked )
    {
        obj_protolist.disabled=false;
        obj_port.disabled=false;
    }
    else
    {
        LoadForwardportInfo();
        obj_enable.checked = false;
        obj_protolist.disabled=true;
        obj_port.disabled=true;
    }
    return true;
}

function fun_forwardport_submit()
{
	var obj_submitstr = document.getElementById('submit_forwardport_str');
    var obj_enable = document.getElementById('enable');
	var obj_protolist = document.getElementById('proto_list');
	var obj_port = document.getElementById('port');
    
    var enabled = 0;
    if(obj_enable.checked)
    {
        enabled = 1;
    }
    var proto = obj_protolist.selectedIndex;
    var port = obj_port.value;
	if( isNaN(port) || port.Trim()=="")
	{
		alert("͸���˿�����----�˿ںŴ���");
		obj_port.focus();
		obj_port.select();
		return false;
	}
    var submitstr = enabled + ";" + proto + ";" + port + ";";
    obj_submitstr.value = submitstr;
	// ������ʾ����
	document.getElementById('set_channel_div').style.display="none";
	document.getElementById('setting_channel_tip_div').style.display="block";
    return true;
}

function OnWebLoad()
{
	// ͨ����Ϣ
	OnSelectEncChnno(1);
	// PTZ��Ϣ
	LoadPtzPortInfo();
    // ͸���˿���Ϣ
    LoadForwardportInfo();
}

</SCRIPT>

</head>

<BODY bgColor=#ffffff leftMargin=0 topMargin=0 marginheight="0" marginwidth="0" onLoad="OnWebLoad()">
<div id="set_channel_div" style="dispaly:block;">
<table width="1080">
  <tr><td>
    <table align="left">
      <tr>
        <td class="subtitle">ͨ������</td>
      </tr>
	  <tr><td><img src="images/break_bg.gif"></td></tr>
    </table>
  </td></tr>
</table>

<form name="enc_channel_form" action="/goform/form_enc_channel" method=POST>
  <p>
    
<input type="hidden" id="submit_str" name="submit_str" value="">
<!---->
<input type="hidden" id="chnno1_str" name="chnno1_str" value="<%asp_get_enc_channel(1);%>">
<input type="hidden" id="chnno2_str" name="chnno2_str" value="<%asp_get_enc_channel(2);%>">
<input type="hidden" id="chnno3_str" name="chnno3_str" value="<%asp_get_enc_channel(3);%>">
<input type="hidden" id="chnno4_str" name="chnno4_str" value="<%asp_get_enc_channel(4);%>">
	</p>
  <table width="1080" cellspacing="5">
	<tr><td class="lable">ѡ�����ͨ��</td>
	<td>
		<select name="enc_chn_no_list" id="enc_chn_no_list" style="width: 120px;" onChange="OnEncChnnoChange()">
	    <option value="1">ͨ��01</option>
		<option value="2">ͨ��02</option>
        <option value="3">ͨ��03</option>
		<option value="4">ͨ��04</option>
		</select>
	</td>
	</tr>
	<tr><td class="lable">����ͨ������</td>
	<td>
		<input type="text" id="chn_name" name="chn_name" value="" size="32"/>
	</td>
	</tr>
	<tr><td class="lable">����ͨ�����</td>
	<td>
		<input type="text" id="chn_id" name="chn_id" value="" size="32"/>
	</td>
	</tr>
	<tr>
	  <td>
	    <input type="submit" name="enc_channel_submit" 
			style="border:none;background:url(images/save_btn.png);width:83px;height:20px;cursor:hand;" 
			onclick="return fun_enc_channel_submit();" value=""/>
	  </td>
	  <td></td>
	</tr>
</table>
</form>

<table width="1080">
  <tr><td>
    <table align="left">
      <tr>
        <td class="subtitle">PTZͨѶ�˿�����</td>
      </tr>
	  <tr><td><img src="images/break_bg.gif"></td></tr>
    </table>
  </td></tr>
</table>

<form name="enc_ptzport_form" action="/goform/form_enc_ptzport" method=POST>
  <p>
    
<input type="hidden" name="submit_ptzport_str" value="">
<!---->
<input type="hidden" name="ptzport_str" value="<%asp_get_ptzport();%>">

	</p>
  <table width="1080" cellspacing="5">
	<tr><td class="lable">������</td>
	<td>
		<select name="ptzport_baude_list" id="enc_chn_no_list" style="width: 120px;" onChange="">
	    <option value="1">2400</option>
		<option value="2" selected>4800</option>
		<option value="3">9600</option>
		<option value="4">19200</option>
	    <option value="5">38400</option>
		<option value="6">51200</option>
		</select>
	</td>
	</tr>
	<tr><td class="lable">����λ</td>
	<td>
		<select name="ptzport_databit_list" id="ptzport_databit_list" style="width: 120px;" onChange="">
	    <option value="1">5</option>
		<option value="2">6</option>
		<option value="3">7</option>
		<option value="4" selected>8</option>
		</select>
	</td>
	</tr>
	<tr><td class="lable">��żУ��</td>
	<td>
		<select name="ptzport_parity_list" id="ptzport_parity_list" style="width: 120px;" onChange="">
	    <option value="1" selected>��</option>
		<option value="2">��У��</option>
		<option value="3">żУ��</option>
		</select>
	</td>
	</tr>
	<tr><td class="lable">ֹͣλ</td>
	<td>
		<select name="ptzport_stopbits_list" id="ptzport_stopbits_list" style="width: 120px;" onChange="">
	    <option value="1" selected>1</option>
		<option value="2">1.5</option>
		<option value="3">2</option>
		</select>
	</td>
	</tr>
	<tr>
	  <td>
	    <input type="submit" name="ptzport_submit" 
			style="border:none;background:url(images/save_btn.png);width:83px;height:20px;cursor:hand;" 
			onclick="return fun_ptzport_submit();" value=""/>
	  </td>
	  <td></td>
	</tr>
</table>
</form>

<table width="1080">
  <tr><td>
    <table align="left">
      <tr>
        <td class="subtitle">͸���˿�����</td>
      </tr>
	  <tr><td><img src="images/break_bg.gif"></td></tr>
    </table>
  </td></tr>
</table>

<form name="enc_forwardport_form" action="/goform/enc_forwardport_form" method=POST>
<input type="hidden" id="submit_forwardport_str" name="submit_forwardport_str" value="">
<!---->
<input type="hidden" id="forwardport_str" name="forwardport_str" value="<%asp_get_forwardport_info();%>">
  <table width="500" cellspacing="5">
    <tr>
	<td class="lable">����</td>
	<td>
	  <input id="enable" name="enable" type="checkbox" value="" onClick="fun_enable_forwardport()">
	</td>
	</tr>
	<tr>
	  <td class="lable">��������</td>
	  <td>
	  	<select name="proto_list" id="proto_list" style="width: 80px;" onChange="">
	      <option value="0">UDP</option>
		  <option value="1">TCP</option>
		</select>
	  </td>
	</tr>
	<tr>
	<td class="lable">�˿ں�</td>
	<td>
	  <input type="text" id="port" name="port" value="" size="10"/>
	</td>
	</tr>
    <tr>
	  <td>
	    <input type="submit" name="forwardport_submit" 
			style="border:none;background:url(images/save_btn.png);width:83px;height:20px;cursor:hand;" 
			onclick="return fun_forwardport_submit();" value=""/>
	  </td>
	  <td></td>
	</tr>
  </table>
</form>
<table width="500" cellspacing="5">
	<tr>
        <td colspan="2"><img src="images/tip_24.gif"><span class="span_tip" style="font-size:12">˵����͸���˿����ñ����ȴ�5�����Ч��</span></td>
		<td></td>
    </tr>
</table>
</div>

<div id="setting_channel_tip_div" style="display:none;">
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