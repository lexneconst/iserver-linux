<?php
	$dblink = mysql_connect("localhost", "root", "123");
	mysql_query("CREATE DATABASE shopping_cart;"); 
	mysql_query("USE shopping_cart;");
	
$sql = <<<SQL

	CREATE TABLE product(
		pid SMALLINT NOT NULL AUTO_INCREMENT PRIMARY KEY,
		product_name VARCHAR(100),
		price SMALLINT,
		description TEXT,
		img BLOB
	);
SQL;

	$tb_product = mysql_query($sql);
	if(!$tb_product) {
		echo "create table: product Error!<br>";
	}

$sql = <<<SQL

	CREATE TABLE cart(
		sid VARCHAR(40) NOT NULL,
		pid SMALLINT,
		product_name VARCHAR(100),
		price SMALLINT,
		quantity TINYINT UNSIGNED,
		date_shopping DATE, 
		PRIMARY KEY(sid, pid)
	);
SQL;

	$tb_cart = mysql_query($sql);
	if(!$tb_cart) {
 		echo "create table: cart Error!<br>";
	}

$sql = <<<SQL

	CREATE TABLE customer(
		custid SMALLINT NOT NULL AUTO_INCREMENT PRIMARY KEY,
		name VARCHAR(50),
		address TEXT,
		phone VARCHAR(50),
		email VARCHAR(100),
		payment VARCHAR(30),
		order_date DATE
	);
SQL;

	$tb_cust = mysql_query($sql);
	if(!$tb_cust) {
 		echo "create table: customer Error!<br>";
	}

$sql = <<<SQL

	CREATE TABLE orders(
		orid SMALLINT NOT NULL AUTO_INCREMENT PRIMARY KEY,
		custid SMALLINT,
		pid SMALLINT,
		product_name VARCHAR(100),
		price SMALLINT,
		quantity TINYINT UNSIGNED
	);
SQL;

	$tb_ord = mysql_query($sql);
	if(!$tb_ord) {
 		echo "create table: orders Error!<br>";
	}

	mysql_close($dblink);

?>