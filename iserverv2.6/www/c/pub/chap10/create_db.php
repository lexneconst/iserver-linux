<?php
	$dblink = mysql_connect("localhost", "root", "123");
	$create_db = mysql_query("CREATE DATABASE ajax;");
	if(!$create_db) {
		echo "�������ö���ҧ�ҹ��������";
		mysql_close($dblink);
		exit();
	}
	mysql_query("USE ajax;");

$sql = <<<SQL

	CREATE TABLE books(
	id SMALLINT NOT NULL AUTO_INCREMENT,
	title VARCHAR(100),
	author VARCHAR(50),
	price SMALLINT,
	PRIMARY KEY(id))Engine = MyISAM;
SQL;

	$create_tb = mysql_query($sql);
	if(!$create_tb) {
		echo "�������ö���ҧ���ҧ��������";
		mysql_close($dblink);
		exit();
	}
	else {
		echo "������ҧ���ҧ: books �������º����";
	}

	mysql_close($dblink);
?>