<?php
	header("content-type:text/javascript; charset=tis-620");

	$tt = iconv('utf-8', 'tis-620', $_POST['tt']); 
	$title = addslashes($tt);   					
	
	$au = iconv('utf-8', 'tis-620', $_POST['au']); 
	$author = addslashes($au);    				
	
	$price = $_POST['pc'];

$sql = <<<SQL

	INSERT INTO books VALUES
	('', '$title', '$author', $price);

SQL;

	$dblink = mysql_connect("localhost", "root", "123");
	mysql_query("USE ajax;");

	mysql_query($sql);

	$msg = "";
	$resetForm = "";
 	if(mysql_affected_rows($dblink)==0) {
		$msg = "<font color=red>";
 		$msg .= "เกิดข้อผิดพลาด ไม่สามารถจัดเก็บข้อมูลได้</font>";
	}
	else {
		$msg = "ข้อมูลถูกจัดเก็บแล้ว กรุณาใส่ข้อมูลลำดับถัดไป";
		$resetForm = "document.getElementById('frm').reset();";
	}

	mysql_close($dblink);

echo <<<JS
	var el = document.getElementById('displayDiv');
	el.innerHTML = "$msg";
	$resetForm
JS;

?>
