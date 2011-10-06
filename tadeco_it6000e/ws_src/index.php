<?php
error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);

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
	
	try {
		$db = Db::get_instance();

		$db->log_request(array(
			"server_variables"=>$server_variables,
			"arguments"=>$args
		));
		
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
		
		die("ok");
		
	} catch(Exception $e){
		die("<pre>".print_r($e, true)."</pre>");
	}
}