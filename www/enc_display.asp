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

function fun_enc_display_submit()
{
	var obj_chk_date = document.getElementById('chk_date');
	var obj_chk_time = document.getElementById('chk_time');
	var obj_chk_datetime = document.getElementById('chk_datetime');
	var obj_chk_content1 = document.getElementById('chk_content1');
	var obj_chk_content2 = document.getElementById('chk_content2');
	var obj_chk_content3 = document.getElementById('chk_content3');
	var obj_chk_name = document.getElementById('chk_name');
	var obj_font = document.getElementById("font_list");
	var obj_chnno = document.getElementById("chnno_list");
	var obj_streamno = document.getElementById("streamno_list");
	
	var submit_str = "";
	// 通道号	
	var chnno = obj_chnno.selectedIndex + 1;
	var streamno = obj_streamno.selectedIndex;
	var num = 0;
	if(streamno == 0)// 主码流
	{
		num = chnno * 2 - 1 ;
	}
	else
	{
		num = chnno * 2;
	}
	submit_str += num;
	submit_str += ";";
	
	// 字体大小
	submit_str += "1;";
	// 日期
	var obj_date_x = document.getElementById('date_posx');
	var obj_date_y = document.getElementById('date_posy');	
	if( isNaN(obj_date_x.value) )
	{
		alert("位置数值错误！");
		obj_date_x.focus();
		obj_date_x.select();
		return false;
	}
	if( isNaN(obj_date_y.value) )
	{
		alert("位置数值错误！");
		obj_date_y.focus();
		obj_date_y.select();
		return false;
	}
	str_date="";
	if( obj_chk_date.checked )
		str_date = "1,";
	else
		str_date += "0,";

	str_date += obj_date_x.value + "," + obj_date_y.value + ",0, ;";
	submit_str += str_date;
	
	// 时间
	var obj_time_x = document.getElementById('time_posx');
	var obj_time_y = document.getElementById('time_posy');
	if( isNaN(obj_time_x.value) )
	{
		alert("位置数值错误！");
		obj_time_x.focus();
		obj_time_x.select();
		return false;
	}
	if( isNaN(obj_time_y.value) )
	{
		alert("位置数值错误！");
		obj_time_y.focus();
		obj_time_y.select();
		return false;
	}
	str_time="";
	if( obj_chk_time.checked )
		str_time = "1,";
	else
		str_time += "0,";
	str_time += obj_time_x.value + "," + obj_time_y.value + ",1, ;";
	submit_str += str_time;
	
	// 日期时间
	var obj_datetime_x = document.getElementById('datetime_posx');
	var obj_datetime_y = document.getElementById('datetime_posy');
	if( isNaN(obj_datetime_x.value) )
	{
		alert("位置数值错误！");
		obj_datetime_x.focus();
		obj_datetime_x.select();
		return false;
	}
	if( isNaN(obj_datetime_y.value) )
	{
		alert("位置数值错误！");
		obj_datetime_y.focus();
		obj_datetime_y.select();
		return false;
	}
	str_datetime="";
	if( obj_chk_datetime.checked )
		str_datetime = "1,";
	else
		str_datetime += "0,";
	str_datetime += obj_datetime_x.value + "," + obj_datetime_y.value + ",2, ;";
	submit_str += str_datetime;
	
	// 名称
	var obj_name_x = document.getElementById('name_posx');
	var obj_name_y = document.getElementById('name_posy');
	if( isNaN(obj_name_x.value) )
	{
		alert("位置数值错误！");
		obj_name_x.focus();
		obj_name_x.select();
		return false;
	}
	if( isNaN(obj_name_y.value) )
	{
		alert("位置数值错误！");
		obj_name_y.focus();
		obj_name_y.select();
		return false;
	}
	str_name="";
	if( obj_chk_name.checked )
		str_name = "1,";
	else
		str_name += "0,";
	var value_name = document.getElementById('name_text').value;
	if(value_name=="")
	{
		value_name = " ";
	}
	str_name += obj_name_x.value + "," + obj_name_y.value + ",4," + value_name + ";";
	submit_str += str_name;
	
	// 内容一
	var obj_content1_x = document.getElementById('content1_posx');
	var obj_content1_y = document.getElementById('content1_posy');
	if( isNaN(obj_content1_x.value) )
	{
		alert("位置数值错误！");
		obj_content1_x.focus();
		obj_content1_x.select();
		return false;
	}
	if( isNaN(obj_content1_y.value) )
	{
		alert("位置数值错误！");
		obj_content1_y.focus();
		obj_content1_y.select();
		return false;
	}
	str_content1="";
	if( obj_chk_content1.checked )
		str_content1 = "1,";
	else
		str_content1 += "0,";
	var value_content1 = document.getElementById('content1_text').value;
	if(value_content1=="")
	{
		value_content1 = " ";
	}
	str_content1 += obj_content1_x.value + "," + obj_content1_y.value + ",3," + value_content1 + ";";
	submit_str += str_content1;

	// 内容二
	var obj_content2_x = document.getElementById('content2_posx');
	var obj_content2_y = document.getElementById('content2_posy');
	if( isNaN(obj_content2_x.value) )
	{
		alert("位置数值错误！");
		obj_content2_x.focus();
		obj_content2_x.select();
		return false;
	}
	if( isNaN(obj_content2_y.value) )
	{
		alert("位置数值错误！");
		obj_content2_y.focus();
		obj_content2_y.select();
		return false;
	}
	str_content2="";
	if( obj_chk_content2.checked )
		str_content2 = "1,";
	else
		str_content2 += "0,";
	var value_content2 = document.getElementById('content2_text').value;
	if(value_content2=="")
	{
		value_content2 = " ";
	}
	str_content2 += obj_content2_x.value + "," + obj_content2_y.value + ",3," + value_content2 + ";";
	submit_str += str_content2;
	
	// 内容三
	var obj_content3_x = document.getElementById('content3_posx');
	var obj_content3_y = document.getElementById('content3_posy');
	if( isNaN(obj_content3_x.value) )
	{
		alert("位置数值错误！");
		obj_content3_x.focus();
		obj_content3_x.select();
		return false;
	}
	if( isNaN(obj_content3_y.value) )
	{
		alert("位置数值错误！");
		obj_content3_y.focus();
		obj_content3_y.select();
		return false;
	}
	str_content3="";
	if( obj_chk_content3.checked )
		str_content3 = "1,";
	else
		str_content3 += "0,";
	var value_content3 = document.getElementById('content3_text').value;
	if(value_content3=="")
	{
		value_content3 = " ";
	}
	str_content3 += obj_content3_x.value + "," + obj_content3_y.value + ",3," + value_content3 + ";";
	submit_str += str_content3;
	
	document.getElementById("submit_str").value = submit_str;
	//alert(submit_str);
	// 界面显示控制
	document.getElementById('set_display_div').style.display="none";
	document.getElementById('setting_display_tip_div').style.display="block";	
	
	return true;
}

