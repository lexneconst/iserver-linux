<?php
	header("Content-Type:text/plain; charset=tis-620");

	$num_food = count($_POST['food']);
	
	$food = "";
	for($i=0; $i<$num_food; $i++) {
		if($food != "") {
			$food .= ", ";
		}
		$food .= $_POST['food'][$i];
	}
	$food = "<b>�����:</b> " . enc($food);
	
	$drink = implode(", ", $_POST['drink']);
	$drink = "<b>����ͧ����:</b> " . enc($drink);

	echo "��¡�÷�����:<br> $food <br> $drink";

?>
<?php
function enc($input){
	return iconv('utf-8', 'tis-620', $input);
}
?>