<?php
	session_start();
	
	$id = $_POST['id'];
	$login = $_POST['login'];
	$pswd = $_POST['pswd'];
	$email = $_POST['email'];
	$name = enc($_POST['name']);
	
	$pat_account = "^[a-zA-Z0-9]{5,15}$";
	$pat_email = "^[_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.([a-z]){2,4})$";
	$err_msg = "";
	if(!eregi($pat_account, $login)) {
		$err_msg = "Login ต้องประกอบด้วย a-z หรือ 0-9 จำนวน 5-15 ตัว";
	}
	else if(!eregi($pat_account, $pswd)) {
		$err_msg = "Password ต้องประกอบด้วย a-z หรือ 0-9 จำนวน 5-15 ตัว";
	}
	else if(!eregi($pat_email, $email)) {
		$err_msg = "Email ไม่ถูกต้องตามรูปแบบ";
	}
	else if(strlen($name)<1) {
		$err_msg = "ท่านยังไม่ได้ใส่ชื่อ";
	}

	if($err_msg!="") {
		header("content-type:text/plain; charset=tis-620");
		echo $err_msg;
		exit();
	}

	$id = "";
	if(isset($_SESSION['uid'])) {
		$id = $_SESSION['uid'];
	}

	$dblink = mysql_connect("localhost", "root", "123");
	mysql_query("USE ajax;");
	
$sql = <<<SQL

	REPLACE INTO member VALUES
	('$id','$login','$pswd','$email','$name');
SQL;

	$qry = mysql_query($sql);
	$response = "";
	if(mysql_affected_rows($dblink)==0) {
		$response = "alert('การบันทึกข้อมูล เกิดผิดพลาด!!!');";
	}
	else {
		$response = "alert('การบันทึกข้อมูล เสร็จเรียบร้อย');";
		$response .= "location='index.php';";
	}
	mysql_close($dblink);

	if(isset($_COOKIE['login'])) {
		$expire = time() + 30*24*60*60;
		setcookie('login', $login, $expire);
	}
	header("content-type:text/javascript; charset=tis-620");
	echo $response;
?>

<?php function enc($input){return iconv("utf-8","tis-620",$input);} ?>