<?php

	$count = 0;

	if(isset($_POST['b'])) {
		$count = count($_POST['b']);
	}
	$tbody = "";
	$gt = 0;
	for($i=0; $i<$count; $i++) {
		if(!isset($_POST['b'])) {
			
		$tbody .= "<tr><td>{$_POST['b'][$i]}</td>";
		$tbody .= "<td>{$_POST['p'][$i]}</td>";
		$tbody .= "<td>{$_POST['q'][$i]}</td>";
		$st = $_POST['p'][$i] * $_POST['q'][$i];
		$tbody .= "<td>$st</td></tr>";
	
		$gt += $st;
	}

	if($tbody!="") {
		$table = "<table border=1 cellpadding=3>";
		$table .= "<tr><th>����</th><th>�Ҥ�</th><th>�ӹǹ</th><th>���</th></tr>";
		$table .= $tbody;
		$table .= "</table>";
	}

	header("content-type: text/plain; charset=tis-620");
	echo $table;

?>
		
