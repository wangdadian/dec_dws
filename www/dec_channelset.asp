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
function set_channel()
{
	var obj   = document.getElementById("channellist");
	var index = obj.selectedIndex;
	var chn_nov = obj.options[index].value;
	var chn_code = document.chnset_form.channel_code.value;
	chn_code = chn_code.Trim();

	document.chnset_form.chn_CODE.value=chn_code;
	document.chnset_form.chn_NO.value=chn_nov;

	document.getElementById('set_chnset_div').style.display="none";
	document.getElementById('setting_chnset_tip_div').style.display="block";
	return true;
}

function OnSelectChn()
{
	var obj   = document.getElementById("channellist");
	var index = obj.selectedIndex;
	var chn_nov = obj.options[index].value;
	var obj_code_str = "chan" + chn_nov + "_CODE";
	document.chnset_form.channel_code.value=document.getElementById(obj_code_str).value;
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
<div id="set_chnset_div" style="dispaly:block;">
<table width="1080">
  <tr><td>
    <table align="left">
      <tr>
        <td class="subtitle">通道设置</td>
      </tr>
	  <tr><td><img src="images/break_bg.gif"></td></tr>
    </table>
  </td></tr>
</table>

<form name="chnset_form" action="/goform/form_dec_set_channel" method=POST>

<input type="hidden" id="chan1_CODE" name="chan1_CODE" value="<%asp_get_chn_code(1);%>">
<input type="hidden" id="chan2_CODE" name="chan2_CODE" value="<%asp_get_chn_code(2);%>">
<input type="hidden" id="chan3_CODE" name="chan3_CODE" value="<%asp_get_chn_code(3);%>">
<input type="hidden" id="chan4_CODE" name="chan4_CODE" value="<%asp_get_chn_code(4);%>">
<input type="hidden" id="chan5_CODE" name="chan5_CODE" value="<%asp_get_chn_code(5);%>">
<input type="hidden" id="chan6_CODE" name="chan6_CODE" value="<%asp_get_chn_code(6);%>">
<input type="hidden" id="chan7_CODE" name="chan7_CODE" value="<%asp_get_chn_code(7);%>">
<input type="hidden" id="chan8_CODE" name="chan8_CODE" value="<%asp_get_chn_code(8);%>">
<input type="hidden" id="chan9_CODE" name="chan9_CODE" value="<%asp_get_chn_code(9);%>">
<input type="hidden" id="chan10_CODE" name="chan10_CODE" value="<%asp_get_chn_code(10);%>">
<input type="hidden" id="chan11_CODE" name="chan11_CODE" value="<%asp_get_chn_code(11);%>">
<input type="hidden" id="chan12_CODE" name="chan12_CODE" value="<%asp_get_chn_code(12);%>">
<input type="hidden" id="chan13_CODE" name="chan13_CODE" value="<%asp_get_chn_code(13);%>">
<input type="hidden" id="chan14_CODE" name="chan14_CODE" value="<%asp_get_chn_code(14);%>">
<input type="hidden" id="chan15_CODE" name="chan15_CODE" value="<%asp_get_chn_code(15);%>">
<input type="hidden" id="chan16_CODE" name="chan16_CODE" value="<%asp_get_chn_code(16);%>">


<input type="hidden" id="chn_CODE" name="chn_CODE" value="">
<input type="hidden" id="chn_NO" name="chn_NO" value="">


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
	<td class="lable">编号</td>
	<td>
	  <input id="channel_code" name="channel_code" type="text" value="" size="50">
	</td>
	</tr>
	<tr>
	<td>
		<input type="submit" name="dec_startdynamic_submit" 
		style="border:none;background:url(images/save_btn.png);width:83px;height:20px;cursor:hand;" 
		onclick="return set_channel();" value=""/>
	</td>
	</tr>
</table>
</form>
</div>

<div id="setting_chnset_tip_div" style="display:none;">
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