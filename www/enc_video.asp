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
function fun_enc_video_submit()
{
	var obj_chnno = document.getElementById("enc_chn_no_list");
	var obj_streamno = document.getElementById("stream_no_list");
	var obj_resolution = document.getElementById("resolution_list");
	var obj_fps = document.getElementById("fps");
	var obj_gop = document.getElementById("gop");
	var obj_brmode = document.getElementById("br_mode_list");
	var obj_codecsize = document.getElementById("codecsize");
	var obj_profile = document.getElementById("profile_list");
	var obj_ptztype = document.getElementById("ptz_type_list");
	var obj_addrcode = document.getElementById("ptz_addrcode");

	var submit_str = "";
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

	var resno = obj_resolution.selectedIndex;
	submit_str += resno;
	submit_str += ";";
	
	var fps_value = obj_fps.value;
	if(isNaN(fps_value) || fps_value<1 || fps_value>25 || fps_value=="")
	{
		alert("帧率数值范围：1-25");
		obj_fps.focus();
		obj_fps.select();
		return false;
	}
	

	submit_str += fps_value;
	submit_str += ";";

	var gop_value = obj_gop.value;
	if( isNaN(gop_value) || gop_value=="")
	{
		alert("I帧间隔数值错误！");
		obj_gop.focus();
		obj_gop.select();
		return false;
	}
	submit_str += gop_value;
	submit_str += ";";

	var brmode = obj_brmode.selectedIndex;
	submit_str += brmode;
	submit_str += ";";

	var codec_size = obj_codecsize.value;
	if( isNaN(codec_size) || codec_size=="")
	{
		alert("码流大小数值错误！");
		obj_codecsize.focus();
		obj_codecsize.select();
		return false;
	}
	submit_str += codec_size;
	submit_str += ";";
	
	var profile = obj_profile.selectedIndex;
	submit_str += profile + ";";
	
	var ptztype = obj_ptztype.selectedIndex;
	submit_str += ptztype + ";";

	var ptzaddrcode = obj_addrcode.value;
	if( isNaN(ptzaddrcode) )
	{
		alert("PTZ地址码数值错误！");
		obj_addrcode.focus();
		obj_addrcode.select();
		return false;
	}
	if(ptzaddrcode=="")
	{
		ptzaddrcode = " ";
	}
	submit_str += ptzaddrcode + ";";
	
	document.getElementById("submit_str").value = submit_str;
	// 界面显示控制
	document.getElementById('set_video_div').style.display="none";
	document.getElementById('setting_video_tip_div').style.display="block";
	return true;
}
function OnEncChnnoChange()
{
	var obj_chnno = document.getElementById("enc_chn_no_list");
	var index_chnno  = obj_chnno.selectedIndex + 1;
	var num = index_chnno * 2 - 1;// 默认选择主码流
	OnSelectEncChnno(num);
}
function OnEncStreamNoChange()
{
	var obj_chnno = document.getElementById("enc_chn_no_list");
	var index_chnno  = obj_chnno.selectedIndex + 1;
	var obj_streamno = document.getElementById("stream_no_list");
	var index_streamno = obj_streamno.selectedIndex;
	var num = 0;
	if(index_streamno == 0)// 主码流
	{
		num = index_chnno * 2 -1;
	}
	else // 子码流
	{
		num = index_chnno * 2;
	}
	OnSelectEncChnno(num);
}
function OnSelectEncChnno(num)
{
	var obj_chnno = document.getElementById("enc_chn_no_list");
	var obj_streamno = document.getElementById("stream_no_list");
	var obj_resolution = document.getElementById("resolution_list");
	var obj_fps = document.getElementById("fps");
	var obj_gop = document.getElementById("gop");
	var obj_brmode = document.getElementById("br_mode_list");
	var obj_codecsize = document.getElementById("codecsize");
	var obj_profile = document.getElementById("profile_list");
	var obj_ptztype = document.getElementById("ptz_type_list");
	var obj_addrcode = document.getElementById("ptz_addrcode");
	
	//通道号（1-通道1、主码流，2-通道1、子码流，3-通道2、主码流，。。。依次类推），分辨率，帧率，I帧间隔，码率控制，码流大小，编码规格，PTZ类型，PTZ地址码
	//var str1="2;3;25;10;1;4000;2;0;1;";
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
	var str = document.getElementById(obj_str).value;

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
	// 分辨率、帧率、I间隔
	var resno = parseInt(strs[1]);
	obj_resolution.selectedIndex = resno;
	var fps_value = parseInt(strs[2]);
	obj_fps.value = fps_value;	
	var gop_value = parseInt(strs[3]);
	obj_gop.value = gop_value;
	// 码率控制、码流大小
	var brmodeno = parseInt(strs[4]);
	var codecsize = parseInt(strs[5]);
	obj_brmode.selectedIndex = brmodeno;
	obj_codecsize.value = codecsize;
	//编码规格
	var profile = parseInt(strs[6]);
	obj_profile.selectedIndex = profile;
	// PTZ类型、地址码
	var ptz_type = parseInt(strs[7]);
	var ptz_addrcode = parseInt(strs[8]);
	obj_ptztype.selectedIndex = ptz_type;
	obj_addrcode.value = ptz_addrcode;
}
function OnResolutionChange()
{
	var obj_resolution = document.getElementById("resolution_list");
	var obj_codecsize = document.getElementById("codecsize");
	var res_i = obj_resolution.selectedIndex;
	switch(res_i)
	{
		case 0: //qcif
			obj_codecsize.value = 800;
			break;
		case 1: //cif
			obj_codecsize.value = 1000;
			break;
		case 2: //d1
			obj_codecsize.value = 1500;
			break;
		case 3: //720p
			obj_codecsize.value = 4000;
			break;
		case 4: //1080p
			obj_codecsize.value = 6000;
			break;
	}
}
</SCRIPT>

