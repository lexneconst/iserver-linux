<?php
	$dblink = mysql_connect("localhost","root","123");
	mysql_query("USE chatroom;");
	
$sql = <<<SQL
	SELECT *, TIME(post_time) AS pt FROM message
	ORDER BY post_time DESC
	LIMIT 10;
SQL;

	$result = mysql_query($sql);

$tb = <<<TABLE
	<table width="520">
	<tr>
		<td width="40"></td><td width="100"></td>
		<td width="10"></td><td width="370"></td>
	</tr>
TABLE;
	$msg = "";
	$num_msg = mysql_num_rows($result);
	for($i=($num_msg-1); $i>=0; $i--) {
		$mg = mysql_result($result, $i, "msg");
		$color = mysql_result($result, $i, "color");
		$m = "<font color=$color>$mg</font>";
		$t = mysql_result($result, $i, "pt");
		$n = mysql_result($result, $i, "name");
		
$tbody = <<<TBODY
	<tr valign="top">
		<td>$t</td>
		<td align="right"><b>$n</b></td>
		<td>:</td>
		<td>$m</td>
	</tr>
TBODY;
		
		$msg .= $tbody;
	}

	$response = $tb . $msg . "</table>";
	
	mysql_close($dblink);

	header("content-type:text/plain; charset=tis-620");
	echo $response;
?>