<?php
	session_start();	
?>
<html>
<head>
<script src="/ajaxbook/ajax_framework.js"> </script>
<script>
function ajaxSubmit() {
	if(!confirm('ยกเลิกการเป็นสมาชิก?')) {
		return;
	}
	var data = "x=1";
	
	var URL = "member_delete_ss.php";
	
	ajaxLoad('post', URL, data, 'msg');
}
</script>
</head>
<body style="text-align:center;">
<h2>ยกเลิกการเป็นสมาชิก?..</h2>

<?php
	if(isset($_SESSION['login'])) {
?>
<form name="frm">
<button onclick="ajaxSubmit()">ยกเลิกการเป็นสมาชิก</button>
</form>
<?php
	}
	else {
		echo "ท่านต้อง Login เข้าสู่ระบบก่อนจึงจะใช้บริการนี้ได้";
	}
?>
<p>
<a href="index.php">หน้าแรก</a>
</body>
</html>