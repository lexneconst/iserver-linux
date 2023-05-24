<?php
	header("content-type:text/javascript; charset=tis-620");

	$pattern = 
 "^[_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.([a-z]){2,4})$";

	$from = $_POST['from'];
	$to = $_POST['to'];
	
	if(!ereg($pattern, $from)) {
		echo "alert('อีเมล์ของผู้ส่ง ไม่ถูกต้องตามรูปแบบ');";
		exit();
	}
	else if(!ereg($pattern, $to)) {
		echo "alert('อีเมล์ของผู้รับ ไม่ถูกต้องตามรูปแบบ');";
		exit();
	}

	$subject = thai_enc($_POST['subject']);
	$body = thai_enc($_POST['body']);

	$header = "From:$from\r\n";

	if(mail($to, $subject, $message, $header)) {
		echo "alert('การส่งเมล์เสร็จเรียบร้อย');";
	}
	else {
		echo "alert('การส่งเมล์เกิดข้อผิดพลาด!');";
	}


?>

<?php
function thai_enc($input) {

	return iconv('utf-8','tis-620',$input);

}
?>