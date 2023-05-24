<?php
	$title = $_GET['title'];
	if(empty($title)) {
		listbox("", "none", "");
		exit();
	}

	$dblink = mysql_connect("localhost", "root", "123");
	mysql_query("USE ajax;");
	
$sql = <<<SQL

	SELECT * FROM auto_complete
	WHERE title LIKE '$title%';
SQL;
	
	$result = mysql_query($sql);
	
	if(mysql_num_rows($result)==0) {
		listbox("", "none", $dblink);
		exit();
	}

	$list = "";
	while($data = mysql_fetch_array($result)) {
		$list .= "<div onclick=\"readText(this)\" ";
		$list .= "onmouseover=\"msOverList(this)\" ";
		$list .= "onmouseout=\"msOutList(this)\">";
		$list .= $data['title'];
		$list .= "</div>";
	}

	listbox($list, "block", $dblink);
	exit();
?>

<?php
function listbox($innerHTML, $display, $dblink) {

$javascript = <<<JS

	document.getElementById('listbox').innerHTML = '$innerHTML';
	document.getElementById('listbox').style.display = '$display';

JS;
	header("content-type: text/javascript; charset=tis-620");
	echo $javascript;
	if($dblink) {
		mysql_close($dblink);
	}
}
?>