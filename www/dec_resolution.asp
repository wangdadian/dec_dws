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
function check_resolution()
{
	var obj_displayno = document.getElementById("displayno_list");
	var index_displayno  = obj_displayno.selectedIndex;
	var value_displayno   = obj_displayno.options[index_displayno].value;
	
	var obj_resolution   = document.getElementById("resolution_list");
	var index_resolution = obj_resolution.selectedIndex;
	var value_resolution = obj_resolution.options[index_resolution].value;
	if(value_resolution==0)
	{
		//alert("请选择输出分辨率");
		//return false;
	}

	var obj_channel = document.getElementById("channellist");
	var index_channel = obj_channel.selectedIndex;
	var value_channel = obj_channel.options[index_channel].value;
	if(value_channel==0)
	{
		//alert("请关联解码通道");
		//return false;
	}
	
	//设置提交表单的数据，分辨率及关联通道
	document.resolution_form.displayno.value=value_displayno;
	document.resolution_form.resolution.value=value_resolution;
	document.resolution_form.channel.value=value_channel;	
	document.getElementById('set_res_div').style.display="none";
	document.getElementById('setting_res_tip_div').style.display="block";
	//document.resolution_form.submit();
	return true;
}

function SelectDisplayno(displayno)
{
	var displaymode=parseInt(document.resolution_form.displaymode.value);
	var resolutionlist="";
	var channellist="";
	if(displaymode==1)
	{
		resolutionlist=document.resolution_form.vga_resolution.value;
		channellist=document.resolution_form.vga_chn.value;
	}
	else if(displaymode==2)
	{
		resolutionlist=document.resolution_form.bnc_resolution.value;
		channellist=document.resolution_form.bnc_chn.value;
	}
	else if(displaymode==3)
	{
		resolutionlist=document.resolution_form.hdmi_resolution.value;
		channellist=document.resolution_form.hdmi_chn.value;
	}
	else
	{
		return false;
	}

	var obj_displayno = document.getElementById("displayno_list");
	var obj_resolution   = document.getElementById("resolution_list");
	var obj_channel = document.getElementById("channellist");
	var index_resolution=0;
	var index_channel=0;
	var tmp_i=0;
	
	obj_displayno.selectedIndex=(displayno-1);
	for(var i=0; i<obj_displayno.options.length; i++)
	{
		tmp_i = i+1;
		if(displayno==tmp_i)
		{
			//例如： "1,2,3,4,5"
			var res_values=new Array();
			var chn_values=new Array();
			res_values=resolutionlist.split(",");
			chn_values=channellist.split(",");
			index_channel = chn_values[i];
			index_resolution = res_values[i];
			if(index_channel == 128)//组合模式2x2
			{
				obj_channel.selectedIndex=obj_channel.options.length-3;
			}
            else if(index_channel == 129)//组合模式3x3
            {
                obj_channel.selectedIndex=obj_channel.options.length-2;
            }
            else if(index_channel == 130)//组合模式4x4
            {
                obj_channel.selectedIndex=obj_channel.options.length-1;
            }
			else
			{
				obj_channel.selectedIndex=index_channel;
			}
			obj_resolution.selectedIndex=index_resolution;
			break;
		}
	}
	return true;
}
function OnSelectDisplayno()
{
	var obj_displayno = document.getElementById("displayno_list");
	var index_displayno  = obj_displayno.selectedIndex;
	var value_displayno   = obj_displayno.options[index_displayno].value;	
	SelectDisplayno(value_displayno);
	return true;
}