function fun_chk_osd()
{
	var obj_chk_date = document.getElementById('chk_date');
	var obj_chk_time = document.getElementById('chk_time');
	var obj_chk_datetime = document.getElementById('chk_datetime');
	var obj_chk_content1 = document.getElementById('chk_content1');
	var obj_chk_content2 = document.getElementById('chk_content2');
	var obj_chk_content3 = document.getElementById('chk_content3');
	var obj_chk_name = document.getElementById('chk_name');

	//日期时间显示
	if( obj_chk_date.checked  )
	{
		document.getElementById('date_posx').disabled=false;
		document.getElementById('date_posy').disabled=false;
	}
	else
	{
		document.getElementById('date_posx').disabled=true;
		document.getElementById('date_posy').disabled=true;
	}
	//时间显示
	if( obj_chk_time.checked )
	{
		document.getElementById('time_posx').disabled=false;
		document.getElementById('time_posy').disabled=false;
	}
	else
	{
		document.getElementById('time_posx').disabled=true;
		document.getElementById('time_posy').disabled=true;
	}
	//日期时间显示
	if( obj_chk_datetime.checked  )
	{
		document.getElementById('datetime_posx').disabled=false;
		document.getElementById('datetime_posy').disabled=false;
	}
	else
	{
		document.getElementById('datetime_posx').disabled=true;
		document.getElementById('datetime_posy').disabled=true;
	}
	//名称显示
	if( obj_chk_name.checked  )
	{
		document.getElementById('name_text').disabled=false;
		document.getElementById('name_posx').disabled=false;
		document.getElementById('name_posy').disabled=false;
	}
	else
	{
		document.getElementById('name_text').disabled=true;
		document.getElementById('name_posx').disabled=true;
		document.getElementById('name_posy').disabled=true;
	}
	//内容显示一
	if( obj_chk_content1.checked  )
	{
		document.getElementById('content1_text').disabled=false;
		document.getElementById('content1_posx').disabled=false;
		document.getElementById('content1_posy').disabled=false;
	}
	else
	{
		document.getElementById('content1_text').disabled=true;
		document.getElementById('content1_posx').disabled=true;
		document.getElementById('content1_posy').disabled=true;
	}
	//内容显示二
	if( obj_chk_content2.checked  )
	{
		document.getElementById('content2_text').disabled=false;
		document.getElementById('content2_posx').disabled=false;
		document.getElementById('content2_posy').disabled=false;
	}
	else
	{
		document.getElementById('content2_text').disabled=true;
		document.getElementById('content2_posx').disabled=true;
		document.getElementById('content2_posy').disabled=true;
	}
	//内容显示三
	if( obj_chk_content3.checked  )
	{
		document.getElementById('content3_text').disabled=false;
		document.getElementById('content3_posx').disabled=false;
		document.getElementById('content3_posy').disabled=false;
	}
	else
	{
		document.getElementById('content3_text').disabled=true;
		document.getElementById('content3_posx').disabled=true;
		document.getElementById('content3_posy').disabled=true;
	}

	return true;
}
function OnStreamnoChange()
{
	var obj_chnno = document.getElementById("chnno_list");
	var index_chnno  = obj_chnno.selectedIndex + 1;
	var obj_streamno = document.getElementById("streamno_list");
	var index_streamno = obj_streamno.selectedIndex;
	var num = 0;
	if(index_streamno == 0)// 主码流
	{
		num = index_chnno * 2 - 1;
	}
	else // 子码流
	{
		num = index_chnno * 2;
	}
	OnSelectChnno(num);
}
function OnChnnoChange()
{
	var obj_chnno = document.getElementById("chnno_list");
	var index_chnno  = obj_chnno.selectedIndex + 1;
	var num = index_chnno * 2 - 1;// 默认选择主码流
	OnSelectChnno(num);
}
function OnSelectChnno(num)
{
	var obj_chk_date = document.getElementById('chk_date');
	var obj_chk_time = document.getElementById('chk_time');
	var obj_chk_datetime = document.getElementById('chk_datetime');
	var obj_chk_content1 = document.getElementById('chk_content1');
	var obj_chk_content2 = document.getElementById('chk_content2');
	var obj_chk_content3 = document.getElementById('chk_content3');
	var obj_chk_name = document.getElementById('chk_name');
	var obj_font = document.getElementById("font_list");
	var obj_chnno = document.getElementById("chnno_list");
	var obj_streamno = document.getElementById("streamno_list");
	//"1;1;1,0,0,0,2014-1-2;1,1,1,1,10:10:10;0,2,2,2,2014-1-2 15:10:10;1,2,3,3,HELLO;1,2,3,3,WROLD;0,2,3,3,MISS;0,2,3,3,;";
	var chnno_sel = 0;
	var streamno_sel = 0;
	if(num % 2 != 0)//主码流
	{
		chnno_sel = (num + 1) / 2;
		streamno_sel = 1;
	}
	else // 子码流
	{
		chnno_sel = num / 2;
		streamno_sel = 2;
	}
	var obj_str = "chnno" + chnno_sel + "_" + streamno_sel + "_str";
	//alert(obj_str);
	var str =  document.getElementById(obj_str).value;
	//alert(str);
	var strs = new Array();
	strs = str.split(";");
	//通道号、码流号
	var num = parseInt(strs[0]);
	var chnno = 0;
	var streamno = num % 2;
	if(streamno == 0)//子码流
	{
		obj_streamno.selectedIndex = 1;
		var chnno = num / 2;
	}
	else // 主码流
	{
		obj_streamno.selectedIndex = 0;
		var chnno = parseInt((num / 2)) + 1;
	}
	obj_chnno.selectedIndex = chnno-1;
	
	//字体大小
	var fontno = parseInt(strs[1]);
	obj_font.selectedIndex = 0;//fontno;

	// OSD控制
	// 日期	
	var values1 = new Array();
	values1 = strs[2].split(",");
	document.getElementById('date_posx').value=values1[1];
	document.getElementById('date_posy').value=values1[2];
	if(values1[0]==1)
		obj_chk_date.checked=true;
	else
		obj_chk_date.checked=false;

	// 时间
	var values2 = new Array();
	values2 = strs[3].split(",");
	document.getElementById('time_posx').value=values2[1];
	document.getElementById('time_posy').value=values2[2];
	if(values2[0]==1)
		obj_chk_time.checked=true;
	else
		obj_chk_time.checked=false;
		
	// 日期时间
	var values3 = new Array();
	values3 = strs[4].split(",");
	document.getElementById('datetime_posx').value=values3[1];
	document.getElementById('datetime_posy').value=values3[2];
	if(values3[0]==1)
		obj_chk_datetime.checked=true;
	else
		obj_chk_datetime.checked=false;
		
	// 名称
	var valuename = new Array();
	valuename = strs[5].split(",");
	document.getElementById('name_text').value=valuename[4];
	document.getElementById('name_posx').value=valuename[1];
	document.getElementById('name_posy').value=valuename[2];
	if(valuename[0]==1)
		obj_chk_name.checked=true;
	else
		obj_chk_name.checked=false;	
	// 内容一
	var values4 = new Array();
	values4 = strs[6].split(",");
	document.getElementById('content1_text').value=values4[4];
	document.getElementById('content1_posx').value=values4[1];
	document.getElementById('content1_posy').value=values4[2];
	if(values4[0]==1)
		obj_chk_content1.checked=true;
	else
		obj_chk_content1.checked=false;
		
	// 内容二
	var values5 = new Array();
	values5 = strs[7].split(",");
	document.getElementById('content2_text').value=values5[4];
	document.getElementById('content2_posx').value=values5[1];
	document.getElementById('content2_posy').value=values5[2];
	if(values5[0]==1)
		obj_chk_content2.checked=true;
	else
		obj_chk_content2.checked=false;
	
	// 内容三
	var values6 = new Array();
	values6 = strs[8].split(",");
	document.getElementById('content3_text').value=values6[4];
	document.getElementById('content3_posx').value=values6[1];
	document.getElementById('content3_posy').value=values6[2];
	if(values6[0]==1)
		obj_chk_content3.checked=true;
	else
		obj_chk_content3.checked=false;
	
	fun_chk_osd();
}

