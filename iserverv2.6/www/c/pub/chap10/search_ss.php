<?php
	header("content-type:text/plain; charset=tis-620");

	$dblink = mysql_connect("localhost", "root", "123");
	mysql_query("USE ajax;");

	$q = iconv('utf-8', 'tis-620', $_GET['q']);
	$kw = addslashes($q);

	$sql = "SELECT * FROM books ";
	$sql .= "WHERE title LIKE '%$kw%';";

	$result = mysql_query($sql);
	if(!$result) {
		echo "�������ö�׺�鹢�������! $sql";
		mysql_close($dblink);
		exit();
	}

$response = <<<RES
	�š���׺�� $kw
 	<table border=1 cellpadding=5>
	<tr bgcolor="#dddddd">
	<th>����</th><th>����˹ѧ���</th><th>�����¹</th><th>�Ҥ�</th></tr>
RES;

	while($p = mysql_fetch_array($result)) {

$tbody = <<<TBODY

	<tr><td>{$p['id']}</td>
	<td>{$p['title']}</td>
	<td>{$p['author']}</td>
	<td>{$p['price']}</td></tr>

TBODY;
	$response .= $tbody;

	}  //end block while

	$response .= "</table>";
	
	if(mysql_num_rows($result)==0) {
		$response = "��辺�������Թ��� \"$kw\"";
	}

	mysql_close($dblink);

	echo $response;
?>
	