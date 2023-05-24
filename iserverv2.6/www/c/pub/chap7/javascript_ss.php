<?php

	$login = $_POST['login'];
	$password = $_POST['password'];

	if($login!="ajax" || $password!="123") {
 		header("content-type: text/plain; charset=tis-620");
		echo "Login หรือ Password ไม่ถูกต้อง!";
	}
	else {

 		header("content-type: text/javascript; charset=tis-620");

		//ส่งผลลัพธ์กลับในแบบ HEREDOC
echo <<<JS

	var f = document.getElementById('frm');
	f.style.display = 'none';
	
	var el = document.getElementById('displayDiv');
	el.style.color = 'red';
	el.innerHTML = 'ท่านเข้าสู่ระบบแล้ว';

JS;
		
	} 	// สิ้นสุดบล็อก else

?>
