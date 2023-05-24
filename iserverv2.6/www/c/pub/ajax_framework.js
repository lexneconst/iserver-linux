
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
	if(method=="get") {
		URL += "&" + data;
		data = null;
	}

	ajax.open(method, URL);

	if(method=="post") {
		ajax.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
	}
	
	ajax.onreadystatechange = function() {
		if(ajax.readyState==4 && ajax.status==200) {
			var ctype = ajax.getResponseHeader("Content-Type").toLowerCase();
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

function getFormData(form_name_or_id) {
	
	var frm = document.forms[form_name_or_id];
	if(frm==null) {
		alert("form not found!");
		return;
	}

	var data = "";
	var num_el = frm.elements.length;
	for(i=0; i<num_el; i++) {
		var el = frm.elements[i];
		if(el.name=="" && el.id=="") {
			continue;
		}
		var param_name = "";
		if(el.name!="") {
			param_name = el.name;
		}
		else if(el.id!="") {
			param_name = el.id;
		}

		var t = frm.elements[i].type;
		var value = "";
		if(t=="text"||t=="password"||t=="hidden"||t=="textarea") {
			value = encodeURI(el.value);
		}
		else if(t=="radio"||t=="checkbox") {
			if(el.checked) {
				value = encodeURI(el.value);
			}
			else {
				continue;
			}
		}
		else if(t=="select-one") {
			value = encodeURI(el.options[el.selectedIndex].value);
		}
		else if(t=="select-multiple") {
			for(j=0; j<el.length; j++) {
				if(el.options[j].selected) {
					if(data!="") {
						data += "&";
					}
					data += param_name + "=";
					data += encodeURI(select.options[j].value);
				}
			}
			
			continue;
		}
		if(data!="") {
			data += "&";
		}
		data += param_name + "=" + value;
	}

	return data;
}