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
function network_form_check()
{
    var ret = 0;
    ret = check_ip(document.network_form.ipaddr);
    if( ret == false )
    {
        alert("IP��ַ����");
        return false;
    }
    
    ret = check_ip(document.network_form.netmask);
    if( ret == false )
    {
        alert("�����������");
        return false;
    }
    
    ret = check_ip(document.network_form.gateway);
    if( ret == false )
    {
        alert("���ش���");
        return false;
    }
    //if( confirm("��������������Ϣ���Ƿ������") )
    {
        document.getElementById('set_network_div').style.display="none";
        document.getElementById('setting_network_tip_div').style.display="block";
        var ip=document.network_form.ipaddr.value;
        //document.network_form.target="_parent";
        var str="<a class=\"a_addr\" href=\"http://" +ip + "/main.asp\" target=\"_top\">" + ip + "</a>";
        document.getElementById("newipaddr").innerHTML = str;
        return true;
    }

    return false;        
}
function fun_sipsvr_submit()
{
    var ret = 0;
    var obj_sipsvr_ip = document.getElementById('sipsvr_ipaddr');
    var obj_sipsvr_id = document.getElementById('sipsvr_id');
    var value_sipip = obj_sipsvr_ip.value;
    var value_sipid = obj_sipsvr_id.value;
    value_sipip = value_sipip.Trim();
    value_sipid = value_sipid.Trim();
    if(value_sipip=="")
    {
        value_sipip = " ";
    }
    else
    {
        ret = check_ip(obj_sipsvr_ip);
        if( ret == false )
        {
            alert("SIP������IP��ַ����");
            return false;
        }
    }
    if(value_sipid=="")
    {
        value_sipid = " ";
    }
    
    var submit_str = value_sipip + ";" + value_sipid + ";";
    document.getElementById('submit_str').value = submit_str;
    // ������ʾ����
    document.getElementById('set_network_div').style.display="none";
    document.getElementById('setting_network_tip_div').style.display="block";
    return true;
}
function dev_reboot()
{
    if(confirm("���������豸���Ƿ������"))
    {
        document.dev_reboot_form.target="_parent";
        return true;
    }
    else
    {
        return false;
    }
}
function OnWebLoad()
{
    // ���SIP����������
    var obj_sipsvr_str = document.getElementById('sipsvr_str');
    var obj_sipsvr_ip = document.getElementById('sipsvr_ipaddr');
    var obj_sipsvr_id = document.getElementById('sipsvr_id');
    
    //"192.168.1.100;300000001234;"
    //ip��ַ;���
    var str = obj_sipsvr_str.value;
    var strs = new Array();
    strs = str.split(";");
    
    obj_sipsvr_ip.value = strs[0];
    obj_sipsvr_id.value = strs[1];
    
    //
}
</script>
</head>
<!--  
/////////////////////////////////////////////////////////////
-->

<body onLoad="OnWebLoad()">
<div id="set_network_div" style="dispaly:block;">
<table width="1080">
  <tr><td>
      <table width="1080">
        <tr>
        <td class="subtitle">��������</td>
        </tr>
        <tr><td><img src="images/break_bg.gif"></td></tr>
      </table>
  </td></tr>
  <tr><td>
      <table width="1080" border="0" cellpadding="6" align="left">
        <tr>
        <form id="network_form" name="network_form" action="/goform/form_network_config" method="POST"> 
          <td class="lable">IP  ��ַ</td>
          <td>
            <input type="text" id="ipaddr" maxlength="15" name="ipaddr" value="<%asp_get_ipaddr();%>" size="20" />
          </td>
        </tr>
        <tr>
          <td class="lable">��������</td>
          <td>
            <input type="text" id="netmask" maxlength="15" name="netmask" value="<%asp_get_netmask();%>" size="20" />
          </td>
        </tr>
        <tr>
          <td class="lable">���ص�ַ</td>
          <td>
            <input type="text" id="gateway" maxlength="15" name="gateway" value="<%asp_get_gateway();%>" size="20" />
          </td>
        </tr>
        <tr>
          <td>
            <input type="submit" name="network_submit" 
            style="border:none;background:url(images/save_btn.png);width:83px;height:20px;cursor:hand;"  
            onClick="return network_form_check();" value="" />
          </td>
          </form>
          <form name="dev_reboot_form" action="/goform/form_dev_reboot" method=POST>
          <td >
            <!--
            <input type="submit" name="dev_reboot_submit" 
            style="border:none;background:url(images/reboot_btn.png);width:83;height:20;cursor:hand;" 
            onclick="return dev_reboot();" value=""/>
            -->
          </td>
          </form>
        </tr>
      </table>
  </td></tr>
</table>
<br>
<span style="color:#FF0000;font-weight:bold;"><%asp_get_network_ret();%></span>

<form id="sipsvr_form" name="sipsvr_form" action="/goform/form_sipsvr" method="POST">
<input type="hidden" id="submit_str" name="submit_str" value="">
<input type="hidden" id="sipsvr_str" name="sipsvr_str" value="<%asp_get_sipsvr();%>">

<table width="1080">
  <tr><td>
      <table width="1080">
        <tr>
        <td class="subtitle">SIP����������</td>
        </tr>
        <tr><td><img src="images/break_bg.gif"></td></tr>
      </table>
  </td></tr>
  </table>
<table width="1080" border="0" cellpadding="6" align="left">
<tr>

  <td class="lable">IP��ַ</td>
  <td>
    <input type="text" id="sipsvr_ipaddr" maxlength="15" name="sipsvr_ipaddr" value="" size="30" />
  </td>
</tr>
<tr>
  <td class="lable">���</td>
  <td>
    <input type="text" id="sipsvr_id" name="sipsvr_id" value="" size="30" />
  </td>
</tr>
<tr>
  <td colspan="2">
    <input type="submit" name="sipsvr_submit" 
    style="border:none;background:url(images/save_btn.png);width:83px;height:20px;cursor:hand;"  
    onClick="return fun_sipsvr_submit();" value="" />
  </td>

</tr>
</table>
</form>
</div>

<div id="setting_network_tip_div" style="display:none;">
<table>
    <tr>
        <td width="512" height="200" bgcolor="#FEF9E9" align="center">
            <img src="images/loading_01.gif">
            <br><br>
            ��ʹ�����µ�IP��ַ<span id="newipaddr"></span>��½������ҳ��
        </td>
    </tr>
</table>
</div>

</body>
</html>