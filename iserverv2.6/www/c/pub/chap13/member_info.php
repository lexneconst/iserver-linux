<?php
	
	session_start();

	$id = "";
	$login = "";
	$password = "";
	$email = "";
	$name = "";

	if(isset($_SESSION['uid'])) {
		$dblink = mysql_connect("localhost", "root", "123");
		mysql_query("USE ajax;");
		$id = $_SESSION['uid'];
		$sql = "SELECT * FROM member WHERE id = $id;";
		$result = mysql_query($sql);
		$member = mysql_fetch_array($result);
		$login = $member['login'];
		$password = $member['password'];
		$email = $member['email'];
		$name = $member['name'];
		mysql_close($dblink);
	}
?>	
<html>
<head>
<script src="/ajaxbook/ajax_framework.js"> </script>
<script>
function ajaxSubmit() {
	var data = getFormData("frm");
	
	var URL = "member_info_ss.php";
	
	ajaxLoad('post', URL, data, 'msg');
}
</script>
</head>
<body style="text-align:center;">
<h3>ข้อมูลสมาชิก</h3>
<form name="frm">
<input type="hidden" name="id" value="<?php echo $id; ?>">
<div id="msg" style="color:red;"></div>

<table bgcolor="#eeeeff">
<tr><td>Login:</td><td><input type="text" name="login" value="<?php echo $login; ?>"></td></tr>
<tr><td>Pswd:</td><td><input type="password" name="pswd" value="<?php echo $password; ?>"></td></tr>
<tr><td>Email:</td><td><input type="text" name="email" value="<?php echo $email; ?>"></td></tr>
<tr><td>ชื่อ:</td><td><input type="text" name="name" value="<?php echo $name; ?>"></td></tr>
<tr><td>&nbsp;</td><td><p><button onclick="ajaxSubmit()">ส่งข้อมูล</button></td></tr>
</table>
</form>
<p>
<a href="index.php">หน้าแรก</a>
</body>
</html>
