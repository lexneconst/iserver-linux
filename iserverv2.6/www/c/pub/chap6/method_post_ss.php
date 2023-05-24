<?php

	$login = $_POST['login'];
	$password = $_POST['password'];
	$msg = "";

	if($login != "jobgle") {
		$msg = "Login incorrect!";
	}
	else if($password != "123") {
		$msg = "Password incorrect!";
	}
	else {
		$msg = "Login และ Password ถูกต้อง!";
	}

	echo $msg;

?>
