<?php
	$dblink = mysql_connect("localhost","root","123");
	mysql_query("CREATE DATABASE chatroom;");
	mysql_query("USE chatroom;");
	
$sql = <<<SQL
	CREATE TABLE chatter(
	name VARCHAR(30) PRIMARY KEY,
	last_post_time DATETIME
	);
SQL;

	$create_tb_chatter = mysql_query($sql);
	if(!$create_tb_chatter) {
		echo "CREATE TABLE chatter: Error<br>";
	}
	else {
		echo "CREATE TABLE chatter: Success<br>";
	}

$sql = <<<SQL
	
	CREATE TABLE message(
	id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
	name VARCHAR(30), 
	msg VARCHAR(250),
	color VARCHAR(20),
	post_time DATETIME
	);
SQL;

	$create_tb_message = mysql_query($sql);
	if(!$create_tb_message) {
		echo "CREATE TABLE message: Error<br>";
	}
	else {
		echo "CREATE TABLE message: Success<br>";
	}		
	
	mysql_close($dblink);

?>