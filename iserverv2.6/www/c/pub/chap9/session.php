<?php
	session_start();
?>
<html>
<head>
<script src="/ajaxbook/ajax_framework.js"> </script>
<script>

function signin_signout() {
	var URL = "";
	var data = ""; 
	if(document.getElementById('bt').innerHTML=="เข้าสู่ระบบ") {
		var URL = "signin.php";
		URL += "?dummy=" + (new Date()).getTime();

		data = getFormData("frm");
	}
	else {
		URL = "signout.php";
		URL += "?dummy=" + (new Date()).getTime();
	}

	ajaxLoad('post', URL, data, 'displayDiv');
}
function hideForm() {
	document.getElementById('frm').reset();
	document.getElementById('frm').style.display = 'none';
	
	document.getElementById('displayDiv').innerHTML = "ท่านเข้าสู่ระบบแล้ว";
	document.getElementById('bt').innerHTML = "ออกจากระบบ";
}

function showForm() {
	document.getElementById('frm').style.display = 'block';
	
	document.getElementById('displayDiv').innerHTML = "กรุณา Login เข้าสู่ระบบ";
	document.getElementById('bt').innerHTML = "เข้าสู่ระบบ";
}
</script>
</head>
<body>
<h3>Ajax Session</h3>

<div id="displayDiv"> </div>
<p>

<form id="frm">
Login:<input id="login" type="text"><br>
Pswd:<input id="pswd" type="password"><p>
</form>

<button id="bt" onclick="signin_signout()"></button>
<p>
<a href="session_2.php">Test</a>

<?php
	if(isset($_SESSION['login'])) {
		echo "<script> hideForm(); </script>";
	}
	else {
		echo "<script> showForm(); </script>";
	}
?>

</body>
</html>