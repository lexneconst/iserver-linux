<?php
	$content = $_GET['content'];
	header("content-type: text/plain; charset=tis-620");

	readfile("$content.txt");

?>