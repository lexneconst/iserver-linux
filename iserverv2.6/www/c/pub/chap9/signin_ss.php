<?php
	header("content-type: text/javascript; charset=tis-620");

	$login = $_POST['login'];
	$pswd = $_POST['password'];
	if($login=="ajax" && $pswd=="php") {
		$cookie_name = "login";
		$response = "��ҹ�������к�����";
		if(isset($_POST['check_login'])) {
	
			$value = $_POST['login'];
			$expire = time() + 30*24*60*60; //�ӹǹ�Թҷբͧ 30 �ѹ

			if(setcookie($cookie_name, $login, $expire)) {
 				$response .= " ��� Login �١�Ѵ�������ͧ����";
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
