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
		
		$data = json_decode($args["post_data"]);

		$farm_id = $data["farm_id"];
		$parcel_id = $data["parcel_id"];
		$lot_id = $data["lot_id"];
		$gang_id = $data["gang_id"];
		$ribbon_id = $data["ribbon_id"];
		$age = $data["age"];
		$weigh_date = $data["weigh_date"]; //date("MM/dd/yyyy");
		$weight = $data["weight"];
		
		$db->log_data(
			$farm_id,
			$parcel_id,
			$lot_id,
			$gang_id,
			$ribbon_id,
			$age,
			$weigh_date,
			$weight
		);
		
		header("HTTP/1.0 200 OK");
		exit();
		
	} catch(Exception $e){
		die("<pre>".print_r($e, true)."</pre>");
	}
}
