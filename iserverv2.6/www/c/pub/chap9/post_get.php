<?php
	header("Content-Type:text/plain; charset=tis-620");

	$name = $_POST['name']; //iconv('utf-8', 'tis-620', $_POST['name']);
	$gender = $_POST['gender']; //iconv('utf-8', 'tis-620', $_POST['gender']);
	$address = $_POST['address']; //iconv('utf-8', 'tis-620', $_POST['address']);
	$lang = $_POST['lang']; //iconv('utf-8', 'tis-620', $_POST['lang']);

echo <<<HTML

	<table border="1" cellspacing="0">
	<tr><td width="60">����</td><td>$name</td></tr>
	<tr><td>��</td><td>$gender</td></tr>
	<tr><td>�������</td><td>$address</td></tr>
	<tr><td>���ҷ�����</td><td>$lang</td></tr>
	</table>

HTML;

?>