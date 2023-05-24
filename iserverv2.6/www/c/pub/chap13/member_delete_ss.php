<?php
	session_start();

	if(!isset($_SESSION['uid'])||!isset($_POST['x'])) {
		exit();
	}
	$id = $_SESSION['uid'];		

	$dblink = mysql_connect("localhost", "root", "123");
	mysql_query("USE ajax;");
	
$sql = <<<SQL
	DELETE FROM member 
	WHERE id = $id;
SQL;
	$result = mysql_query($sql);
	$response = "";
	if(mysql_affected_rows($dblink)==0) {
		$response = "alert('เกิดข้อผิดพลาด ไม่สามารถลบข้อมูลได้')";
	}
	else {
		unset($_SESSION['uid']);
		unset($_SESSION['login']);
		unset($_SESSION['name']);

		setcookie('login', '', 0);

		$response = "alert('ข้อมูลของท่านถูกลบแล้ว');";
		$response .= "location = 'index.php';";
	}
	mysql_close($dblink);
	
	header("content-type:text/javascript; charset=tis-620");
	echo $response;
?>
	