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
function startdynamic()
{
	var obj   = document.getElementById("channellist");
	var index = obj.selectedIndex;
	var chn_nov = obj.options[index].value;
	var chn_urlv = document.dynamic_form.channelurl.value;
	index = document.dynamic_form.fpslist.selectedIndex;
	var chn_fpsv = document.dynamic_form.fpslist.options[index].value;
	chn_urlv = chn_urlv.Trim();
	if(chn_urlv.length==0)
	{
		alert("请设置解码通道的URL");
		document.dynamic_form.channelurl.focus();
		document.dynamic_form.channelurl.select();
		return false;
	}
	if( ! confirm("即将启动解码，是否继续？") )
	{
		return false;
	}
	document.dynamic_form.chn_URL.value=chn_urlv;
	document.dynamic_form.chn_NO.value=chn_nov;
	document.dynamic_form.chn_FPS.value=chn_fpsv;
	document.getElementById('set_dynamic_div').style.display="none";
	document.getElementById('setting_dynamic_tip_div').style.display="block";
	//document.dynamic_form.submit();
	return true;
}
function stopdynamic()
{
	if( ! confirm("即将停止解码，是否继续？") )
	{
		return false;
	}
	var obj   = document.getElementById("channellist");
	var index = obj.selectedIndex;
	var chn_nov = obj.options[index].value;

	document.dynamic_form.chn_URL.value="";
	document.dynamic_form.chn_NO.value=chn_nov;
	document.dynamic_form.chn_FPS.value=30;
	document.getElementById('set_dynamic_div').style.display="none";
	document.getElementById('setting_dynamic_tip_div').style.display="block";
	//document.dynamic_form.submit();
	return true;
}
function OnSelectChn()
{
	var obj   = document.getElementById("channellist");
	var index = obj.selectedIndex;
	var chn_nov = obj.options[index].value;
	var obj_url_str = "chan" + chn_nov + "_URL";
	var obj_fps_str = "chan" + chn_nov + "_FPS";
	var fps_value = document.getElementById(obj_fps_str).value;
	document.dynamic_form.channelurl.value=document.getElementById(obj_url_str).value;
	document.dynamic_form.fpslist.selectedIndex=parseInt(fps_value) - 1;
}
</SCRIPT>

<style type="text/css">
<!--
.STYLE6 {font-size: 13px; }
-->
</style>
</head>

<BODY bgColor=#ffffff leftMargin=0 topMargin=0 marginheight="0" marginwidth="0" onLoad="OnSelectChn()">
<input type="hidden" id="dec_chn_cnt" name="dec_chn_cnt" value="<%asp_get_chn_cnt(1);%>">
<div id="set_dynamic_div" style="dispaly:block;">
<table width="1080">
  <tr><td>
    <table align="left">
      <tr>
        <td class="subtitle">动态解码</td>
      </tr>
	  <tr><td><img src="images/break_bg.gif"></td></tr>
    </table>
  </td></tr>
</table>

<form id="dynamic_form" name="dynamic_form" action="/goform/form_dec_set_dynamic" method=POST>

<input type="hidden" id="chan1_FPS" name="chan1_FPS" value="<%asp_get_chn_fps(1);%>">
<input type="hidden" id="chan2_FPS" name="chan2_FPS" value="<%asp_get_chn_fps(2);%>">
<input type="hidden" id="chan3_FPS" name="chan3_FPS" value="<%asp_get_chn_fps(3);%>">
<input type="hidden" id="chan4_FPS" name="chan4_FPS" value="<%asp_get_chn_fps(4);%>">
<input type="hidden" id="chan5_FPS" name="chan5_FPS" value="<%asp_get_chn_fps(5);%>">
<input type="hidden" id="chan6_FPS" name="chan6_FPS" value="<%asp_get_chn_fps(6);%>">
<input type="hidden" id="chan7_FPS" name="chan7_FPS" value="<%asp_get_chn_fps(7);%>">
<input type="hidden" id="chan8_FPS" name="chan8_FPS" value="<%asp_get_chn_fps(8);%>">
<input type="hidden" id="chan9_FPS" name="chan9_FPS" value="<%asp_get_chn_fps(9);%>">
<input type="hidden" id="chan10_FPS" name="chan10_FPS" value="<%asp_get_chn_fps(10);%>">
<input type="hidden" id="chan11_FPS" name="chan11_FPS" value="<%asp_get_chn_fps(11);%>">
<input type="hidden" id="chan12_FPS" name="chan12_FPS" value="<%asp_get_chn_fps(12);%>">
<input type="hidden" id="chan13_FPS" name="chan13_FPS" value="<%asp_get_chn_fps(13);%>">
<input type="hidden" id="chan14_FPS" name="chan14_FPS" value="<%asp_get_chn_fps(14);%>">
<input type="hidden" id="chan15_FPS" name="chan15_FPS" value="<%asp_get_chn_fps(15);%>">
<input type="hidden" id="chan16_FPS" name="chan16_FPS" value="<%asp_get_chn_fps(16);%>">

