<?php
	session_start();

	$dblink = mysql_connect("localhost", "root", "123");
	mysql_query("USE shopping_cart;");

	$msg = "";
	$name = htmlspecialchars($_POST['name'], ENT_QUOTES);
	$name = enc($name);

	$address = htmlspecialchars($_POST['address'], ENT_QUOTES);
	$address = enc($address);

	$phone = htmlspecialchars($_POST['phone'], ENT_QUOTES);
	$phone = enc($phone);

	$email = htmlspecialchars($_POST['email'], ENT_QUOTES);
	$pattern = "^[_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.([a-z]){2,4})$";

	if(empty($name)) {
		$msg = "ท่านยังไม่ได้ใส่ชื่อ";
	}
	else if(empty($address)) {
		$msg = "ท่านยังไม่ได้ใส่ที่อยู่";
	}
	else if(empty($phone)) {
		$msg = "ท่านยังไม่ได้ใส่เบอร์โทร";
	}
	else if(!eregi($pattern, $email)) {
		$msg = "ท่านใส่ Email ไม่ถูกต้องตามรูปแบบ";
	}

	if($msg!="") {
		header("content-type:text/plain; charset=tis-620");
		echo $msg;
		exit();
	}

	$payment = enc($_POST['payment']);

$sql = <<<SQL
	
	INSERT INTO customer VALUES
	('', '$name', '$address', '$phone', '$email', '$payment', NOW());
SQL;
	mysql_query($sql);
	$cust_id = mysql_insert_id();

	$sid = session_id();
$sql = <<<SQL
	SELECT * FROM cart
	WHERE sid = '$sid';
SQL;
	$result = mysql_query($sql);
	while($cart = mysql_fetch_array($result)) {

$sql = <<<SQL
	INSERT INTO orders VALUES(
	'', $cust_id, {$cart['pid']}, '{$cart['product_name']}', 
	{$cart['price']}, {$cart['quantity']}
	);
SQL;
		mysql_query($sql);
	
	}

$sql = <<<SQL
	DELETE FROM cart
	WHERE sid = '$sid';
SQL;
	mysql_query($sql);

	mysql_close($dblink);

	header("content-type:text/javascript; charset=tis-620");

echo <<<JS
	document.forms['frm'].style.display = 'none';
	var msg = 'เราได้รับข้อมูลการสั่งซื้อของท่านแล้ว<br>หากท่านชำระเงินตามวิธีการที่ระบุแล้ว ';
	msg += '<br>เราจะดำเนินการจัดส่งสินค้าให้ท่านทันที<p>ขอบพระคุณที่เลือกซื้อสินค้าจากเรา';
	msg += '<p><a href="shopping_cart.php">กลับไปที่หน้าหลัก</a>';
	document.getElementById('msg').innerHTML = msg;
JS;

?>

<?php
function enc($input) {
	return iconv('utf-8', 'tis-620', $input);
}
?>