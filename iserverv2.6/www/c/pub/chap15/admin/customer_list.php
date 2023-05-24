<html>
<head>
<script src="/ajaxbook/ajax_framework.js"> </script>
<script>
function viewCustomer(cid) {
	open('view_order.php?cid=' + cid);
}
function deleteCustomer(cid) {
	if(!confirm('Delete this customer?')) {
		return;
	}

	var data = "cid=" + cid;
	var URL = "delete_customer_ss.php";
	ajaxLoad('post', URL, data, 'msg');
}
</script>
</head>
<body>
<?php
	$dblink = mysql_connect("localhost", "root", "123");
	mysql_query("USE shopping_cart;");

$sql = <<<SQL
	SELECT *, DATE_FORMAT(order_date,'%d-%m-%Y') AS dt
	FROM customer;
SQL;
	
	$result = mysql_query($sql);
?>
<p>
<table width="600" border="1" cellpadding="3" style="border-collapse:collapse;">
<tr bgcolor="#eeeeff"><th width="50">ลำดับ</th><th width="250">ชื่อลูกค้า</th><th width="100">วันที่สั่งซื้อ</th><th>ดำเนินการ</th></tr>
<?php
	$i = 0;
	while($cust = mysql_fetch_array($result)) {
		$i++;
echo <<<TBODY
	<tr id="row_{$cust['custid']}" align="center" valign="top">
	<td>$i</td><td align="left">{$cust['name']}</td><td>{$cust['dt']}</td>
	<td><button onclick="viewCustomer({$cust['custid']})">รายละเอียด</button>&nbsp;&nbsp;
		<button onclick="deleteCustomer({$cust['custid']})">ลบ</button>
	</td>
	</tr>
TBODY;
	}
	echo "</table>";

	mysql_close($dblink);

?>
</body>
</html>