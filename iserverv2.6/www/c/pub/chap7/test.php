<?php
	$pdc = array("สินค้า 1", "สินค้า 2", "สินค้า 3");
	$prc = array(200, 300, 100);
	$qun = array(3, 1, 5);

$response = <<<RES

	<table width="500" border="1" cellspacing="1">
	<tr bgcolor="#dddddd">
		<th width="">สินค้า</th><th width="">ราคา</th>
		<th width="">จำนวน</th><th>รวม</th>
	</tr>
	<tr>
		<td>{$pdc[0]}</td><td>{$prc[0]}</td><td>{$qun[0]}</td><td>...</td>
	</tr>
	<tr>
		<td>{$pdc[1]}</td><td>{$prc[1]}</td><td>{$qun[1]}</td><td>...</td>
	</tr>
	<tr>
		<td>{$pdc[2]}</td><td>{$prc[2]}</td><td>{$qun[2]}</td><td>...</td>
	</tr>
	<tr>
		<td colspan="3">รวม</td><td>...</td>
	</tr>
	</table>

RES;
	header("content-type: text/plain; charset=tis-620");
	echo $response;

?>

<?php

	$condition = ...;

$sql = <<<SQL

	SELECT *
	FROM table1
	WHERE column1 = '$condition'
	ORDER BY column2
	LIMIT 20;
SQL;

	$result = mysql_query($sql);
	.
	.

?>

<?php
	$resp = "...";

	header("content-type: text/javascript; charset=tis-620");

echo <<< JS
	
	var el = document.getElementById('displayId');
	el.innerHTML = '$resp';
	el.style.color = '#00ffff';
	alert('Ajax Done!');

JS;

?>