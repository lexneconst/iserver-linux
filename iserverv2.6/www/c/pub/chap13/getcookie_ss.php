<?php	
	header("content-type:text/javascript; charset=tis-620");

	if(isset($_COOKIE['login'])) {
		$login = $_COOKIE['login'];

echo <<<JS
	
	document.getElementById('login').value = '$login';
	document.getElementById('store_login').checked = true;

JS;

	}
?>
