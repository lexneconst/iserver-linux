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
	('�˹��', '�����ͧ�͹'),
	('�˹��', '�ҡ'),
	('�˹��', '��ɳ��š'),
	('�˹��', '��⢷��'),

	('���ҹ', '���'),
	('���ҹ', '˹ͧ���'),
	('���ҹ', '��þ��'),
	('���ҹ', '�ء�����'),

	('��ҧ', '��ا෾'),
	('��ҧ', '�����ҹ�'),
	('��ҧ', '��ظ��'),
	('��ҧ', 'ž����'),

	('��', '��ѧ'),
	('��', '�ѧ��'),
	('��', '��к��'),
	('��', 'ʵ��');

SQL;
	mysql_query($sql);

	mysql_close($dblink);
?>