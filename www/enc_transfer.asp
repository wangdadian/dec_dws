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
function fun_enc_transfer_submit()
{
	var obj_chnno = document.getElementById("enc_chn_no_list");
	var obj_streamno = document.getElementById("streamno_list");
	var obj_chk_t1 = document.getElementById('chk_trans1');
	var obj_chk_t2 = document.getElementById('chk_trans2');
	var obj_chk_t3 = document.getElementById('chk_trans3');
	var obj_sel_p1 = document.getElementById("proto_list1");
	var obj_sel_mux1 = document.getElementById("enc_mux1");
	var obj_sel_p2 = document.getElementById("proto_list2");
	var obj_sel_mux2 = document.getElementById("enc_mux2");
	var obj_sel_p3 = document.getElementById("proto_list3");
	var obj_sel_mux3 = document.getElementById("enc_mux3");
	
	var obj_ip1 = document.getElementById('ip_addr1');
	var obj_port1 = document.getElementById('port1');
	var obj_ip2 = document.getElementById('ip_addr2');
	var obj_port2 = document.getElementById('port2');
	var obj_ip3 = document.getElementById('ip_addr3');
	var obj_port3 = document.getElementById('port3');

	var web_submit_str = "";
	// ͨ����
	var chnno = obj_chnno.selectedIndex + 1;
	var streamno = obj_streamno.selectedIndex;
	var num = 0;
	if(streamno == 0)// ������
	{
		num = chnno * 2 - 1 ;
	}
	else
	{
		num = chnno * 2;
	}
	web_submit_str += num;
	web_submit_str += ";";

	// ����һ
	str_trans1="";
	if( obj_chk_t1.checked )
		str_trans1 = "1,1,";
	else
		str_trans1 += "0,1,";
		
	if( check_ip(obj_ip1) == false && obj_chk_t1.checked )
	{
		alert("����һIP��ַ����");
		return false;
	}
	if( isNaN(obj_port1.value) )
	{
		alert("����һ�˿ںŴ���");
		obj_port1.focus();
		obj_port1.select();
		return false;
	}
	if(obj_ip1.value=="")
		obj_ip1.value=" ";
	if(obj_port1.value=="")
		obj_port1.value=" ";
	str_trans1 += obj_sel_p1.selectedIndex + ',' + obj_ip1.value + "," + obj_port1.value + "," +
	               obj_sel_mux1.selectedIndex + ";";
	web_submit_str += str_trans1;
	
	// ���Ӷ�
	str_trans2="";
	if( obj_chk_t2.checked )
		str_trans2 = "1,2,";
	else
		str_trans2 += "0,2,";
		
	if( check_ip(obj_ip2) == false && obj_chk_t2.checked )
	{
		alert("���Ӷ�IP��ַ����");
		return false;
	}
	if( isNaN(obj_port2.value) )
	{
		alert("���Ӷ��˿ںŴ���");
		obj_port2.focus();
		obj_por2.select();
		return false;
	}
	if(obj_ip2.value=="")
		obj_ip2.value=" ";
	if(obj_port2.value=="")
		obj_port2.value=" ";
	str_trans2 += obj_sel_p2.selectedIndex + ',' + obj_ip2.value + "," + obj_port2.value + "," +
	               obj_sel_mux2.selectedIndex + ";";
	web_submit_str += str_trans2;

	// ������
	str_trans3="";
	if( obj_chk_t3.checked )
		str_trans3 = "1,3,";
	else
		str_trans3 += "0,3,";
		
	if( check_ip(obj_ip3) == false && obj_chk_t3.checked )
	{
		alert("������IP��ַ����");
		return false;
	}
	if( isNaN(obj_port3.value) )
	{
		alert("�������˿ںŴ���");
		obj_port3.focus();
		obj_port3.select();
		return false;
	}
	if(obj_ip2.value=="")
		obj_ip2.value=" ";
	if(obj_port2.value=="")
		obj_port2.value=" ";
	str_trans3 += obj_sel_p3.selectedIndex + ',' + obj_ip3.value + "," + obj_port3.value + "," +
	               obj_sel_mux3.selectedIndex + ";";
	web_submit_str += str_trans3;
	
	document.getElementById("submit_str").value = web_submit_str;

	// ������ʾ����
	document.getElementById('set_transfer_div').style.display="none";
	document.getElementById('setting_transfer_tip_div').style.display="block";
	return true;
}

