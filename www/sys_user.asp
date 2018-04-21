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
var names=new Array();
var flags=new Array();
function onclick_user_edit()
{
	var obj_userlist = document.getElementById('user_list');
	var obj_userpass1 = document.getElementById('user_newpass1');
	var obj_userpass2 = document.getElementById('user_newpass2');
	
	var index_userlist = obj_userlist.selectedIndex;
	if( index_userlist == 0)
	{
		alert("��ѡ���û���");
		return false;
	}
	var value_userlist = obj_userlist.options[index_userlist].value;
	var value_pass1  = obj_userpass1.value;
	var value_pass2  = obj_userpass2.value;
	if(value_pass1 != value_pass2 || value_pass1.Trim()=="" || value_pass2.Trim=="")
	{
		alert("���������������������룡");
		obj_userpass2.value = "";
		obj_userpass1.focus();
		obj_userpass1.select();
		return false;
	}
	//alert(value_userlist+"&&"+value_pass1+"&&"+flags[index_userlist-1]);
	document.getElementById('username').value = value_userlist;
	document.getElementById('userpass').value = value_pass1;
	document.getElementById('usertype').value = flags[index_userlist-1];
	//if( confirm("��������ϵͳ��Ϣ���Ƿ������") )
	{
		document.getElementById('set_user_div').style.display="none";
		document.getElementById('setting_user_tip_div').style.display="block";
		//document.form_useredit.submit();
		return true;
	}
	return false;
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
function OnSelectUser()
{
	var obj_userlist = document.getElementById('user_list');
	var obj_usertype = document.getElementById('user_type');
	
	var index_userlist = obj_userlist.selectedIndex;
	var flag = flags[index_userlist-1];
	var type = "";
	switch(parseInt(flag))
	{
	case 0:
		type="����Ա";
		break;
	case 1:
		type="����Ա";
		break;
	case 2:
		type="��ͨ�û�";
		break;
	default:
		type="";
		break;
	};
	obj_usertype.value = type;
}
function myload()
{
	var users_str=document.getElementById('userinfos').value;
	var users = new Array();
	users = users_str.split(";");
	for(var i=0; i<users.length; i++)
	{
		var info = new Array();
		info = users[i].split(":");
		names[i] = info[0];
		flags[i] = info[1];
	}
	
	var str="";
	str =  "<select id=\"user_list\" name=\"user_list\" style=\"width: 126px;\" onChange=\"OnSelectUser()\">";
	str += "<option value=\"\"></option>";
	for(var i=0; i<users.length; i++)
	{
		str += "<option value=\""+ names[i] + "\">"+ names[i] +"</option>";
	}
	str += "</select>"
	document.getElementById('td_userlist').innerHTML=str;
}
</SCRIPT>

</head>

<BODY bgColor=#ffffff leftMargin=0 topMargin=0 marginheight="0" marginwidth="0" onLoad="myload()">
<div id="set_user_div" style="dispaly:block;">
<table align="left" width="1080">
  <tr>
	<td class="subtitle">�û�����</td>
  </tr>
  <tr>
	<td><img src="images/break_bg.gif"></td>
  </tr>
</table>
  <p>&nbsp;</p>
  <p>&nbsp;</p>
  <p>&nbsp;</p>
  <p>&nbsp;</p>
  <table width="1080" border="0" cellpadding="6" align="left">
  <form action="/goform/form_user_edit" method=POST>
    <input type="hidden" id="" name="userinfos" value="<%asp_get_user_list();%>">
    <!---->
    <input type="hidden" id="username" name="username" value="0">
    <input type="hidden" id="userpass" name="userpass" value="0">
    <input type="hidden" id="usertype" name="usertype" value="0">
	<tr>
	  <td class="subsubtitle">�޸�����</td>
	  <td></td>
    </tr>
	<tr>
	  <td class="lable">ѡ���û�</td>
      <td id="td_userlist" name="td_userlist">

      </td>
    </tr>
    <tr>	
      <td class="lable">�û�����</td>
      <td>
        <input type="text" id="user_type"  name="user_type" disabled="disabled" readonly value="" size="16" />
      </td>
    </tr>
    <tr>
      <td class="lable">�µ�����</td>
      <td>
        <input type="password" id="user_newpass1" name="user_newpass1"  value="" size="16" />
      </td>
    </tr>
    <tr>
      <td class="lable">ȷ������</td>
      <td>
        <input type="password" id="user_newpass2" name="user_newpass2" value="" size="16" />
      </td>
    </tr>
    <tr>
      <td colspan="2">
        <input type="submit" name="user_edit_submit" 
		style="border:none;background:url(images/save_btn.png);width:83px;height:20px;cursor:hand;" 
		onclick="return onclick_user_edit();" value=""/>
      </td>
	  </form>
    </tr>

</table>

</div>

<div id="setting_user_tip_div" style="display:none;">
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