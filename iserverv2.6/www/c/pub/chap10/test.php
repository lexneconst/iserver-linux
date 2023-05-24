<?php

	if(mysql_connect("localhost", "root", "123")) {
		echo "yes";
	}
	else {
		echo "no";
	}
?>