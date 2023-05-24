<?php
	header("content-type:text/html; charset=tis-620");

	$dblink = mysql_connect("localhost", "root", "123");
	mysql_query("USE ajax;");
	$id = $_POST['bid'];
	
	$sql = "DELETE FROM books ";
	$sql .= "WHERE id = $id;";
	//$qry = mysql_query($sql);
	//if(!$qry || mysql_affected_rows($dblink)==0) {
	//	echo "alert('ไม่สามารถลบข้อมูลได้');";
	//	mysql_close($dblink);
	//	exit();
	//}
	
	mysql_close($dblink);
	
	$response = "document.getElementById('b_$id').style.display = 'none';";
	echo $response;
?>