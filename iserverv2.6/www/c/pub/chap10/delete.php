<html>
<head>
<script src="/ajaxbook/ajax_framework.js"> </script>
<script>
function deleteData(id) {
	var URL = "delete_ss.php";

	var data = "id=" + id;

	ajaxLoad('post', URL, data, '');
}
</script>
</head>
<body>
<?php
	$dblink = mysql_connect("localhost", "root", "123");
	mysql_query("USE ajax;");

	$sql = "SELECT * FROM books ";
	$result = mysql_query($sql);
?>

<table border=1 cellpadding=5>
<tr bgcolor="#dddddd"><th>ชื่อหนังสือ</th><th>ผู้เขียน</th><th>ราคา</th><th>ลบ</th></tr>
<?php
	while($p = mysql_fetch_array($result)) {

echo <<<TBODY

	<tr id="{$p['id']}">
		<td>{$p['title']}</td>
		<td>{$p['author']}</td>
		<td>{$p['price']}</td>
		<td><button onclick="deleteData({$p['id']})">ลบ</td>
	</tr>
TBODY;

	} //end while
?>
</table>

<?php mysql_close($dblink); ?>

</body>
</html>