function fun_chk_trans()
{
	var obj_chk_t1 = document.getElementById('chk_trans1');
	var obj_chk_t2 = document.getElementById('chk_trans2');
	var obj_chk_t3 = document.getElementById('chk_trans3');

	//����һ
	if( obj_chk_t1.checked  )
	{
		document.getElementById('proto_list1').disabled=false;
		document.getElementById('ip_addr1').disabled=false;
		document.getElementById('port1').disabled=false;
		document.getElementById('enc_mux1').disabled=false;
	}
	else
	{
		document.getElementById('proto_list1').disabled=true;
		document.getElementById('ip_addr1').disabled=true;
		document.getElementById('port1').disabled=true;
		document.getElementById('enc_mux1').disabled=true;
	}
	//���Ӷ�
	if( obj_chk_t2.checked  )
	{
		document.getElementById('proto_list2').disabled=false;
		document.getElementById('ip_addr2').disabled=false;
		document.getElementById('port2').disabled=false;
		document.getElementById('enc_mux2').disabled=false;
	}
	else
	{
		document.getElementById('proto_list2').disabled=true;
		document.getElementById('ip_addr2').disabled=true;
		document.getElementById('port2').disabled=true;
		document.getElementById('enc_mux2').disabled=true;
	}
	//������
	if( obj_chk_t3.checked  )
	{
		document.getElementById('proto_list3').disabled=false;
		document.getElementById('ip_addr3').disabled=false;
		document.getElementById('port3').disabled=false;
		document.getElementById('enc_mux3').disabled=false;
	}
	else
	{
		document.getElementById('proto_list3').disabled=true;
		document.getElementById('ip_addr3').disabled=true;
		document.getElementById('port3').disabled=true;
		document.getElementById('enc_mux3').disabled=true;
	}

	return true;
}
function OnStreamnoChange()
{
	var obj_chnno = document.getElementById("enc_chn_no_list");
	var index_chnno  = obj_chnno.selectedIndex + 1;
	var obj_streamno = document.getElementById("streamno_list");
	var index_streamno = obj_streamno.selectedIndex;
	var num = 0;
	if(index_streamno == 0)// ������
	{
		num = index_chnno * 2 - 1;
	}
	else // ������
	{
		num = index_chnno * 2;
	}
	OnSelectEncChnno(num);
}
function OnEncChnnoChange()
{
	var obj_chnno = document.getElementById("enc_chn_no_list");
	var index_chnno  = obj_chnno.selectedIndex + 1;
	var num = index_chnno * 2 - 1;// Ĭ��ѡ��������
	OnSelectEncChnno(num);
}
function OnSelectEncChnno(num)
{
	var obj_chnno = document.getElementById("enc_chn_no_list");
	var obj_streamno = document.getElementById("streamno_list");
	var obj_chk_t1 = document.getElementById('chk_trans1');
	var obj_chk_t2 = document.getElementById('chk_trans2');
	var obj_chk_t3 = document.getElementById('chk_trans3');
	var obj_sel_p1 = document.getElementById("proto_list1");
	var obj_sel_mux1 = document.getElementById("enc_mux1");
	var obj_sel_p2 = document.getElementById("proto_list2");
	var obj_sel_mux2 = document.getElementById("enc_mux2");
	var obj_sel_p3 = document.getElementById("proto_list3");
	var obj_sel_mux3 = document.getElementById("enc_mux3");
	
	var obj_ip1 = document.getElementById('ip_addr1');
	var obj_port1 = document.getElementById('port1');
	var obj_ip2 = document.getElementById('ip_addr2');
	var obj_port2 = document.getElementById('port2');
	var obj_ip3 = document.getElementById('ip_addr3');
	var obj_port3 = document.getElementById('port3');
	
	//"1;1,1,1,192.168.1.1,4511,2;1,2,0,192.168.1.2,4511,2;1,3,3,192.168.1.3,4512,0;"
	var chnno_sel = 0;
	var streamno_sel = 0;
	if(num % 2 != 0)//������
	{
		chnno_sel = (num + 1) / 2;
		streamno_sel = 1;
	}
	else // ������
	{
		chnno_sel = num / 2;
		streamno_sel = 2;
	}
	var obj_str = "chnno" + chnno_sel + "_" + streamno_sel + "_str";
	var str =  document.getElementById(obj_str).value;
	
	var strs = new Array();
	strs = str.split(";");

	//ͨ���š�������
	var num = parseInt(strs[0]);
	var chnno = 0;
	var streamno = num % 2;
	if(streamno == 0)//������
	{
		obj_streamno.selectedIndex = 1;
		var chnno = num / 2;
	}
	else // ������
	{
		obj_streamno.selectedIndex = 0;
		var chnno = parseInt((num / 2)) + 1;
	}
	obj_chnno.selectedIndex = chnno-1;
	
	// ����һ
	var values1 = new Array();
	values1 = strs[1].split(",");
	obj_sel_p1.selectedIndex = parseInt(values1[2]);
	obj_ip1.value=values1[3];
	obj_port1.value=values1[4];
	obj_sel_mux1.selectedIndex = parseInt(values1[5]);
	if(values1[0]==1)
		obj_chk_t1.checked=true;
	else
		obj_chk_t1.checked=false;
		
	// ���Ӷ�
	var values2 = new Array();
	values2 = strs[2].split(",");
	obj_sel_p2.selectedIndex = parseInt(values2[2]);
	obj_ip2.value=values2[3];
	obj_port2.value=values2[4];
	obj_sel_mux2.selectedIndex = parseInt(values2[5]);
	if(values2[0]==1)
		obj_chk_t2.checked=true;
	else
		obj_chk_t2.checked=false;
		
	// ������
	var values3 = new Array();
	values3 = strs[3].split(",");
	obj_sel_p3.selectedIndex = parseInt(values3[2]);
	obj_ip3.value=values3[3];
	obj_port3.value=values3[4];
	obj_sel_mux3.selectedIndex = parseInt(values3[5]);
	if(values3[0]==1)
		obj_chk_t3.checked=true;
	else
		obj_chk_t3.checked=false;


	fun_chk_trans();
	return true;
}
</SCRIPT>
</head>

