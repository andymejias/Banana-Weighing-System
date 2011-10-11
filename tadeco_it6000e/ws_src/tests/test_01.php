<?php
error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);


$json = "{\"fm\":\"999\",\"bk\":\"999\",\"pc\":\"99\",\"wk\":\"99\",\"wr\":\"99999\",\"cc\":\"999\",\"dt\":\"10/07/2011 10:10\"}";
?>
<DOCTYPE html>
<html>
<head>
	<title>Test 01</title>
</head>
<body>
	<div class="messages">
	</div>
	<form name="form" method="post" action="http://tadecows.local/record/add">
		<fieldset>
			<legend>test 01</legend>
			<input id="hidden" name="log" type="hidden" value="<?php print(htmlentities($json));?>" />
		</fieldset>
		<input id="submit" name="submit" type="submit" value="Test" />
	</form>
</body>
</html>
