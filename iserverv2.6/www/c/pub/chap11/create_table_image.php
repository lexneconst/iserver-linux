<?php
	$dblink = mysql_connect("localhost", "root", "123");
	mysql_query("USE ajax;");

$sql = <<<SQL

 	CREATE TABLE image(
		id SMALLINT NOT NULL AUTO_INCREMENT,
		img_data BLOB,
 		img_name VARCHAR(30),
 		img_type VARCHAR(20),
 		img_size SMALLINT UNSIGNED,
 		PRIMARY KEY(id)
 	);
SQL;

	$qry = mysql_query($sql);
	if($qry) {
		echo "������ҧ���ҧ: image �������º����";
	}
	else {
		echo "������ҧ���ҧ: image �������º����";
	}
	mysql_close($dblink);

?>