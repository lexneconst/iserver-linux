<?php
	$dblink = mysql_connect("localhost", "root", "123");
	mysql_query("USE chatroom;");

	$name = $_POST['nickname'];
	$name = enc($name);
	mysql_query("DELETE FROM chatter WHERE name = '$name';");

$sql = <<<SQL
	INSERT INTO message VALUES
	('', '# $name', 'ออกจากห้องสนทนา  #', 'red', NOW());
SQL;
	mysql_query($sql);

	$result = mysql_query("SELECT COUNT(*) FROM message;");  
	if(mysql_result($result, 0, 0)>=10) {
		$row = mysql_result($result, 0, 0) - 10;
		mysql_query("DELETE FROM message LIMIT $row;");
	}

$sql = <<<SQL
	DELETE FROM chatter
	WHERE DATEDIFF(NOW(), last_post_time) >= 1;
SQL;
	mysql_query($sql);

	mysql_close($dblink);
	header("content-type:text/javascript; charset=tis-620");
	echo "window.location = 'index.html';";
?>

<?php 	
function enc($input){
	return iconv("utf-8", "tis-620", $input);
} 
?>