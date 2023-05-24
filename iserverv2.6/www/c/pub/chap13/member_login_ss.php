<?php
	session_start();

	$login = $_POST['login'];
	$pswd = $_POST['pswd'];

	$dblink = mysql_connect("localhost", "root", "123");
	mysql_query("USE ajax;");
	
$sql = <<<SQL
	SELECT * FROM member 
	WHERE login = '$login' AND password = '$pswd';
SQL;
	$result = mysql_query($sql);

	$response = "";
	if(mysql_num_rows($result)==0) {
		$response = "alert('Login หรือ Password ไม่ถูกต้อง')";
	}
	else {
		$member = mysql_fetch_array($result);
		$_SESSION['uid'] = $member['id'];
		$_SESSION['login'] = $member['login'];
		$_SESSION['name'] = $member['name'];

		$cookie_name = "login";
		if(isset($_POST['store_login'])) {
	
			$value = $member['login'];
			$expire = time() + 30*24*60*60; //จำนวนวินาทีของ 30 วัน
			setcookie($cookie_name, $value, $expire);
		}
		else {
			setcookie($cookie_name, '', 0);
		}

		$response = "hideForm();";
	}

	mysql_close($dblink);

	header("content-type:text/javascript; charset=tis-620");
	echo $response;
?>
	