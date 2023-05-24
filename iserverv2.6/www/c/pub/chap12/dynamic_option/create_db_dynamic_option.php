<?php

	$dblink = mysql_connect("localhost", "root", "123");
	mysql_query("USE ajax;");
	
$sql = <<<SQL

	CREATE TABLE dynamic_option(
	religion VARCHAR(20),
	province VARCHAR(100),
	index(religion));
SQL;
	
	$result = mysql_query($sql);
	
$sql = <<<SQL

	INSERT INTO dynamic_option VALUES
	('เหนือ', 'แม่ฮ่องสอน'),
	('เหนือ', 'ตาก'),
	('เหนือ', 'พิษณุโลก'),
	('เหนือ', 'สุโขทัย'),

	('อีสาน', 'เลย'),
	('อีสาน', 'หนองคาย'),
	('อีสาน', 'นครพนม'),
	('อีสาน', 'มุกดาหาร'),

	('กลาง', 'กรุงเทพ'),
	('กลาง', 'ปทุมธานี'),
	('กลาง', 'อยุธยา'),
	('กลาง', 'ลพบุรี'),

	('ใต้', 'ตรัง'),
	('ใต้', 'พังงา'),
	('ใต้', 'กระบี่'),
	('ใต้', 'สตูล');

SQL;
	mysql_query($sql);

	mysql_close($dblink);
?>