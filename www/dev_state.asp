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
// �Զ�ˢ��
function update_state(){
window.location.reload();
}
setTimeout('update_state()',10000); //10���Զ�ˢ��һ��

</SCRIPT>

</head>

<BODY bgColor=#ffffff leftMargin=0 topMargin=0 marginheight="0" marginwidth="0">
<form action="/goform/form_dev_state" method=POST>
    <table width="1080">
      <tr><td>
        <table align="left" width="1080">
          <tr><td class="subtitle">�豸����״̬</td></tr>
		<tr>
        <td><img src="images/break_bg.gif"></td>
      </tr>
        </table>
      </td></tr>
      <!--����ʱ��-->
      <tr><td>
        <table border="0" cellpadding="6" align="left">
        <tr>
          <td class="lable">�豸����ʱ��</td>
          <td>
            <span><%asp_get_dev_uptime();%></span>&nbsp;��
          </td>
        </tr>
      </td></tr>
      
      <!--�ֶ�ˢ��-->
      <tr><td>
        <table>
        <tr><td>
            <input type="submit" name="dev_state_submit" 
			style="border:none;background:url(images/refresh_btn.png);width:83;height:20;cursor:hand;"
			value=""/>
        </td></tr>
        </table>
      </td></tr>
    </table>
</form>
</body>
</html>