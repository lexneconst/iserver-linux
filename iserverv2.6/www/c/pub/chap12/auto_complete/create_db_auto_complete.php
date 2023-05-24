<?php

	$dblink = mysql_connect("localhost", "root", "123");
	mysql_query("USE ajax;");
	
$sql = <<<SQL

	CREATE TABLE auto_complete(
	title VARCHAR(50),
	index(title));
SQL;
	
	$result = mysql_query($sql);
	
$sql = <<<SQL

	INSERT INTO auto_complete VALUES
	('ajaxthai.net'),
	('Ajax and PHP'),
	('Ajax and ASP.NET'),
	('Ajax Amsterdam'),
	('Angel of Bangkok'),
	('CSS for Web Designer'),
	('C# Bible'),
	('C++ Reference'),
	('C Programming');

SQL;
	mysql_query($sql);

	mysql_close($dblink);
?>