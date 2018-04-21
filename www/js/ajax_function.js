
var g_xmlhttp;

function loadDoc(url,sub_fuc)
{
	g_xmlhttp=null;
	if (window.XMLHttpRequest)
	{// for Firefox, Opera, IE7, etc.
		g_xmlhttp=new XMLHttpRequest();
	}
	else if (window.ActiveXObject)
	{// for IE6, IE5
		g_xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	if (g_xmlhttp!=null)
	{
		g_xmlhttp.onreadystatechange=sub_fuc;
		g_xmlhttp.open("GET",url,true);
		g_xmlhttp.send(null);
	}
	else
	{
		//alert("Your browser does not support XMLHTTP.");
	}
}

function uptime_ajax()
{
	if (g_xmlhttp.readyState==4)
  	{// 4 = "loaded"
		if (g_xmlhttp.status==200)
		{// 200 = "OK"
			document.getElementById('uptime').innerHTML=g_xmlhttp.responseText;
		}
	}
}




