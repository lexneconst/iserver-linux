<?php
	$dblink = mysql_connect("localhost", "root", "123");
	mysql_query("USE ajax;");
	//ฐานข้อมูลชื่อ "ajax" เราได้สร้างไว้ตั้งแต่บทก่อนๆ หากยังไม่มีต้องสร้างขึ้นก่อน

$sql = <<<SQL

	CREATE TABLE member(
		id SMALLINT NOT NULL AUTO_INCREMENT,
		login VARCHAR(30),
		password VARCHAR(20),
		email VARCHAR(100),
		name VARCHAR(50),
		UNIQUE(login),
		PRIMARY KEY(id)
	);
SQL;

	$qry = mysql_query($sql);
	if(!$qry) {
		echo "การสร้างตาราง: member ผิดพลาด";
	}
	else {
		echo "การสร้างตาราง: member เสร็จเรียบร้อย";
	}
	
	mysql_close($dblink);

?>