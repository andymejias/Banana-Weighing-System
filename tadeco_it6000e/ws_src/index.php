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
	"record/update"=>array(
		"method"=>"POST",
		"callback"=>"tadeco_record_update"
	),
	"sampling/add"=>array(
		"method"=>"POST",
		"callback"=>"tadeco_sampling_add"
	)
);

try {
	$service = new RestService($callbacks);
	$service->handle();
} catch(Exception $e){
	$db = Db::get_instance();
	if($db){
		$db->log_exception($e);
	}
}

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
		$weigh_date = $data->dt; //date("MM/dd/yyyy");
		$weight = $data->wr;
		
		$db->log_data(
			$machine_id,
			$record_id,
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
		throw $e;
	}
}

function tadeco_record_update($server_variables = array(), $args = array()){
	try {
		$db = Db::get_instance();
		$db->log_request(array(
			"server_variables"=>$server_variables,
			"arguments"=>$args
		));
		
		if(isset($args["log"])){
			$data = json_decode($args["log"]);
			
			$machine_id = $data->machine_id;
			$record_id = $data->record_id;
			$farm_id = $data->farm_id;
			$parcel_id = $data->parcel_id;
			$lot_id = $data->lot_id;
			$gang_id = $data->gang_id;
			$ribbon_id = $ribbon_id;
			
			$db->log_data_update(
				$machine_id,
				$record_id,
				$farm_id,
				$parcel_id,
				$lot_id,
				$gang_id,
				$ribbon_id
			);
			
			header("HTTP/1.0 200 OK");
			print("ok");
			exit();
			
		} else {
			throw new Exception("Log data not found");
		}
	}catch(Exception $e){
		throw $e;
	}
}

function tadeco_sampling_add($server_variables = array(), $args = array()){
	try {
		$db = Db::get_instance();
		$db->log_request(array(
			"server_variables"=>$server_variables,
			"arguments"=>$args
		));
		if(isset($args["log"])){
			$data = json_decode($args["log"]);
			
			$machine_id = $data->machine_id;
			$record_id = $data->record_id;
			$bc = $data->bc;
			$fl = $data->fl;
			$nh = $data->nh;
			$fc = $data->fc;
			$hc = $data->hc;
			
			$db->log_sampling(
				$machine_id,
				$record_id,
				$bc,
				$fl,
				$nh,
				$fc,
				$hc
			);
			
			header("HTTP/1.0 200 OK");
			print("ok");
			exit();
		} else {
			throw new Exception("Log sampling data not found");
		}
	}catch(Exception $e){
		throw $e;
	}
}
