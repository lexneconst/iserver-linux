<html>
<head>

</head>
<body>
<?php
	$cust_id = $_GET['cid'];

	$dblink = mysql_connect("localhost", "root", "123");
	mysql_query("USE shopping_cart;");

$sql = <<<SQL
	SELECT * FROM customer
	WHERE custid = $cust_id;
SQL;
	
	$result = mysql_query($sql);
	$cust = mysql_fetch_array($result);

echo <<<CUST

<div style="font:bold 20pt;">Ajax Shopping Cart</div>
<table>
<tr><td colspan=2>&nbsp;</td></tr>
<tr><td>ชื่อ:</td><td>{$cust['name']}</td></tr>
<tr><td>ที่อยู่:</td><td>{$cust['address']}</td></tr>
<tr><td>โทร:</td><td>{$cust['phone']}</td></tr>
<tr><td>อีเมล์:</td><td>{$cust['email']}</td></tr>
<tr><td>การชำระเงิน:</td><td>{$cust['payment']}</td></tr>
</table>
<p>

CUST;

$sql = <<<SQL
	SELECT * FROM orders
	WHERE custid = $cust_id;
SQL;
	$result = mysql_query($sql);
?>
<p>
<table width="650" border="1" cellpadding="3" style="border-collapse:collapse;">
<tr bgcolor="#eeeeff"><th width="50">ลำดับ</th><th width="360">รายการ</th><th width="80">ราคา</th><th width="80">จำนวน</th><th width="80">รวม</th></tr>
<?php
	$i = 0;
	$gt = 0;
	while($ord = mysql_fetch_array($result)) {
		$st = $ord['price'] * $ord['quantity'];
		$gt += $st;
		$i++;
echo <<<TBODY
	<tr align="right" valign="top">
	<td align=center>$i</td>
	<td align="left">{$ord['product_name']}</td>
	<td>{$ord['price']}</td>
	<td>{$ord['quantity']}</td>
	<td>$st</td>
	</tr>
TBODY;
	}

	echo "<tr bgcolor=\"#eeeeff\" align=center><td colspan=2>รวมทั้งหมด</td><td colspan=3 align=right>$gt</td></tr>";
	echo "</table>";

	mysql_close($dblink);

?>

</body>
</html>