<?php
	header("content-type:text/javascript; charset=tis-620");

	$pattern = 
 "^[_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.([a-z]){2,4})$";

	$from = $_POST['from'];
	$to = $_POST['to'];
	
	if(!ereg($pattern, $from)) {
		echo "alert('������ͧ����� ���١��ͧ����ٻẺ');";
		exit();
	}
	else if(!ereg($pattern, $to)) {
		echo "alert('������ͧ����Ѻ ���١��ͧ����ٻẺ');";
		exit();
	}

	$subject = thai_enc($_POST['subject']);
	$body = thai_enc($_POST['body']);

	$header = "From:$from\r\n";

	if(mail($to, $subject, $message, $header)) {
		echo "alert('����������������º����');";
	}
	else {
		echo "alert('����������Դ��ͼԴ��Ҵ!');";
	}


?>

<?php
function thai_enc($input) {

	return iconv('utf-8','tis-620',$input);

}
?>