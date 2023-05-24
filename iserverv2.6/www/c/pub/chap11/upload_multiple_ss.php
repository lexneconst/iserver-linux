
<?php
	$file_data = array();
	$num = count($_FILES['upfile']['name']);
	for($i=0; $i<$num; $i++) {
		if($_FILES['upfile']['error'][$i]!=0) {
			$file_data[$i] = "";
			continue;
		}

		$file = $_FILES['upfile']['tmp_name'][$i];
		$file_handle = fopen($file, "r");
		$file_data_ = fread($file_handle, filesize($file));

		$file_data[$i] = addslashes($file_data_);

		fclose($file_handle);
	}

	/*
	จากนั้นเราสามารถนำค่าจากตัวแปร $file_data[$i] แต่ละตัวไป
	ใช้งานอย่างอื่นต่อไปได้ เช่น หากเก็บในฐานข้อมูล อาจทำในลักษณะดังนี้

	$sql = <<<SQL
		INSERT INTO table1 VALUES(
		'$id', '$...', '{$file_data[0]}', '{$file_data[1]}',...);
	SQL;
	.
	.
	*/
?>
