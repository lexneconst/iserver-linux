<?php

	$login = $_POST['login'];
	$password = $_POST['password'];

	if($login!="ajax" || $password!="123") {
 		header("content-type: text/plain; charset=tis-620");
		echo "Login ���� Password ���١��ͧ!";
	}
	else {

 		header("content-type: text/javascript; charset=tis-620");

		//�觼��Ѿ���Ѻ�Ẻ HEREDOC
echo <<<JS

	var f = document.getElementById('frm');
	f.style.display = 'none';
	
	var el = document.getElementById('displayDiv');
	el.style.color = 'red';
	el.innerHTML = '��ҹ�������к�����';

JS;
		
	} 	// ����ش���͡ else

?>
