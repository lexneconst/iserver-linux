<?php
	session_start();

	header("content-type:text/javascript; charset=tis-620");

	$login = $_POST['login'];
	$pswd = $_POST['pswd'];

	if($login=="ajax" && $pswd=="php") {
		$_SESSION['login'] = $login;
		echo "hideForm()";
	}
	else {
		echo "alert('Login หรือ Password ไม่ถูกต้อง')";
	}

?>
	