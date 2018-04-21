// Trim(), Ltrim(), RTrim()º¯Êý 
String.prototype.Trim = function()
{
	return this.replace(/(^\s*)|(\s*$)/g, "");
}

String.prototype.LTrim = function()
{
	return this.replace(/(^\s*)/g, "");
}

String.prototype.RTrim = function()
{
	return	 this.replace(/(\s*$)/g, "");
}

function getArgs() {  
	var args = {}; 
	var query = location.search.substring(1); 
	// Get query string 
	var pairs = query.split("&");  
	// Break at ampersand 
	for(var i = 0; i < pairs.length; i++) 
	{ 
		var pos = pairs[i].indexOf('='); 
		// Look for "name=value" 
		if (pos == -1) continue; 
		// If not found, skip 
		var argname = pairs[i].substring(0,pos);// Extract the name 
		var value = pairs[i].substring(pos+1);// Extract the value 
		value = decodeURIComponent(value);// Decode it, if needed 
		args[argname] = value;// Store as a property 
	} 
	return args;// Return the object  
 }