</SCRIPT>

</head>

<BODY bgColor=#ffffff leftMargin=0 topMargin=0 marginheight="0" marginwidth="0" onLoad="OnSelectChnno(1)">
<div id="set_display_div" style="dispaly:block;">
<table width="1080">
  <tr><td>
    <table align="left">
      <tr>
        <td class="subtitle">字符显示设置</td>
      </tr>
	  <tr><td><img src="images/break_bg.gif"></td></tr>
    </table>
  </td></tr>
</table>

<form name="enc_display_form" action="/goform/form_enc_display" method=POST>
<input type="hidden" id="submit_str" name="submit_str" value="">
<input type="hidden" id="chnno1_1_str" name="chnno1_1_str" value="<%asp_get_enc_display(1);%>">
<input type="hidden" id="chnno1_2_str" name="chnno1_2_str" value="<%asp_get_enc_display(2);%>">
<input type="hidden" id="chnno2_1_str" name="chnno2_1_str" value="<%asp_get_enc_display(3);%>">
<input type="hidden" id="chnno2_2_str" name="chnno2_2_str" value="<%asp_get_enc_display(4);%>">
<input type="hidden" id="chnno3_1_str" name="chnno3_1_str" value="<%asp_get_enc_display(5);%>">
<input type="hidden" id="chnno3_2_str" name="chnno3_2_str" value="<%asp_get_enc_display(6);%>">
<input type="hidden" id="chnno4_1_str" name="chnno4_1_str" value="<%asp_get_enc_display(7);%>">
<input type="hidden" id="chnno4_2_str" name="chnno4_2_str" value="<%asp_get_enc_display(8);%>">
<table width="1080" cellspacing="5">
	<tr><td class="lable">选择编码通道</td>
	<td>
		<select name="chnno_list" id="chnno_list" style="width: 80px;" onChange="OnChnnoChange()">
	    <option value="1">通道01</option>
		<option value="2">通道02</option>
        <option value="3">通道03</option>
		<option value="4">通道04</option>
		</select>
	</td>
	</tr>
	<tr><td class="lable">选择码流号</td>
	<td>
		<select name="streamno_list" id="streamno_list" style="width: 80px;" onChange="OnStreamnoChange()">
	    <option value="1">主码流</option>
		<option value="2">子码流</option>
		</select>
	</td>
	</tr>
	<tr><td class="lable">字体大小</td>
	<td>
		<select name="font_list" id="font_list" style="width: 80px;" onChange="OnFontChange()">
	    <!--<option value="1">16点阵</option>-->
		<option value="2">32点阵</option>
		</select>
	</td>
	</tr>
