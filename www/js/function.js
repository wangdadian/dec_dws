
/*
 * ˵�����ж�IP�Ƿ���ȷ
 * 
 * created by �����, 2009-12-24
 */
function IsIpOk(ipaddr)
{
	// �жϳ���
	var iplen = ipaddr.length;
	if( iplen<7/*1.1.1.1*/ || iplen>15/*100.100.100.100*/ )
	{
		return false;
	}
	
	// �ж���Ч�ַ�
	var valid_char = "0123456789.";
	for(var i=0; i<iplen; i++)
	{
		var chr = ipaddr.charAt(i);
		if( valid_char.indexOf(chr) == -1 )
		{
			return false;
		}
	}
	
	// �ж�ÿ���ֶεĴ�С
	var field_arr = new Array();
	field_arr = ipaddr.split(".");
	if( field_arr.length != 4 )
	{
		return false;
	}
	
	// ������0.0.0.0
	if( field_arr[0]==0 && field_arr[1]==0 && field_arr[2]==0 && field_arr[3]==0 )
	{
		return false;
	}
	// ��127.0.0.1
	if( field_arr[0]==127 && field_arr[1]==0 && field_arr[2]==0 && field_arr[3]==1 )
	{
		return false;
	}
	// ��255.255.255.255
	if( field_arr[0]==255 && field_arr[1]==255 && field_arr[2]==255 && field_arr[3]==255 )
	{
		return false;
	}
	
	for(var i=0; i<field_arr.length; i++)
	{
		if( field_arr[i] > 255 || field_arr[i]=="")
		{
			return false;
		}
	}
	
	return true;
}

/*
 * ��������Hostname�����Ƿ���ȷ(HOSTNAME)
 */
function IsHostnameOk(name)
{
	// �жϳ���
	var namelen = name.length;
	if( namelen==0 || namelen>16 )
	{
		return false;
	}
	
	// �ж���Ч�ַ�
	var valid_char = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_.-";
	for(var i=0; i<namelen; i++)
	{
		var chr = name.charAt(i);
		if( valid_char.indexOf(chr) == -1 )
		{
			return false;
		}
	}
	
	return true;
}

/*
 * ��������Hostname�����Ƿ���ȷ(HOSTNAME)
 */
function IsMacOk(mac)
{
	//00:16:17:30:A1:88
	var macs = new Array();
	macs = mac.split(":");
	var len = macs.length;
	if(len != 6)
	{
		return false;
	}

	for(var i=0; i<len; i++)
	{	
		var values = new Array();
		values = macs[i].split("");
		var lenv = values.length;
		// DE
		if( lenv != 2 )
		{
			return false;
		}
		for(var j=0; j<lenv; j++)
		{
			if( values[j] >= "0" && values[j]<= "9" ||
			    values[j] >= "A" && values[j]<= "F" ||
				values[j] >= "a" && values[j]<= "f")
			{
				continue;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}





