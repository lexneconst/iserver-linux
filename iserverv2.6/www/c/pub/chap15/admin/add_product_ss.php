<?php
	$dblink = mysql_connect("localhost", "root", "123");
	mysql_query("USE shopping_cart;");

	$pdname = htmlspecialchars($_POST['pdname'], ENT_QUOTES);
	$descr = htmlspecialchars($_POST['descr'], ENT_QUOTES);
	$price = $_POST['price'];

	$file_data = "";
	if($_FILES['img']['error']==0) {
		$file = $_FILES['img']['tmp_name'];
		$file_handle = fopen($file, "r");
		$file_data = fread($file_handle, filesize($file));
		$file_data = addslashes($file_data);
		fclose($file_handle);
	}

$sql = <<<SQL
	
	INSERT INTO product VALUES
	('', '$pdname', '$price', '$descr', '$file_data');
SQL;

	mysql_query($sql);
	$msg = "";
	$reset_form = "";
	if(mysql_affected_rows($dblink)==0) {
		$msg = "เกิดข้อผิดพลาดในการบันทึกข้อมูล";
	}
	else {
		$msg = "ข้อมูลได้รับการบันทึกแล้ว";
		$reset_form = "top.document.forms['frm'].reset();";
	}
	mysql_close($dblink);

?>

<script>
	top.document.getElementById('indicator').innerHTML = "";
 	alert('<?php echo $msg; ?>');
	<?php echo $reset_form; ?>
</script>