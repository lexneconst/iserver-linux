<?php
	session_start();

	header("content-type:text/javascript; charset=tis-620");

	if(isset($_SESSION['login'])) {
		unset($_SESSION['login']);
		
		echo "showForm()";
	}
	else {
		echo "alert('��ҹ�ѧ������������к�');";
	}
?>