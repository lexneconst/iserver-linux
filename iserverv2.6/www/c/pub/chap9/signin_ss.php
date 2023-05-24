<?php
	header("content-type: text/javascript; charset=tis-620");

	$login = $_POST['login'];
	$pswd = $_POST['password'];
	if($login=="ajax" && $pswd=="php") {
		$cookie_name = "login";
		$response = "ท่านเข้าสู่ระบบแล้ว";
		if(isset($_POST['check_login'])) {
	
			$value = $_POST['login'];
			$expire = time() + 30*24*60*60; //จำนวนวินาทีของ 30 วัน

			if(setcookie($cookie_name, $login, $expire)) {
 				$response .= " และ Login ถูกจัดเก็บในเครื่องแล้ว";
			}

		}
		else {
			setcookie($cookie_name, '', 0);
		}

		echo "alert('$response');";
	}
	else {
		echo "alert('Login Failed!');";
	}
?>
