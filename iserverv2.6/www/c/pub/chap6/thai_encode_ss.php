<?php
	header("Content-Type:text/plain; charset=tis-620");

	$name = $_POST['name']; //iconv('utf-8', 'tis-620', $_POST['name']);
	$gender = $_POST['gender']; //iconv('utf-8', 'tis-620', $_POST['gender']);
	$address = $_POST['address']; //iconv('utf-8', 'tis-620', $_POST['address']);
	$lang = $_POST['lang']; //iconv('utf-8', 'tis-620', $_POST['lang']);

	$html = "<table border=1 cellspacing=0>";
	$html .= "<tr><td width=60>����</td><td>$name</td></tr>";
	$html .= "<tr><td>��</td><td>$gender</td></tr>";
	$html .= "<tr><td>�������</td><td>$address</td></tr>";
	$html .= "<tr><td>���ҷ�����</td><td>$lang</td></tr>";
	$html .= "</table>";

	echo $html;

?>