<?php

	$login = $_POST['login'];
	$pswd = $_POST['pswd'];

	if($login!="ajax" || $pswd!="php") {
		header("content-type: text/plain; charset=tis-620");
		echo "<font color=red>Login หรือ Password ไม่ถูกต้อง</font>";
		exit();
	}

$js = <<<JS
	var f = document.forms['frm'];
	f.style.display = 'none';
	var el = document.getElementById('msg');
	el.innerHTML = 'ท่านเข้าสู่ระบบแล้ว';
JS;
	header("content-type: text/javascript; charset=tis-620");
	echo $js;
?>
		
