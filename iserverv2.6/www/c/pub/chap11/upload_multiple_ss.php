
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
	�ҡ����������ö�Ӥ�Ҩҡ����� $file_data[$i] ���е���
	��ҹ���ҧ��蹵����� �� �ҡ��㹰ҹ������ �Ҩ����ѡɳдѧ���

	$sql = <<<SQL
		INSERT INTO table1 VALUES(
		'$id', '$...', '{$file_data[0]}', '{$file_data[1]}',...);
	SQL;
	.
	.
	*/
?>