</head>

<BODY bgColor=#ffffff leftMargin=0 topMargin=0 marginheight="0" marginwidth="0" onLoad="OnSelectEncChnno(1)">
<div id="set_video_div" style="dispaly:block;">
<table width="1080">
  <tr><td>
    <table align="left">
      <tr>
        <td class="subtitle">视频设置</td>
      </tr>
	  <tr><td><img src="images/break_bg.gif"></td></tr>
    </table>
  </td></tr>
</table>

<form name="enc_video_form" action="/goform/form_enc_video" method=POST>
  <p>
    
<input type="hidden" id="submit_str" name="submit_str" value="">
<!---->
<input type="hidden" id="enc_chn_count" name="enc_chn_count" value="<%asp_get_chn_cnt(2);%>">
<input type="hidden" id="chnno1_1_str" name="chnno1_1_str" value="<%asp_get_enc_video(1);%>">
<input type="hidden" id="chnno1_2_str" name="chnno1_2_str" value="<%asp_get_enc_video(2);%>">
<input type="hidden" id="chnno2_1_str" name="chnno2_1_str" value="<%asp_get_enc_video(3);%>">
<input type="hidden" id="chnno2_2_str" name="chnno2_2_str" value="<%asp_get_enc_video(4);%>">
<input type="hidden" id="chnno3_1_str" name="chnno3_1_str" value="<%asp_get_enc_video(5);%>">
<input type="hidden" id="chnno3_2_str" name="chnno3_2_str" value="<%asp_get_enc_video(6);%>">
<input type="hidden" id="chnno4_1_str" name="chnno4_1_str" value="<%asp_get_enc_video(7);%>">
<input type="hidden" id="chnno4_2_str" name="chnno4_2_str" value="<%asp_get_enc_video(8);%>">
	</p>
  <table width="1080" cellspacing="5">
	<tr><td class="lable">选择编码通道</td>
	<td>
		<select name="enc_chn_no_list" id="enc_chn_no_list" style="width: 120px;" onChange="OnEncChnnoChange()">
	    <option value="1">通道01</option>
		<option value="2">通道02</option>
        <option value="3">通道03</option>
		<option value="4">通道04</option>
		</select>
	</td>
	</tr>
	<tr>
	<td class="lable">选择码流号</td>
	<td>
		<select name="stream_no_list" id="stream_no_list" style="width: 120px;" onChange="OnEncStreamNoChange()">
	    <option value="1">主码流</option>
		<option value="2">子码流</option>
		</select>
	</td>
	</tr>
    <tr><td class="lable">输出分辨率</td>
	<td>
	  <select name="resolution_list" id="resolution_list" style="width: 120px;" onChange="OnResolutionChange()">
	    <option value="1">QCIF</option>
		<option value="2">CIF</option>
		<option value="3">D1</option>
		<option value="4">720P</option>
		<option value="5">1080P</option>
	  </select>
	</td>
	</tr>
	<tr>
	  <td class="lable">帧率[1-25]</td>
	  <td>
	  <input id="fps" name="fps" type="text" value="" size="12">
	  </td>
	</tr>
	<tr>
	  <td class="lable">I帧间隔</td>
	  <td>
	  <input id="gop" name="gop" type="text" value="" size="12">
	  </td>
	</tr>
	<tr>
	  <td class="lable">码率控制</td>
	  <td>
	  <select name="br_mode_list" id="br_mode_list" style="width: 120px;" onChange="">
	    <option value="1">固定码率</option>
	    <option value="2">可变码率</option>
	  </select>
	  </td>
	</tr>
	<tr>
	  <td class="lable">码流大小</td>
	  <td>
	  <input id="codecsize" name="codecsize" type="text" value="" size="12">
	  </td>
	</tr>
	<tr>
	  <td class="lable">编码规格</td>
	  <td>
	  	<select name="profile_list" id="profile_list" style="width: 120px;" onChange="">
		<option value="0">baseline</option>
	    <option value="1">main profile</option>
	    <option value="2">high profile</option>
	    </select>
	  </td>
	</tr>
	<tr>
	  <td class="lable">PTZ协议类型</td>
	  <td>
	  <select name="ptz_type_list" id="ptz_type_list" style="width: 120px;" onChange="">
	    <option value="1">PelcoD</option>
	  </select>
	  </td>
	</tr>
	<tr>
	  <td class="lable">PTZ地址码</td>
	  <td>
	  <input id="ptz_addrcode" name="ptz_addrcode" type="text" value="" size="12">
	  </td>
	</tr>
	<tr>
	  <td>
	    <input type="submit" name="enc_video_submit" 
			style="border:none;background:url(images/save_btn.png);width:83px;height:20px;cursor:hand;" 
			onclick="return fun_enc_video_submit();" value=""/>
	  </td>
	  <td></td>
	</tr>
</table>
</form>
</div>
<div id="setting_video_tip_div" style="display:none;">
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