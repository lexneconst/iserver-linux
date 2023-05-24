<?php
	session_start();
?>
<html>
<head>
<script src="/ajaxbook/ajax_framework.js"> </script>
<script>
function ajaxSubmit() {
	var action = document.getElementById('bt').value;
	var data = "";
	var URL = "";
	if(action=="เข้าสู่ระบบ") {
		data = getFormData("frm");
		URL = "member_login_ss.php";
	}
	else {
		data = "x=1";
		URL = "member_logout_ss.php";
	}
	
	ajaxLoad('post', URL, data, 'msg');
}
function hideForm() {
	document.getElementById('frm').reset();
	document.getElementById('frm').style.display = 'none';
	
	document.getElementById('msg').innerHTML = "ท่านเข้าสู่ระบบแล้ว";
	document.getElementById('bt').innerHTML = "ออกจากระบบ";
}

function showForm() {
	document.getElementById('frm').style.display = 'block';
	document.getElementById('bt').innerHTML = "เข้าสู่ระบบ";
}

function getStoredLogin() {
	var URL = "getcookie_ss.php";
	
	var data = null;
	
	ajaxLoad('post', URL, data, '');
}
</script>
</head>
<body style="text-align:center;">

<div id="msg" style="color:red"></div>

<div style="width:300px;background-color:#eeeeff;padding:10px;">
<form id="frm" name="frm">
ยังไม่ได้เป็นสมาชิก? <a href="member_info.php">สมัครได้ที่นี่</a><p>
<table>
<tr><td>Login:</td><td><input type="text" name="login"></td></tr>
<tr><td>Pswd:</td><td><input type="password" name="pswd"></td></tr>
<tr><td>&nbsp;</td><td><a href="forgot_pswd.html">ลืมรหัสผ่าน</a></td></tr>
<tr><td>&nbsp;</td><td><input type="checkbox" id="store_login">เก็บ Login ไว้ที่เครื่องนี้</td></tr>
</table>
</form>
<button id="bt" onClick="ajaxSubmit()">เข้าสู่ระบบ</button>
</div>
<?php
	if(isset($_SESSION['login'])) {
		echo "<script> hideForm(); </script>";
	}
	else {
		echo "<script> showForm(); </script>";
	}
?>
<a href="member_info.php">แก้ไขข้อมูล</a> -
<a href="member_delete.php">ยกเลิกการเป็นสมาชิก</a>

</body>
</html>

<script>
	getStoredLogin();
</script>