</table>
<table width="500" cellspacing="5">
	<tr>
	  <td class="lable_ex" colspan="2">日期时间显示</td>
	</tr>
	<tr>
	  <td class="lable" ><input id="chk_date" name="chk_date" type="checkbox" value="" onClick="return fun_chk_osd();">日期</td>
	  <td>
	  位置: 
		X<input type="text" id="date_posx" name="date_posx" value="" size="6"/>
		Y<input type="text" id="date_posy" name="date_posy" value="" size="6"/>
	  </td>
	</tr>
	<tr>
	  <td class="lable" ><input id="chk_time" name="chk_time" type="checkbox" value="" onClick="return fun_chk_osd();">时间</td>
	  <td>
	  位置: 
		X<input type="text" id="time_posx" name="time_posx" value="" size="6"/>
		Y<input type="text" id="time_posy" name="time_posy" value="" size="6"/>
	  </td>
	</tr>
	<tr>
	  <td class="lable" ><input id="chk_datetime" name="chk_datetime" type="checkbox" value="" onClick="return fun_chk_osd();">日期+时间</td>
	  <td>
	  位置: 
		X<input type="text" id="datetime_posx" name="datetime_posx" value="" size="6"/>
		Y<input type="text" id="datetime_posy" name="datetime_posy" value="" size="6"/>
	  </td>
	</tr>
