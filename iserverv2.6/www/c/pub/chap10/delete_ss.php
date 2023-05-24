<?php
	header("content-type:text/javascript; charset=tis-620");

	$dblink = mysql_connect("localhost", "root", "123");
	mysql_query("USE ajax;");

	$id = $_POST['id'];
	
	$sql = "DELETE FROM books ";
	$sql .= "WHERE id = $id;";

	mysql_query($sql);

	if(mysql_affected_rows($dblink)==0) {
		echo "alert('ไม่สามารถลบข้อมูลได้');";
	}
	else {
		echo "var el = document.getElementById('$id');";
		echo "el.style.display = 'none';";
	}

	mysql_close($dblink);
?>