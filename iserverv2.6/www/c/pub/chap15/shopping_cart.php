<html>
<head>
<style> body, td, th, div, span, a, button, input, textarea {font:10pt tahoma;}
	.bt_add_cart{font:bold 8pt;color:blue;}
	.dv_add_cart{padding:2px;text-align:right;border-top:dashed 1px orange;}
	.bt_cart{font:8pt; border:solid 1px gray;}
	.pd_title{font:bold 11pt;color:navy;padding:3px;background-color:#ddffdd;}
	.tx_qul{width:30px;margin:2px;}
	.td_img {padding:3px;}
</style>
<script src="/ajaxbook/ajax_framework.js"> </script>
<script>
function addCart(pid) {
	var q = document.getElementById('q_' + pid).value;
	var data = "act=add&pid=" + pid + "&q=" + q;
	var URL = "cart_ss.php";

	ajaxLoad('post', URL, data, "cart");
}
function delCart(pid) {
	if(!confirm('ลบสินค้านี้ ?')) {
		return;
	}
	var data = "act=del&pid=" + pid;
	var URL = "cart_ss.php";

	ajaxLoad('post', URL, data, "cart");
}
function clearCart() {
	if(!confirm('ลบทั้งหมด ?')) {
		return;
	}
	var data = "act=clear&pid=";
	var URL = "cart_ss.php";

	ajaxLoad('post', URL, data, "cart");
}
</script>
</head>
<body>
<h2>Ajax Shopping Cart</h2>
<?php
	$dblink = mysql_connect("localhost","root","123");
	mysql_query("USE shopping_cart;");

	$result = mysql_query("SELECT * FROM product;");
?>
<table width="800">
<tr valign="top">
<td width="500">
<div style="width:100%; height:500px;">
<table width="100%" border="0" bordercolor="gray" style="border-colllapse:collapse;">
<?php
	while($p = mysql_fetch_array($result)) {
?>
<tr valign="top">
	<td width="100" align="center">
		<img src="read_image.php?pid=<?php echo $p['pid']; ?>">
	</td>
	<td>
		<div class="pd_title"><?php echo $p['product_name']; ?></div>
		<?php echo $p['description']; ?>
		<p>
		ราคา: <?php echo $p['price']; ?> บาท
		<div class="dv_add_cart">
			<button onclick="addCart(<?php echo $p['pid']; ?>)" class="bt_add_cart">หยิบใส่รถเข็น</button>
			จำนวน<input type="text" 
 				id="<?php echo "q_{$p['pid']}"; ?>" 
				value="1" class="tx_qul">หน่วย
		</div>
	</td>
</tr>
<tr><td colspan="2"><hr noshade size="1" color="green"></td></tr>
<?php
	}
?>
</table>
</td>
<td id="cart" align="center" bgcolor="#eeeeff">&nbsp;
<script> ajaxLoad('post','cart_ss.php','','cart'); </script>
</div>
</td>
</tr>
</table>
</body>
</html>

<?php	mysql_close($dblink);	?>

