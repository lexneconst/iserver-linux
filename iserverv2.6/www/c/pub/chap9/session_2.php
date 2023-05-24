<?php
	session_start();
?>
<html>
<body>
<?php
	if(isset($_SESSION['login'])) {
		echo "ท่านเข้าสู่ระบบแล้ว";
	}
	else {
		echo "ท่านยังไม่ได้เข้าสู่ระบบ";
	}
?>
<p>
<a href="session.php">Back</a>

</body>
</html>
