<?php
	session_start();

	if(!isset($_POST['x'])) {
		exit();
	}

	header("Content-Type:text/javascript; charset=tis-620");

	if(isset($_SESSION['uid'])) {
		unset($_SESSION['uid']);	
	}
	if(isset($_SESSION['login'])) {
		unset($_SESSION['login']);	
	}
	if(isset($_SESSION['name'])) {
		unset($_SESSION['name']);	
	}
	
	echo "location = 'index.php';";
?>