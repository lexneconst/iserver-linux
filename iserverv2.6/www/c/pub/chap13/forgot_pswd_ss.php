<?php
	session_start();

	$email = $_POST['email'];

	$dblink = mysql_connect("localhost", "root", "123");
	mysql_query("USE ajax;");
	
$sql = <<<SQL
	SELECT password FROM member 
	WHERE email = '$email';
SQL;
	$qry = mysql_query($sql);

	$response = "";
	if(mysql_num_rows($qry)==0) {
		$response = "��辺 Email ����ҹ�к�";
	}
	else {
		$pswd = mysql_result($qry, 0, "password");
		$to = $email;
		$subject = "Reply for Password";
		$message = "���ʼ�ҹ�ͧ��ҹ���: $pswd";
		$header = "From:noreply@example.com\r\n";

		if(mail($to, $subject, $message, $header)) {
			$response = "���ʼ�ҹ�ͧ��ҹ�١������Ƿ��: $email";
		}
		else {
			$response = "����������Դ��ͼԴ��Ҵ!";
		}
	}
	mysql_close($dblink);
	
	header("content-type:text/javascript; charset=tis-620");
	echo "alert('$response')";
?>
	