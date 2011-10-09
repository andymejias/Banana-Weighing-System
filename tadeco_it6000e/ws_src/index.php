<?php
error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);

include("iplist.php");
include("settings.php");
include("classes/service.class.inc");
include("classes/db.class.inc");

$callbacks = array(
	"record/add"=>array(
		"method"=>"POST",
		"callback"=>"tadeco_record_add"
	),
	"record_update"=>array(
		"method"=>"POST",
		"callback"=>"tadeco_record_update"
	)
);

$service = new RestService($callbacks);
$service->handle();

function tadeco_record_add($server_variables = array(), $args = array()){
	$data = json_decode($args["log"]);
	
	try {
		$db = Db::get_instance();

		$db->log_request(array(
			"server_variables"=>$server_variables,
			"arguments"=>$args
		));

		$machine_id = "todo"; 	// TODO should use correct machine id
		$record_id = 1;			// TODO should use correct record id
		$farm_id = $data->fm;
		$parcel_id = $data->pc;
		$lot_id = $data->bk;
		$gang_id = $data->cc;
		$ribbon_id = $data->wk;
		$age = $data->wk;
		$weigh_date = $data->dt;
		$weight = $data->wr;
		
		$db->log_data(
			$machine_id,
			$record_id,
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
		print("ok");
		exit();
		
	} catch(Exception $e){
		die("<pre>".print_r($e, true)."</pre>");
	}
}

function tadeco_record_update($server_variables = array(), $args = array()){
	throw new Exception("TODO");
}
