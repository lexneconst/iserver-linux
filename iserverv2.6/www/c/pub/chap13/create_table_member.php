<?php
	$dblink = mysql_connect("localhost", "root", "123");
	mysql_query("USE ajax;");
	//�ҹ�����Ū��� "ajax" ��������ҧ������躷��͹� �ҡ�ѧ����յ�ͧ���ҧ��鹡�͹

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
		echo "������ҧ���ҧ: member �Դ��Ҵ";
	}
	else {
		echo "������ҧ���ҧ: member �������º����";
	}
	
	mysql_close($dblink);

?>