<BODY bgColor=#ffffff leftMargin=0 topMargin=0 marginheight="0" marginwidth="0" onLoad="OnSelectEncChnno(1)">
<div id="set_transfer_div" style="dispaly:block;">
<table width="1080">
  <tr><td>
    <table align="left">
      <tr>
        <td class="subtitle">������������</td>
      </tr>
	  <tr><td><img src="images/break_bg.gif"></td></tr>
    </table>
  </td></tr>
</table>

<form name="transfer_form" action="/goform/form_enc_transfer" method=POST>
  <p>
    <!---->
<input type="hidden" id="submit_str" name="submit_str" value="">
<input type="hidden" id="chnno1_1_str" name="chnno1_1_str" value="<%asp_get_enc_trans(1);%>">
<input type="hidden" id="chnno1_2_str" name="chnno1_2_str" value="<%asp_get_enc_trans(2);%>">
<input type="hidden" id="chnno2_1_str" name="chnno2_1_str" value="<%asp_get_enc_trans(3);%>">
<input type="hidden" id="chnno2_2_str" name="chnno2_2_str" value="<%asp_get_enc_trans(4);%>">
<input type="hidden" id="chnno3_1_str" name="chnno3_1_str" value="<%asp_get_enc_trans(5);%>">
<input type="hidden" id="chnno3_2_str" name="chnno3_2_str" value="<%asp_get_enc_trans(6);%>">
<input type="hidden" id="chnno4_1_str" name="chnno4_1_str" value="<%asp_get_enc_trans(7);%>">
<input type="hidden" id="chnno4_2_str" name="chnno4_2_str" value="<%asp_get_enc_trans(8);%>">
    <!---->
	</p>
  <table width="1080" cellspacing="5">
	<tr>
	<tr>
	<td class="lable">ѡ�����ͨ��</td>
	<td>
		<select name="enc_chn_no_list" id="enc_chn_no_list" style="width: 80px;" onChange="OnEncChnnoChange()">
	    <option value="1">ͨ��01</option>
		<option value="2">ͨ��02</option>
        <option value="3">ͨ��03</option>
		<option value="4">ͨ��04</option>
		</select>
	</td>
	</tr>
	<tr><td class="lable">ѡ��������</td>
	<td>
		<select name="streamno_list" id="streamno_list" style="width: 80px;" onChange="OnStreamnoChange()">
	    <option value="1">������</option>
		<option value="2">������</option>
		</select>
	</td>
	</tr>
  </table>
  <table width="500" cellspacing="5">
   <tr><td class="lable_ex" colspan="2">����һ</td></tr>
    <tr>
	<td class="lable">����</td>
	<td>
	  <input id="chk_trans1" name="chk_trans1" type="checkbox" value="" onClick="fun_chk_trans()">
	</td>
	</tr>
	<tr>
	  <td class="lable">��������</td>
	  <td>
	  	<select name="proto_list1" id="proto_list1" style="width: 80px;" onChange="">
	      <option value="0">UDP</option>
		  <option value="1">TCP</option>
		  <option value="2">RTSP</option>
		  <option value="3">RTP</option>
		</select>
	  </td>
	</tr>
    <tr>
	<td class="lable">IP��ַ</td>
	<td>
	  <input type="text" id="ip_addr1" name="ip_addr1" value="" size="20"/>
	</td>
	</tr>
	<tr>
	<td class="lable">�˿ں�</td>
	<td>
	  <input type="text" id="port1" name="port1" value="" size="10"/>
	</td>
	</tr>
	<tr>
	  <td class="lable">��Ƶ����</td>
	  <td>
	  	<select name="enc_mux1" id="enc_mux1" style="width: 80px;" onChange="">
	      <option value="0">ES</option>
		  <option value="1">PS</option>
		  <option value="2">TS</option>
		</select>
	  </td>
	</tr>
	
   <tr><td class="lable_ex" colspan="2">���Ӷ�</td></tr>
	<tr>
	<td class="lable">����</td>
	<td>
	  <input id="chk_trans2" name="chk_trans2" type="checkbox" value="" onClick="fun_chk_trans()">
	</td>
	</tr>
	<tr>
	  <td class="lable">��������</td>
	  <td>
	  	<select name="proto_list2" id="proto_list2" style="width: 80px;" onChange="">
	      <option value="0">UDP</option>
		  <option value="1">TCP</option>
		  <option value="2">RTSP</option>
		  <option value="3">RTP</option>
		</select>
	  </td>
	</tr>
    <tr>
	<td class="lable">IP��ַ</td>
	<td>
	  <input type="text" id="ip_addr2" name="ip_addr2" value="" size="20"/>
	</td>
	</tr>
	<tr>
	<td class="lable">�˿ں�</td>
	<td>
	  <input type="text" id="port2" name="port2" value="" size="10"/>
	</td>
	</tr>
	<tr>
	  <td class="lable">��Ƶ����</td>
	  <td>
	  	<select name="enc_mux2" id="enc_mux2" style="width: 80px;" onChange="">
	      <option value="0">ES</option>
		  <option value="1">PS</option>
		  <option value="2">TS</option>
		</select>
	  </td>
	</tr>
	
   <tr><td class="lable_ex" colspan="2">������</td></tr>
    <tr>
	<td class="lable">����</td>
	<td>
	  <input id="chk_trans3" name="chk_trans3" type="checkbox" value="" onClick="fun_chk_trans()">
	</td>
	</tr>
	<tr>
	  <td class="lable">��������</td>
	  <td>
	  	<select name="proto_list3" id="proto_list3" style="width: 80px;" onChange="">
	      <option value="0">UDP</option>
		  <option value="1">TCP</option>
		  <option value="2">RTSP</option>
		  <option value="3">RTP</option>
		</select>
	  </td>
	</tr>
    <tr>
	<td class="lable">IP��ַ</td>
	<td>
	  <input type="text" id="ip_addr3" name="ip_addr3" value="" size="20"/>
	</td>
	</tr>
	<tr>
	<td class="lable">�˿ں�</td>
	<td>
	  <input type="text" id="port3" name="port3" value="" size="10"/>
	</td>
	</tr>
	<tr>
	  <td class="lable">��Ƶ����</td>
	  <td>
	  	<select name="enc_mux3" id="enc_mux3" style="width: 80px;" onChange="">
	      <option value="0">ES</option>
		  <option value="1">PS</option>
		  <option value="2">TS</option>
		</select>
	  </td>
	</tr>
	<tr>
	  <td>
	    <input type="submit" name="enc_transfer_submit" 
			style="border:none;background:url(images/save_btn.png);width:83px;height:20px;cursor:hand;" 
			onclick="return fun_enc_transfer_submit();" value=""/>
	  </td>
	  <td></td>
	</tr>
</table>
</form>
</div>
<div id="setting_transfer_tip_div" style="display:none;">
<table cellspacing="5">
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