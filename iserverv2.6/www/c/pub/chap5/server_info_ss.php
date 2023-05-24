<?php

	$result = "";

	$server_vars = array('HTTP_USER_AGENT', 'HTTP_HOST', 
		'SERVER_SOFTWARE','DOCUMENT_ROOT', 'SCRIPT_FILENAME', 
		'REQUEST_METHOD', 'REQUEST_URI', 'PHP_SELF');

	for($i=0; $i<count($server_vars); $i++) {
		$var = $server_vars[$i];
		$result .= "<b>$var:</b> {$_SERVER[$var]}<br>";
	}

	echo $result;

?>