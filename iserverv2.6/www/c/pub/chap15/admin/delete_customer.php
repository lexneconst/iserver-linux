
<?php
	$custid = $_POST['cid'];

	$dblink = mysql_connect("localhost", "root", "123");
	mysql_query("USE shopping_cart;");

$sql = <<<SQL
	DELETE FROM customer, orders 
	USING(customer, orders) 
	WHERE customer.custid = $custid AND orders.custid = $custid;
SQL;
	mysql_query($sql);

	mysql_close($dblink);

	header("content-type: text/javascript; charset=tis-620");

	echo "document.getElementById('row_$custid').style.display = 'none';";

?>


	