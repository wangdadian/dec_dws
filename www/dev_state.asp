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
// 自动刷新
function update_state(){
window.location.reload();
}
setTimeout('update_state()',10000); //10秒自动刷新一次

</SCRIPT>

</head>

<BODY bgColor=#ffffff leftMargin=0 topMargin=0 marginheight="0" marginwidth="0">
<form action="/goform/form_dev_state" method=POST>
    <table width="1080">
      <tr><td>
        <table align="left" width="1080">
          <tr><td class="subtitle">设备运行状态</td></tr>
		<tr>
        <td><img src="images/break_bg.gif"></td>
      </tr>
        </table>
      </td></tr>
      <!--运行时间-->
      <tr><td>
        <table border="0" cellpadding="6" align="left">
        <tr>
          <td class="lable">设备运行时间</td>
          <td>
            <span><%asp_get_dev_uptime();%></span>&nbsp;秒
          </td>
        </tr>
      </td></tr>
      
      <!--手动刷新-->
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