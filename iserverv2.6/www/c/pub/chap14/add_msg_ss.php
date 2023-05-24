<?php
	$name = $_POST['nickname'];
	$msg = trim($_POST['msg']);
	if(empty($name) || empty($msg)) {
		exit();
	}
	$dblink = mysql_connect("localhost", "root", "123");
	mysql_query("USE chatroom;");

	$name = enc($name);
$sql = <<<SQL
	SELECT COUNT(*) FROM chatter
	WHERE name = '$name';
SQL;
	$result = mysql_query($sql);

	$count = mysql_result($result,0,0);
	if($count==0) {
		mysql_close($dblink);
		exit();
	}
	$msg = enc($msg);
	$msg = clean_rude_words($msg);
	$msg = htmlspecialchars($msg, ENT_QUOTES);
	$color = $_POST['color'];

$sql = <<<SQL
	INSERT INTO message VALUES
 	('', '$name', '$msg', '$color', NOW());
SQL;
	mysql_query($sql);

$sql = <<<SQL
	UPDATE chatter
	SET last_post_time = NOW()
	WHERE name = '$name';
SQL;
	mysql_query($sql);
	mysql_close($dblink);
	
	header("content-type:text/plain; charset=tis-620");
	echo "";
?>

<?php 	
function enc($input){
	return iconv("utf-8", "tis-620", $input);
} 
function clean_rude_words($input) {
	$rudes = array("xxx", "yyy", "zzz");
	for($i=0; $i<count($rudes); $i++) {
		$r = $rudes[$i];
		$input = str_ireplace($r, "***", $input);
	}
	return $input;
}
?>