<input type="hidden" id="chan1_URL" name="chan1_URL" value="<%asp_get_chn_url(1);%>">
<input type="hidden" id="chan2_URL" name="chan2_URL" value="<%asp_get_chn_url(2);%>">
<input type="hidden" id="chan3_URL" name="chan3_URL" value="<%asp_get_chn_url(3);%>">
<input type="hidden" id="chan4_URL" name="chan4_URL" value="<%asp_get_chn_url(4);%>">
<input type="hidden" id="chan5_URL" name="chan5_URL" value="<%asp_get_chn_url(5);%>">
<input type="hidden" id="chan6_URL" name="chan6_URL" value="<%asp_get_chn_url(6);%>">
<input type="hidden" id="chan7_URL" name="chan7_URL" value="<%asp_get_chn_url(7);%>">
<input type="hidden" id="chan8_URL" name="chan8_URL" value="<%asp_get_chn_url(8);%>">
<input type="hidden" id="chan9_URL" name="chan9_URL" value="<%asp_get_chn_url(9);%>">
<input type="hidden" id="chan10_URL" name="chan10_URL" value="<%asp_get_chn_url(10);%>">
<input type="hidden" id="chan11_URL" name="chan11_URL" value="<%asp_get_chn_url(11);%>">
<input type="hidden" id="chan12_URL" name="chan12_URL" value="<%asp_get_chn_url(12);%>">
<input type="hidden" id="chan13_URL" name="chan13_URL" value="<%asp_get_chn_url(13);%>">
<input type="hidden" id="chan14_URL" name="chan14_URL" value="<%asp_get_chn_url(14);%>">
<input type="hidden" id="chan15_URL" name="chan15_URL" value="<%asp_get_chn_url(15);%>">
<input type="hidden" id="chan16_URL" name="chan16_URL" value="<%asp_get_chn_url(16);%>">

<input type="hidden" id="chn_URL" name="chn_URL" value="">
<input type="hidden" id="chn_NO" name="chn_NO" value="">
<input type="hidden" id="chn_FPS" name="chn_FPS" value="">

<table width="1080" border="0" cellpadding="6" align="left">
	<tr>
	<td class="lable">选择解码通道</td>
	<td>
	  <select name="channellist" id="channellist" style="width: 120px;" onChange="OnSelectChn()">
			<SCRIPT type=text/javascript >
			for(i=1; i<=16; i++)
			{
				if(i==1)
				{
					document.writeln("<option value='" + i + "' selected>解码通道" + i + "</option>");
				}
				else
				{
					document.writeln("<option value='" + i + "'>解码通道" + i + "</option>");
				}
			}
			</SCRIPT>
	  </select>
	</td>
	</tr>
    <tr>
	<td class="lable">URL</td>
	<td>
	  <input id="channelurl" name="channelurl" type="text" value="" size="50">
	</td>
	</tr>
	<tr>
	<td class="lable">FPS</td>
	<td>
	  <select name="fpslist" id="fpslist" style="width: 60px;" onChange="">
			<SCRIPT type=text/javascript >
			for(i=1; i<=36; i++)
			{
				if(i==30)
				{
					document.writeln("<option value='" + i + "' selected>" + i + "</option>");
				}
				else
				{
					document.writeln("<option value='" + i + "' >" + i + "</option>");
				}
			}
			</SCRIPT>
	  </select>
	</td>
	</tr>
	<tr>
	<td>
		<input type="submit" name="dec_startdynamic_submit" 
		style="border:none;background:url(images/startdec_btn.png);width:83px;height:20px;cursor:hand;" 
		onclick="return startdynamic();" value=""/>
	</td>
	<td>
		<input type="submit" name="dec_stopdynamic_submit" 
		style="border:none;background:url(images/stopdec_btn.png);width:83;height:20;cursor:hand;" 
		onclick="return stopdynamic();" value=""/>
	</td>
	</tr>
</table>
</form>
<p><br>
  <br>
</p>
<p>&nbsp;</p>
<p>&nbsp;</p>
<p>&nbsp;</p>
<p>&nbsp;</p>
<table width="343">
<tr>
<td colspan="2" bgcolor="#CCCCCC"><p class="STYLE6"><img src="images/tip_24.gif" width="24" height="24">URL格式说明:
  </p>
  <p class="STYLE6"><br>
  </p></td>
</tr>
<tr>
  <td width="98" bgcolor="#CCCCCC"><span class="STYLE6">UDP方式</span></td>
  <td width="233" bgcolor="#CCCCCC"><span class="STYLE6">udp/IP地址:端口</span></td>
</tr>
<tr>
  <td bgcolor="#CCCCCC"><span class="STYLE6">TCP服务端方式</span></td>
  <td bgcolor="#CCCCCC"><span class="STYLE6">tcp/端口</span></td>
</tr>
<tr>
  <td bgcolor="#CCCCCC"><span class="STYLE6">TCP客户端方式</span></td>
  <td bgcolor="#CCCCCC"><span class="STYLE6">tcp/IP地址:端口</span></td>
</tr>
<tr>
  <td bgcolor="#CCCCCC"><span class="STYLE6">RTSP方式</span></td>
  <td bgcolor="#CCCCCC"><span class="STYLE6">rtsp://IP地址:端口/...</span></td>
</tr>
</table>
</div>

<div id="setting_dynamic_tip_div" style="display:none;">
<table>
	<tr>
		<td width="512" height="200" bgcolor="#FEF9E9" align="center">
			<img src="images/loading_01.gif">
			<br><br>
			正在应用中,请稍等，勿操作网页......
		</td>
	</tr>
</table>
</div>

</body>
</html>