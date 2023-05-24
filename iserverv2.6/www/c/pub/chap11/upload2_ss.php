<?php
	$response = "";
	$save_path = "";
	
	if($_FILES['upfile']['error']!=0) {
		$response = "Error: {$_FILES['upfile']['error']}";
	}
	else {
		$accept_types = array("image/gif", "image/jpeg", "image/pjpeg", 
			"image/png", "image/x-png");
	
		$type = $_FILES['upfile']['type'];
		if(!in_array($type, $accept_types)) {
			$response .= "ต้องใช้ไฟล์ชนิด .gif, .jpeg, .jpg หรือ .png เท่านั้น<br>";
		}
		else {
			$save_dir = "upload_images";
			if(!file_exists($save_dir)) {
				mkdir($save_dir);
			}
			$save_path = $save_dir . "/" . $_FILES['upfile']['name'];

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