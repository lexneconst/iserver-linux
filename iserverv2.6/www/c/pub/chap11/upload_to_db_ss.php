<?php

	$msg = "";
	$file_data = "";

	if($_FILES['upfile']['error']!=0) {
		$msg = "การ Upload เกิดข้อผิดพลาด";
	}
	else {
		$file = $_FILES['upfile']['tmp_name'];
		$file_handle = fopen($file, "r");
		$file_data_ = fread($file_handle, filesize($file));
		$file_data = addslashes($file_data_);
		fclose($file_handle);

		$name = $_FILES['upfile']['name'];
		$type = $_FILES['upfile']['type'];
		$size = $_FILES['upfile']['size'];

		$dblink = mysql_connect("localhost", "root", "123");
		mysql_query("USE ajax;");

$sql = <<<SQL
	INSERT INTO image VALUES(
	'', '$file_data', '$name', '$type', '$size');
SQL;

		$qry = mysql_query($sql);
		if(mysql_affected_rows($dblink)==0) {
			$msg = "ไม่สามารถจัดเก็บไฟล์ที่ Upload ได้";
		}
		else {
			$msg = "ไฟล์ที่ Upload ถูกจัดเก็บแล้ว";
		}
		
		mysql_close($dblink);
	}

?>

<script>
	var el = top.document.getElementById('msg');
	 el.innerHTML = '<?php echo $msg; ?>';
</script>

