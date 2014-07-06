<?php
error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);

//$json = "{\"param1\":\"value1\",\"param2\":\"value2\"}";
$json = "{\"fm\":\" 30\",\"bk\":\"30A\",\"pc\":\" 88\",\"wk\":\"  7\",\"wr\":\" 51.0\",\"cc\":\"11\",\"dt\":\"2011-10-08 14:35\"}";
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
