<?php
error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);

include("../settings.php");
include("../classes/db.class.inc");

try {
	$db = Db::get_instance();
	print("db");
	print("<pre>".print_r($db, true)."</pre>");
	
	$args = array(
		"server_variables"=>$_SERVER
	);
	$db->log_request($args);
	print("args");
	print("<pre>".print_r($args, true)."</pre>");
	
	$farm_id = 0;
	$parcel_id = 0;
	$lot_id = 0;
	$gang_id = 0;
	$ribbon_id = 0;
	$weigh_date = date("MM/dd/yyyy");
	$weight = 0;
	
	$db->log_data(
		$farm_id,
		$parcel_id,
		$lot_id,
		$gang_id,
		$ribbon_id,
		$weigh_date,
		$weight
	);
	
	print("done");
	
} catch(Exception $e){
	print("</pre>");
	var_dump($e);
	print("</pre>");
}