function select_vga()
{
	// 显示界面
	document.getElementById("a_vga").className="a_page_sel";
	document.getElementById("a_bnc").className="a_page";
	document.getElementById("a_hdmi").className="a_page";
	
	// 设置表单提交数据的显示模式
	document.resolution_form.displaymode.value="1";	
	// 处理分辨率显示、通道号显示
	SelectDisplayno(1);
}
function osd_show_load()
{
	var value_osdshow_str = document.osd_form.osd_showed.value;
	var obj_osd_show = document.getElementById("osd_show_enabled");
	var obj_osd_mid_show = document.getElementById("osd_show_mid_enabled");
	
	var osdshow_values=new Array();
	osdshow_values=value_osdshow_str.split(",");
	if(osdshow_values.length<2)
	{
		return;
	}
	var info_show = osdshow_values[0];
	var mid_show = osdshow_values[1];
	
	if(info_show==0)
	{
		obj_osd_show.selectedIndex = 0;
	}
	else
	{
		obj_osd_show.selectedIndex = 1;
	}
	if(mid_show==0)
	{
		obj_osd_mid_show.selectedIndex = 0;
	}
	else
	{
		obj_osd_mid_show.selectedIndex = 1;
	}
}
function MyOnLoad()
{
	select_vga();
	osd_show_load();
}
function select_bnc()
{
	// 显示界面
	document.getElementById("a_vga").className="a_page";
	document.getElementById("a_bnc").className="a_page_sel";
	document.getElementById("a_hdmi").className="a_page";
	// 设置表单提交数据的显示模式
	document.resolution_form.displaymode.value="2";
	
	// 处理分辨率显示、通道号显示
	SelectDisplayno(1);
}
function select_hdmi()
{
	// 显示界面
	document.getElementById("a_vga").className="a_page";
	document.getElementById("a_bnc").className="a_page";
	document.getElementById("a_hdmi").className="a_page_sel";
	// 设置表单提交数据的显示模式
	document.resolution_form.displaymode.value="3";
	
	// 处理分辨率显示、通道号显示
	SelectDisplayno(1);
}
function osd_show()
{
	var obj_osd_show = document.getElementById("osd_show_enabled");
	var index_osdshow  = obj_osd_show.selectedIndex;
	var value_osdshow   = obj_osd_show.options[index_osdshow].value;
	document.osd_form.osd_showed.value=value_osdshow;
	
	var obj_osd_show_mid = document.getElementById("osd_show_mid_enabled");
	var index_osdshowmid  = obj_osd_show_mid.selectedIndex;
	var value_osdshowmid   = obj_osd_show_mid.options[index_osdshowmid].value;
	document.osd_form.osd_mid_showed.value=value_osdshowmid;
	
	document.getElementById('set_res_div').style.display="none";
	document.getElementById('setting_res_tip_div').style.display="block";
	return true;
}
</SCRIPT>

</head>

<BODY bgColor=#ffffff leftMargin=0 topMargin=0 marginheight="0" marginwidth="0" onLoad="MyOnLoad()">
<div id="set_res_div" style="dispaly:block;">
<table width="1080">
  <tr><td>
    <table align="left">
      <tr>
        <td class="subtitle">分辨率设置</td>
      </tr>
	  <tr><td><img src="images/break_bg.gif"></td></tr>
    </table>
  </td></tr>
</table>

<table width="1080" border="0" cellpadding="6" align="left">
    <tr>
	<!--<td class="lable">绑定输出接口</td>-->
	<td>
	  <a href="#" class="a_page_sel" id="a_vga" name="a_vga"  onClick="select_vga()"/>VGA显示</a>&nbsp;|
      <a href="#" class="a_page" id="a_bnc" name="a_bnc"  onClick="select_bnc()"/>BNC显示</a>&nbsp;|
	  <a href="#" class="a_page" id="a_hdmi" name="a_hdmi" onClick="select_hdmi()"/>HDMI显示</a>&nbsp;|
	</td>
	</tr>
