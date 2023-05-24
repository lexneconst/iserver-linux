<?php

	$num = $_GET['num'];
	$result = ($num%2==0)? "Even" : "Odd";
	echo "$num is an $result number";

?>
