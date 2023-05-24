<?php
	header("content-type: text/plain; charset=tis-620");

	$check = $_POST['check'];
	$pattern = "";
	if($check=="login") {
		$pattern = "^[a-zA-Z0-9_]{5,15}$";
	}
	else if($check=="email") {
		$pattern = 
 "^[_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.([a-z]){2,4})$";

	}
	else if($check=="website") {
		$pattern = "^http:\/\/(.*)$";
	}

	$data = $_POST['data'];
	if(!ereg($pattern, $data)) {
		echo "ข้อมูลไม่ถูกต้องตามรูปแบบ";
	}
	else {
		echo "";
	}
?>
