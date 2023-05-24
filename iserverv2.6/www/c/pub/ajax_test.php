<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=windows-874" />
<title>Untitled Document</title>
<script src="http://www.kawnabroker.com/a/script/ajax_framework.js" type="text/javascript"></script>
<script>
function ajaxCall(){
	var name = document.getElementById('aName').value;
	var data = "name=" + name;
	var URL = "http://www.prakunpai.com/main/ajax_test_return.php";		
	ajaxLoad("post", URL, data, "content");	
}
</script>
</head>

<body>
<form id="form1" name="form1" method="post" action="">
  ใส่ชื่อของคุณ
  <br />
  <input type="text" name="aName" id="aName" />
  <img src="images/submit-button-hover.jpg" width="50" height="21" style="cursor:pointer" onclick="ajaxCall()" />
</form>
<div id="content"></div>
</body>
</html>