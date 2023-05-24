<?php
	$religion = enc($_GET['religion']);

	$dblink = mysql_connect("localhost", "root", "123");
	mysql_query("USE ajax;");
	
$sql = <<<SQL

	SELECT province FROM dynamic_option
	WHERE religion = '$religion';
SQL;
	
	$result = mysql_query($sql);

	$response = "";

$javascript = <<<JS
	var el = document.getElementById('province');
	while(el.length>0) {
		el.remove(0);
	}
JS;

	$response = $javascript;

	while($data = mysql_fetch_array($result)) {

$javascript = <<<JS
	
	var opt = document.createElement('option');
	opt.value = "{$data['province']}";
	opt.text = "{$data['province']}";
	
	document.getElementById('province').add(opt);
JS;

		$response .= $javascript;
	}

	header("content-type: text/javascript; charset=tis-620");
	echo $response;
	mysql_close($dblink);
?>

<?php
function enc($input) {
	return iconv('utf-8', 'tis-620', $input);
}
?>