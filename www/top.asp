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

function Run_exitsystem()
{
    var msg = "确定注销吗？";
    //if( confirm(msg) )
    {
        document.formlogin.target="_parent";
        document.formlogin.submit();
        return true;
    }
    //return false;
}
function select_dec()
{
	// 显示界面
	document.getElementById("a_dec").className="a_tool_bar_sel";
	document.getElementById("a_enc").className="a_tool_bar";
	document.getElementById("a_param").className="a_tool_bar";
	document.getElementById("a_dev").className="a_tool_bar";
}

function select_enc()
{
	// 显示界面
	document.getElementById("a_dec").className="a_tool_bar";
	document.getElementById("a_enc").className="a_tool_bar_sel";
	document.getElementById("a_param").className="a_tool_bar";
	document.getElementById("a_dev").className="a_tool_bar";
}
function select_param()
{
	// 显示界面
	document.getElementById("a_dec").className="a_tool_bar";
	document.getElementById("a_enc").className="a_tool_bar";
	document.getElementById("a_param").className="a_tool_bar_sel";
	document.getElementById("a_dev").className="a_tool_bar";
}

function select_dev()
{
	// 显示界面
	document.getElementById("a_dec").className="a_tool_bar";
	document.getElementById("a_enc").className="a_tool_bar";
	document.getElementById("a_param").className="a_tool_bar";
	document.getElementById("a_dev").className="a_tool_bar_sel";
}
function MyLoad()
{
	var model_str = document.getElementById("get_dev_model").value;
	var model = parseInt(model_str);
	var company = 0; // 0-mingding 1-bocom
	if(model == 0) // 标清编码器
	{
		if(company==0) // mingding
		{
			document.getElementById("top_tab").style.background="url(images/top_bg_sdenc.jpg)";
		}
		else if(company==1) // bocom
		{
			document.getElementById("top_tab").style.background="url(images/top_bg_sdenc_bocom.jpg)";
		}
		
		document.getElementById("dec").style.display="none";
		document.getElementById("enc").style.display="block";
	}
	else if(model == 1)// 高清编码器
	{
		if(company==0) // mingding
		{
			document.getElementById("top_tab").style.background="url(images/top_bg_hdenc.jpg)";
		}
		else if(company==1) // bocom
		{
			document.getElementById("top_tab").style.background="url(images/top_bg_hdenc_bocom.jpg)";
		}
		
		document.getElementById("dec").style.display="none";
		document.getElementById("enc").style.display="block";
	}
	else if(model == 2)// 解码器
	{
		if(company==0) // mingding
		{
			document.getElementById("top_tab").style.background="url(images/top_bg_dec.jpg)";
		}
		else if(company==1) // bocom
		{
			document.getElementById("top_tab").style.background="url(images/top_bg_dec_bocom.jpg)";
		}
		
		document.getElementById("dec").style.display="block";
		document.getElementById("enc").style.display="none";
	}
	else
	{
		if(company==0) // mingding
		{
			document.getElementById("top_tab").style.background="url(images/top_bg.jpg)";
		}
		else if(company==1) // bocom
		{
			document.getElementById("top_tab").style.background="url(images/top_bg_bocom.jpg)";
		}

		document.getElementById("dec").style.display="block";
		document.getElementById("enc").style.display="block";
	}
	select_param();
	return true;
}
</SCRIPT>

<style type="text/css">
<!--
.STYLE2 {
	font-size: 24px;
	font-family: "Times New Roman", Times, serif;
}
-->
</style>
</head>

<BODY bgColor=#ffffff leftMargin=0 topMargin=0 marginheight="0" marginwidth="0"  onload="MyLoad()">
<input type="hidden" id="get_dev_model" name="get_dev_model" value="<%asp_get_dev_model();%>">
<TABLE id="top_tab" width="1280" height="100" border=0  cellPadding=4 cellSpacing=2 bgcolor="#8e929b" background="images/top_bg.jpg">
<TR>
    <form name="formlogin" action="/goform/form_exit_system">
        <TD valign="bottom" width="1000" height="100%" >
        <font style="font-family:'微软雅黑';font-size:12px;color:#FFFFFF">提示：请使用IE浏览器操作，并打开兼容模式</font>
        </TD>
        <td valign="bottom" style="FONT: 15px;COLOR: #ffffff;">
            当前用户：<%asp_get_user();%>&nbsp;&nbsp;<img src="images/logout.png">
            <a class="a_other" href="#" onClick="return Run_exitsystem();">注销</a>
        </td>
    </form>
</TR>
</TABLE>

<TABLE width="1280" height="50"  border=0 align="left" cellPadding=0 cellSpacing=0   bgcolor="#cad5db">
<TBODY><TR><td>
    <TABLE border=0 cellPadding=0 cellSpacing=0>
    <TBODY><TR>
        <TD width=200 height="100%" align="center" >
		  <h1><span class="STYLE2"><%asp_get_dev_hostname();%></span> </h1>
		</TD>
		<TD width=125 id="dec">
			<img src="images/dec_tool.png"><A id="a_dec" name="a_dec" onClick="select_dec()" class="a_tool_bar" href="main_decoder.asp" target="mainFrame">解码设置</A>
			<img src="images/fengexian.gif">		</TD>
		<TD width=125 id="enc">
			<img src="images/enc_tool.png"><A id="a_enc" name="a_enc" onClick="select_enc()" class="a_tool_bar" href="main_encoder.asp" target="mainFrame">编码设置</A>
			<img src="images/fengexian.gif">
		</TD>
        <TD width=125 id="param">
			<img src="images/sys_tool.png"><A id="a_param" name="a_param" onClick="select_param()" class="a_tool_bar" href="main_system.asp" target="mainFrame">参数配置</A>
			<img src="images/fengexian.gif">
		</TD>
        <TD width=125 id="dec">
			<img src="images/dev_tool.png"><A id="a_dev" name="a_dev" onClick="select_dev()" class="a_tool_bar" href="main_device.asp" target="mainFrame">设备管理</A>
			<img src="images/fengexian.gif">
		</TD>
    </TR></TBODY>
	</TABLE>
</td>
</tr></tbody>
</table>

</body>
</html>