<?php
	session_start();
	$name = enc($_POST['nickname']);
	$name = addslashes($name);
							
	$dblink = mysql_connect("localhost", "root", "123");
	mysql_query("USE chatroom;");

$sql = <<<SQL
	SELECT COUNT(*) FROM chatter
	WHERE name = '$name';
SQL;
	$result = mysql_query($sql);
	
	if(mysql_result($result, 0, 0)>0) {
		header("content-type:text/plain; charset=tis-620");
		echo "ชื่อ: $name มีผู้ใช้แล้ว กรุณาใช้ชื่อใหม่";
		mysql_close($dblink);
		exit();
	}
	
$sql = <<<SQL
	INSERT INTO chatter VALUES
	('$name', NOW());
SQL;
	mysql_query($sql);

$sql = <<<SQL
	INSERT INTO message VALUES
	('', '@ $name', 'เข้าร่วมห้องสนทนา  @', 'red', NOW());
SQL;
	mysql_query($sql);
	$_SESSION['nickname'] = enc($_POST['nickname']);
		
	mysql_close($dblink);

	header("content-type:text/javascript; charset=tis-620");
	echo "window.location = 'chatroom.php';";
?>
<?php
function enc($input) {
	return iconv("utf-8","tis-620",$input);
}
?>