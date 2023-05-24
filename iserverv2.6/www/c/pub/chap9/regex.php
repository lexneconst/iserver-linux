<?php
	$source = $_POST['source'];
	$pattern = "";
	if($source=="zip") {
		$pattern = "^[0-9]{5}$";
	}
	else if($source=="mobile") {
		$pattern = "^08[0-9]{8}$";
	}

	$data = $_POST['data'];
	if(!ereg($pattern, $data)) {
		echo "ERROR";
	}
	else {
		echo "OK";
	}
?>