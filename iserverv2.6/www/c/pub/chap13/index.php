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
	if(action=="�������к�") {
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
	
	document.getElementById('msg').innerHTML = "��ҹ�������к�����";
	document.getElementById('bt').innerHTML = "�͡�ҡ�к�";
}

function showForm() {
	document.getElementById('frm').style.display = 'block';
	document.getElementById('bt').innerHTML = "�������к�";
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
�ѧ���������Ҫԡ? <a href="member_info.php">��Ѥ�������</a><p>
<table>
<tr><td>Login:</td><td><input type="text" name="login"></td></tr>
<tr><td>Pswd:</td><td><input type="password" name="pswd"></td></tr>
<tr><td>&nbsp;</td><td><a href="forgot_pswd.html">������ʼ�ҹ</a></td></tr>
<tr><td>&nbsp;</td><td><input type="checkbox" id="store_login">�� Login ���������ͧ���</td></tr>
</table>
</form>
<button id="bt" onClick="ajaxSubmit()">�������к�</button>
</div>
<?php
	if(isset($_SESSION['login'])) {
		echo "<script> hideForm(); </script>";
	}
	else {
		echo "<script> showForm(); </script>";
	}
?>
<a href="member_info.php">��䢢�����</a> -
<a href="member_delete.php">¡��ԡ�������Ҫԡ</a>

</body>
</html>

<script>
	getStoredLogin();
</script>