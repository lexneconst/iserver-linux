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
		$msg = "��ҹ�ѧ�����������";
	}
	else if(empty($address)) {
		$msg = "��ҹ�ѧ��������������";
	}
	else if(empty($phone)) {
		$msg = "��ҹ�ѧ��������������";
	}
	else if(!eregi($pattern, $email)) {
		$msg = "��ҹ��� Email ���١��ͧ����ٻẺ";
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
	var msg = '������Ѻ�����š����觫��ͧ͢��ҹ����<br>�ҡ��ҹ�����Թ����Ըա�÷���к����� ';
	msg += '<br>��Ҩд��Թ��èѴ���Թ�������ҹ�ѹ��<p>�ͺ��Фس������͡�����Թ��Ҩҡ���';
	msg += '<p><a href="shopping_cart.php">��Ѻ价��˹����ѡ</a>';
	document.getElementById('msg').innerHTML = msg;
JS;

?>

<?php
function enc($input) {
	return iconv('utf-8', 'tis-620', $input);
}
?>