</table>

<table width="500" cellspacing="5">
	<tr>
	  <td class="lable_ex" colspan="2">名称显示</td>
	</tr>
	<tr>
	  <td class="lable"><input id="chk_name" name="chk_name" type="checkbox" value="" onClick="return fun_chk_osd();">名称</td>
	  <td>
		名称：
		<input type="text" id="name_text" name="name_text" value="" size="40"/>
		<br>
		位置: 
		X<input type="text" id="name_posx" name="name_posx" value="" size="6"/>
		Y<input type="text" id="name_posy" name="name_posy" value="" size="6"/>
	  </td>
	</tr>
</table>

<table width="500" cellspacing="5">
	<tr>
	  <td class="lable_ex" colspan="2">内容显示</td>
	</tr>
	<tr>
	  <td class="lable"><input id="chk_content1" name="chk_content1" type="checkbox" value="" onClick="return fun_chk_osd();">内容一</td>
	  <td>
		内容：
		<input type="text" id="content1_text" name="content1_text" value="" size="40"/>
		<br>
		位置: 
		X<input type="text" id="content1_posx" name="content1_posx" value="" size="6"/>
		Y<input type="text" id="content1_posy" name="content1_posy" value="" size="6"/>
	  </td>
	</tr>
	<tr>
	  <td class="lable"><input id="chk_content2" name="chk_content2" type="checkbox" value="" onClick="return fun_chk_osd();">内容二</td>
	  <td>
		内容：
		<input type="text" id="content2_text" name="content2_text" value="" size="40"/>
		<br>
		位置: 
		X<input type="text" id="content2_posx" name="content2_posx" value="" size="6"/>
		Y<input type="text" id="content2_posy" name="content2_posy" value="" size="6"/>
	  </td>
	</tr>
	<tr>
	  <td class="lable"><input id="chk_content3" name="chk_content3" type="checkbox" value="" onClick="return fun_chk_osd();">内容三</td>
	  <td>
		内容：
		<input type="text" id="content3_text" name="content3_text" value="" size="40"/>
		<br>
		位置: 
		X<input type="text" id="content3_posx" name="content3_posx" value="" size="6"/>
		Y<input type="text" id="content3_posy" name="content3_posy" value="" size="6"/>
	  </td>
	</tr>
</table>

<table width="1080">
<tr><td>
	<input type="submit" id="enc_display_submit" name="enc_display_submit" 
		style="border:none;background:url(images/save_btn.png);width:83px;height:20px;cursor:hand;" 
		onclick="return fun_enc_display_submit();" value=""/>
  </td>
</tr>
</table>

</form>
</div>

<div id="setting_display_tip_div" style="display:none;">
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
