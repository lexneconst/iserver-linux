<?php
	session_start();	
?>
<html>
<head>
<script src="/ajaxbook/ajax_framework.js"> </script>
<script>
function ajaxSubmit() {
	if(!confirm('¡��ԡ�������Ҫԡ?')) {
		return;
	}
	var data = "x=1";
	
	var URL = "member_delete_ss.php";
	
	ajaxLoad('post', URL, data, 'msg');
}
</script>
</head>
<body style="text-align:center;">
<h2>¡��ԡ�������Ҫԡ?..</h2>

<?php
	if(isset($_SESSION['login'])) {
?>
<form name="frm">
<button onclick="ajaxSubmit()">¡��ԡ�������Ҫԡ</button>
</form>
<?php
	}
	else {
		echo "��ҹ��ͧ Login �������к���͹�֧�����ԡ�ù����";
	}
?>
<p>
<a href="index.php">˹���á</a>
</body>
</html>