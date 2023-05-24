<?php
	session_start();
?>
<html>
<head>
<title><?php echo $_SESSION['nickname']; ?></title>
<style>	
	body, td {
 		font:10pt tahoma
	}
	.iframe_title {
		background-color:green;
		color:white; 
		padding:3px;
	}
	
</style>

<script src="/ajaxbook/ajax_framework.js"></script>

<script>
function ajaxSubmit() {
	var data = getFormData("frm");
	var URL = "add_msg_ss.php";
	ajaxLoad('post', URL, data, 'info');

	document.getElementById('msg').value = "";	
}
function exitChat() {
	if(!confirm('�͡�ҡ��ͧʹ��� ?')) {
		return;
	}
	var data = getFormData("frm");
	var URL = "exit_chatroom_ss.php";
	ajaxLoad('post', URL, data, 'info');
}
function isPressEnter() {
	if(event.keyCode==13) {
		ajaxSubmit();
		return false;
	}
}
</script>
</head>

<body>
<h1>Ajax Live Chat</h1>
<p>
<table>
<tr valign="top">
<td width="550">
<div class="iframe_title">��ͧʹ���</div>
<iframe src="show_msg.html" width="550" height="300" scrolling="yes"></iframe>
</td>
<td>
<div class="iframe_title">�������ʹ���</div>
<iframe src="show_chatter.html" width="200" height="300" scrolling="yes"></iframe>
</td>
</tr>
<tr valign="top">
<td>

<form name="frm">
<input type="hidden" name="nickname" 
	value="<?php echo $_SESSION['nickname']; ?>"
>
��ͤ���:
<input type="text" id="msg" name="msg" size="55" maxlength="250"
	style="background-color:#ffffcc;"
	onkeypress="return isPressEnter()"
>
<button onclick="ajaxSubmit()">Go</button> ���� &lt;Enter&gt;
<br>
�բ�ͤ���:
<input type="radio" name="color" value="black" checked>��
<input type="radio" name="color" value="red">ᴧ
<input type="radio" name="color" value="blue">����Թ
<input type="radio" name="color" value="green">����
<input type="radio" name="color" value="orange">���
</form>

</td>
<td align="right">

<button onclick="exitChat()">�͡�ҡ��ͧʹ���</button>

</td>
</tr>
</table>
<div id="info"></div>
</body>
</html>

