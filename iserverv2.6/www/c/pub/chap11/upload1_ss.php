<?php
	$response = "";

	if($_FILES['upfile']['error']!=0) {
		$response = "Error: {$_FILES['upfile']['error']}";
	}
	else {
		$accept_types = array("image/gif", "image/jpeg", "image/pjpeg", 
			"image/png", "image/x-png");
	
		$type = $_FILES['upfile']['type'];
		$type_ok = false;
		if(in_array($type, $accept_types)) {
			$type_ok = true;
		}
		if(!$type_ok) {
			$response .= "ต้องใช้ไฟล์ชนิด .gif, .jpeg, .jpg หรือ .png เท่านั้น<br>";
		}

		$size_Kb = ($_FILES['upfile']['size'])/1024;
		$size_ok = true;
		if($size_Kb > 100) {
			$response .= "ขนาดของไฟล์ต้องไม่เกิน 100 Kb <br>";
			$size_ok = false;
		}
		$dest = "";
		if($type_ok && $size_ok){
			$response .= "name: {$_FILES['upfile']['name']} <br>";
			$response .= "size(Kb): $size_Kb <br>";
			$response .= "type: $type <br>";
			mkdir("images");
			$save_path = "images/" . $_FILES['upfile']['name'];
			if(!move_uploaded_file($_FILES['upfile']['tmp_name'], $save_path)) {
				$response .= "Move Failed!";	
			}
		}
	}
?>

<script>
	top.document.getElementById('image').src = '<?php echo $save_path; ?>';
	top.document.getElementById('msg').innerHTML = '<?php echo $response; ?>';
</script>