<?php
	$dblink = mysql_connect("localhost", "root", "123");
	mysql_query("USE shopping_cart;");

	$pid = $_GET['pid'];
	$sql = "SELECT img FROM product WHERE pid = $pid;";
	$result = mysql_query($sql);
	$data = mysql_result($result, 0, "img");
	echo $data;

	mysql_close($dblink);
?>