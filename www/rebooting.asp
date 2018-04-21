<html>
	<head>
		<meta http-equiv="pragma" content="no-cache" />
		<meta http-equiv="cache-control" content="no-cache" />
		<meta http-equiv="expires" content="0" />    
		<meta http-equiv="keywords" content="keyword1,keyword2,keyword3" />
		<meta http-equiv="description" content="This is my page" />
		<meta http-equiv="content-type" content="text/html; charset=gb2312" />
		<link rel="stylesheet" href="style/doc.css" type="text/css">
		<link href="./sheet.css" type=text/css rel=stylesheet>
		<title>设备重启</title>
		<style type="text/css">
		
		.style1 {color: #cedfe9}
		
		</style>
		<script>
		<!--
		var counter=40;
		function time_load()
		{
			ID = window.setTimeout("Update();", 1000);
		}
		function Update()
		{
			counter--;
			if(counter < 0) counter = 0;
			document.getElementById("timeLeft").innerHTML = counter;
			if(counter <= 0)
			{
				top.window.location.replace("/");
			}
			ID = window.setTimeout("Update();", 1000);
		}
		//-->
		</script>

	</head>

	<body onLoad="time_load();">
		<table  border="0" align="center" cellpadding="0" cellspacing="0">
		  <tr>
			<td valign="top">
			  <table cellspacing="0" cellpadding="0" width="535" bgcolor="#888888" border="0">
				<tbody>
				  <tr>
					<td width="535"><table cellspacing="0" cellpadding="0" width="100%" border="0">
						<tbody>
						  <tr>
							<td class="title-top" width="536" height="51">
							<p align="center"><span class="style1"> 设备重启 </span></p>
							</td>
						  </tr>
						  <tr>
							<td bgcolor="#ffffff" height="30"></td>
						  </tr>
						  <tr>
							<td valign="top" width="536" bgcolor="white"><table border="0" cellspacing="0" width="513" style="border-style:none;" align="center">
							  <tr>
								<td width="511" height="2" colspan="2" bgcolor="#EED08F"><p><spacer type="block" height="2" /></p></td>
							  </tr>
							  <tr>
								<td width="511" height="250" bgcolor="#FEF9E9" align="center">
										<img src="images/rebooting.gif"><br><br>
										正在重启中，剩余&nbsp;<span id="timeLeft"></span>&nbsp;秒，请耐心等待......<br><br>
										设备管理网页链接地址<a class="a_addr" href="http://<%asp_get_ipaddr();%>"><%asp_get_ipaddr();%></a>
								</td>
							  </tr>
							  <tr>
								<td width="511" height="2" colspan="2" bgcolor="#EED08F"><p><spacer type="block" height="2" /></p></td>
							  </tr>
							</table>
							<p>&nbsp;</p></td>
						  </tr>
						</tbody>
					</table></td>
				  </tr>
				</tbody>
			  </table>
			  <div align="center"><br />
			</div>    </td>
		  </tr>
		</table>
	</body>
</html>
