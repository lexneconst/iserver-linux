<?php
	session_start();
?>
<html>
<body>
<?php
	if(isset($_SESSION['login'])) {
		echo "��ҹ�������к�����";
	}
	else {
		echo "��ҹ�ѧ������������к�";
	}
?>
<p>
<a href="session.php">Back</a>

</body>
</html>
