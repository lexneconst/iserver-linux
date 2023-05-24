
function ajaxLoad(method, URL, data, displayId) {
	var ajax = null;
	if(window.ActiveXObject) {		
		ajax = new ActiveXObject("Microsoft.XMLHTTP");	
	}
	else if(window.XMLHttpRequest) {		
		ajax = new XMLHttpRequest();	
	}
	else {
		alert("Your browser doesn't support Ajax");
		return;
	}

	method = method.toLowerCase();
	URL += "?dummy=" + (new Date()).getTime();
	if(method.toLowerCase()=="get") {
		URL += "&" + data;
		data = null;
	}

	ajax.open(method, URL);

	if(method.toLowerCase()=="post") {
		ajax.setRequestHeader(
 			"Content-Type","application/x-www-form-urlencoded");
	}
	
	ajax.onreadystatechange = function() {
		if(ajax.readyState==4 && ajax.status==200) {

			var ctype = ajax.getResponseHeader("Content-Type");
 			ctype = ctype.toLowerCase();

			ajaxCallback(ctype, displayId, ajax.responseText);

			delete ajax;
 			ajax = null;
		}
	}

	ajax.send(data);
}

function ajaxCallback(contentType, displayId, responseText) {
	if(contentType.match("text/javascript")) {
		eval(responseText);
	}
	else {
		var el = document.getElementById(displayId);
		el.innerHTML = responseText;
	}
}