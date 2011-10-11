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
	$data = json_decode($args["log"]);
		
	
	try {
		$db = Db::get_instance();

		$db->log_request(array(
			"server_variables"=>$server_variables,
			"arguments"=>$args
		));
		
		

		$farm_id = $data->fm;
		$parcel_id = $data->pc;
		$lot_id = $data->bk;
		$gang_id = $data->cc;
		$ribbon_id = $data->wk;
		$weigh_date = $data->dt; //date("MM/dd/yyyy");
		$weight = $data->wr;
		
		$db->log_data(
			$farm_id,
			$parcel_id,
			$lot_id,
			$gang_id,
			$ribbon_id,
			$weigh_date,
			$weight
		);
		
		header("HTTP/1.0 200 OK");
		exit();
		
	} catch(Exception $e){
		die("<pre>".print_r($e, true)."</pre>");
	}
}
