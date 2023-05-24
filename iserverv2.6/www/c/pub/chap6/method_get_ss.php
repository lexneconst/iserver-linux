<?php
	$op1 = $_GET['op1'];
	$op2 = $_GET['op2'];
	$sign = $_GET['sign'];
	switch($sign) {
		case "plus": 
 			echo $op1 + $op2; break;
		case "minus": 
 			echo $op1 - $op2; break;
		case "multiply": 
 			echo $op1 * $op2; break;
		case "divide": 
 			echo $op1 / $op2; break;
	}
?>
