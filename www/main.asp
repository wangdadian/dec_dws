<% asp_web_check_user(); %>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="style/doc.css" type="text/css">
<title>设备管理</title>
<script type="text/javascript">
function refreshTopmain()
{
	//alert("testsetsetst");
	window.parent.frames["topFrame"].location.reload(); 
}
</script> 
</head>

<frameset  rows="150,*,30" cols="1280" framespacing="0" frameborder="no" border="0">
  <frame src="top.asp" name="topFrame" scrolling="No" noresize="noresize" id="topFrame" title="topFrame" />
  <frame src="main_system.asp" name="mainFrame" id="mainFrame" title="mainFrame" scrolling="auto" noresize="noresize" />
  <frame src="bottom.asp" name="buttomFrame" id="buttomFrame" title="buttomFrame" scrolling="no" noresize="noresize" />
</frameset>
<noframes>
<body>
</body>
</noframes></html>

