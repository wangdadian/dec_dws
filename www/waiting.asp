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
        <title>处理中</title>
        <style type="text/css">
        
        .style1 {color: #cedfe9;FONT: 18px;font-weight:bold;}
        
        </style>
        <script>
        <!--
        var counter=11;
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
		<table>
			<tr>
				<td width="511" height="200" bgcolor="#FEF9E9" align="center">
						<img src="images/loading_01.gif"><br><br>
						服务处理中，剩余&nbsp;<span id="timeLeft"></span>&nbsp;秒<br>
				</td>
			</tr>
		</table>
    </body>
</html>
