<?php


include("iplist.php");
include("settings.php");
include("classes/service.class.inc");
include("classes/db.class.inc");

$callbacks = array(
	"POST"=>"do_post"
);

$service = new RestService($callbacks);
$service->handle();

function do_post($server_variables = array(), $args = array()){
	$json = json_decode($args["log"]);
	
	Db = new Db();
	
	print("<pre>".print_r($server_variables, true)."</pre>");
	print("<pre>".print_r($args, true)."</pre>");
	print("<pre>");
	var_dump($json);
	print("</pre>");
	die("do_post");
}