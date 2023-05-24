<?php
	session_start();

	$dblink = mysql_connect("localhost","root","123");
	mysql_query("USE shopping_cart;");

	$sid = session_id();

	$pid = "";
	if(isset($_POST['pid'])) {
		$pid = $_POST['pid'];
	}
	$act = "";
	if(isset($_POST['act'])) {
		$act = $_POST['act'];
	}
	
	$sql = "";

	if($act=="add") {
		$q = $_POST['q'];
		
$sql = <<<SQL
	SELECT product_name, price FROM product
	WHERE pid = $pid;
SQL;
	$result = mysql_query($sql);
	$pname = mysql_result($result,0,0);
	$price = mysql_result($result,0,1);

$sql = <<<SQL
	REPLACE INTO cart VALUES
	('$sid', $pid, '$pname', $price, $q, NOW());
SQL;

	}
	else if($act=="del") {
		
$sql = <<<SQL
	DELETE FROM cart
	WHERE pid = $pid;
SQL;
	}
	else if($act=="clear") {
$sql = <<<SQL
	DELETE FROM cart
	WHERE sid = '$sid';
SQL;
	}

	mysql_query($sql);

$sql = <<<SQL
	SELECT * FROM cart
	WHERE sid = '$sid';
SQL;
	$result = mysql_query($sql);

	header("content-type:text/plain; charset=tis-620");
	if(mysql_num_rows($result)==0) {
		echo "ไม่มีสินค้าในรถเข็น";
		mysql_close($dblink);
		exit();
	}

$tb = <<<TABLE
	<table width="98%" border="1" bordercolor="gray" style="border-collapse:collapse;">
	<caption>รายการสินค้าในรถเข็น</caption>
	<tr align="right" bgcolor="powderblue">
		<th align="center">สินค้า</th><th>ราคา</th><th>#</th><th>รวม</th>
	</tr>

TABLE;
	$grand_total = 0;
	while($cart = mysql_fetch_array($result)) {
		$sub_total = $cart['price'] * $cart['quantity'];

$tbody = <<<TBODY
	<tr align="right" valign="top">
	<td align="left">
		<div style="float:left;"> 
 			<!--	
			<button onclick="viewProduct({$cart['pid']})" 
				class="bt_cart">ดู</button>&nbsp;
			-->
			<button onclick="delCart({$cart['pid']})" 
				class="bt_cart">ลบ</button>
		</div>

		{$cart['product_name']}

 	</td>
	<td>{$cart['price']}</td>
	<td>{$cart['quantity']}</td>
	<td>$sub_total</td>
	</tr>
TBODY;
		$tb .= $tbody;

		$grand_total += $sub_total;
	}
	$tb .= "<tr><td align=center>รวมทั้งหมด</td><td align=right colspan=3>$grand_total</td></tr>";
	$tb .= "</table>";

$bt = <<<BT
	<p align="center">
	<button onclick="clearCart()">ลบทั้งหมด</button>
	&nbsp;&nbsp;&nbsp;&nbsp;
	<button onclick="location='customer_info.html'">สั่งชื่อ&nbsp;&raquo;</button>
	</p>
BT;
	
	echo $tb . $bt;

	mysql_close($dblink);
?>