</table>
<form name="resolution_form" action="/goform/form_dec_set_resolution" method=POST>
  <p>&nbsp;</p>
  <p>&nbsp;</p>
  <p>
    <input type="hidden" id="vga_resolution" name="vga_resolution" value="<%asp_get_resolution(1);%>">
    <input type="hidden" id="vga_chn" name="vga_chn" value="<%asp_get_resolution_chn(1);%>">
	
    <input type="hidden" id="bnc_resolution" name="bnc_resolution" value="<%asp_get_resolution(2);%>">
    <input type="hidden" id="bnc_chn" name="bnc_chn" value="<%asp_get_resolution_chn(2);%>">
	
    <input type="hidden" id="hdmi_resolution" name="hdmi_resolution" value="<%asp_get_resolution(3);%>">
    <input type="hidden" id="hdmi_chn" name="hdmi_chn" value="<%asp_get_resolution_chn(3);%>">
    <!---->
	<input type="hidden" id="displayno" name="displayno" value="0">
    <input type="hidden" id="resolution" name="resolution" value="0">
    <input type="hidden" id="channel" name="channel" value="0">
    <input type="hidden" id="displaymode" name="displaymode" value="0">
	
    <!---->
	</p>
  <table width="1080">
	<tr><td class="lable">选择显示通道</td>
	<td>
		<select name="displayno_list" id="displayno_list" style="width: 120px;" onChange="OnSelectDisplayno()">
	    <option value="1">显示通道01</option>
		</select>
	</td>
	</tr>
    <tr><td class="lable">输出分辨率</td>
	<td>
	  <select name="resolution_list" id="resolution_list" style="width: 120px;">
		<option value="0">未设置</option>
	    <option value="1">1920*1080</option>
		<option value="2">800*600</option>
		<option value="3">1024*768</option>
		<option value="4">1280*1024</option>
		<option value="5">1366*768</option>
		<option value="6">1440*900</option>
		<option value="7">1280*800</option>
	  </select>
	</td>
	</tr>
	<tr>
	  <td class="lable">关联解码通道</td>
	  <td>
	  <select name="channellist" id="channellist" style="width: 120px;" onChange="OnSelectChn()">
	    <option value="0">未设置</option>
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
		<option value="128">组合通道2x2</option>
        <option value="129">组合通道3x3</option>
        <option value="130">组合通道4x4</option>
	  </select>
	  </td>
	</tr>
	<tr>
	  <td>
	    <input type="submit" name="dec_resolution_submit" 
			style="border:none;background:url(images/save_btn.png);width:83px;height:20px;cursor:hand;" 
			onclick="return check_resolution();" value=""/>
	  </td>
	  <td></td>
	</tr>
</table>
</form>

<table >
  <tr>
  <td>
    <table>
    <tr>
      <td class="subtitle">OSD设置</td>
    </tr>
	<tr><td><img src="images/break_bg.gif"></td></tr>
    </table>
   </td>
   </tr>
   </table>
<form name="osd_form" action="/goform/form_dec_osd" method=POST>
<input type="hidden" id="osd_showed" name="osd_showed" value="<%asp_get_dec_osdshow();%>">
<input type="hidden" id="osd_mid_showed" name="osd_mid_showed" value="">
   <table>
	<tr>
	<td class="lable">OSD显示</td>
	<td>
		<select name="osd_show_enabled" id="osd_show_enabled" style="width: 130px;" onChange="">
	    <option value="0">关闭</option>
		<option value="1">打开</option>
		</select>
	</td>
	</tr>
	<tr>
	<td class="lable">显示监视器号</td>
	<td>
		<select name="osd_show_mid_enabled" id="osd_show_mid_enabled" style="width: 130px;" onChange="">
	    <option value="0">关闭</option>
		<option value="1">打开</option>
		</select>
	</td>
	</tr>
	<tr>
	  <td>
	    <input type="submit" name="dec_osd_submit" 
			style="border:none;background:url(images/save_btn.png);width:83px;height:20px;cursor:hand;" 
			onclick="return osd_show();" value=""/>
	  </td>
	  <td></td>
	</tr>
</table>
</form>
</div>
<div id="setting_res_tip_div" style="display:none;">
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