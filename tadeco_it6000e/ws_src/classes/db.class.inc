<?php

define("LOG_DATA",1);
define("LOG_EXCEPTION",2);

/**
 * Database class
 * @author ferd
 * @created 10/4/2011
 */
class Db {

	private static $_instance = null;
	private $_cn = null;
	
	private function __construct(){
		// DB_URL should have been defined in settings.php
		if(defined("DB_URL")){
			$url = parse_url(DB_URL);
			$db_name = str_replace("/", "", $url["path"]);
			$this->_cn = new PDO(
				"{$url["scheme"]}:host={$url["host"]};dbname={$db_name}", 
				$url["user"],
				$url["pass"],
				array()
			);
		} else {
			throw new Exception("DB_URL has not been defined");
		}
	}
	
	public static function get_instance(){
		if(!isset(self::$_instance)){
			self::$_instance = new Db();
		}
		return self::$_instance;
	}
	
	public function log_request($request_data = array()){
		$sql = <<<SQL
insert into log (type_id, created, entry) values
(:type_id, now(), :entry)
SQL;
		$stmt = $this->_cn->prepare($sql);
		if($stmt){
			$log_type = LOG_DATA;
			$stmt->bindParam(":type_id", $log_type, PDO::PARAM_INT);
			$stmt->bindParam(":entry", print_r($request_data, true), PDO::PARAM_STR, 4000);
			if(!$stmt->execute()){
				$err = print_r($stmt->errorInfo(), true);
				throw new Exception("Unable to execute log statement object: {$err}");
			}
		} else {
			$err = print_r($this->_cn->errorInfo(), true);
			throw new Exception("Unable to prepare log statement object: {$err}");
		}
		
	}

	public function log_exception($exception){
		$sql = <<<SQL
insert into log (type_id, created, entry) values
(:type_id, now(), :entry)
SQL;
		$stmt = $this->_cn->prepare($sql);
		if($stmt){
			$log_type = LOG_EXCEPTION;
			$stmt->bindParam(":type_id", $log_type, PDO::PARAM_INT);
				$stmt->bindParam(":entry", print_r($exception, true), PDO::PARAM_STR, 4000);
			if(!$stmt->execute()){
				$err = print_r($stmt->errorInfo(), true);
				throw new Exception("Unable to execute log statement object: {$err}");
			}
		} else {
			$err = print_r($this->_cn->errorInfo(), true);
			throw new Exception("Unable to prepare log statement object: {$err}");
		}
	}
	
	public function log_data(
		$machine_id,
		$record_id,
		$farm_id, 
		$parcel_id, 
		$lot_id, 
		$gang_id, 
		$ribbon_id,		
		$weigh_date, 
		$weight
		){
		$sql = <<<SQL
insert into records (created, machine_id, record_id, farm_id, parcel_id, lot_id, gang_id, ribbon_id, weigh_date, weight) values 
(now(), :machine_id, :record_id, :farm_id, :parcel_id, :lot_id, :gang_id, :ribbon_id, :weigh_date, :weight)
SQL;
		$stmt = $this->_cn->prepare($sql);
		if($stmt){
			$stmt->bindParam(":machine_id", $machine_id, PDO::PARAM_STR);
			$stmt->bindParam(":record_id", $record_id, PDO::PARAM_INT);
			$stmt->bindParam(":farm_id", $farm_id, PDO::PARAM_INT);
			$stmt->bindParam(":parcel_id", $parcel_id, PDO::PARAM_INT);
			$stmt->bindParam(":lot_id", $lot_id, PDO::PARAM_INT);
			$stmt->bindParam(":gang_id", $gang_id, PDO::PARAM_INT);
			$stmt->bindParam(":ribbon_id", $ribbon_id, PDO::PARAM_INT);
			$stmt->bindParam(":weigh_date", $weigh_date, PDO::PARAM_STR);
			$stmt->bindParam(":weight", $weight);
			if(!$stmt->execute()){
				$err = print_r($stmt->errorInfo(), true);
				throw new Exception("Unable to execute log data statement object. {$err}");
			}
		} else {
			$err = print_r($this->_cn->errorInfo(), true);
			throw new Exception("Unable to prepare log data statement object: {$err}");
		}
	}
	
	public function log_data_update(
		$machine_id,
		$record_id,
		$farm_id,
		$parcel_id,
		$lot_id,
		$gang_id,
		$ribbon_id
	){
		$sql = <<<SQL
update records set
farm_id = :farm_id,
parcel_id = :parcel_id,
lot_id = :lot_id,
gang_id = :gang_id,
ribbon_id = :ribbon_id
where machine_id = :machine_id
and record_id = :record_id
SQL;
		$stmt = $this->_cn->prepare($sql);
		if($stmt){
			$stmt->bindParam(":machine_id", $machine_id, PDO::PARAM_STR);
			$stmt->bindParam(":record_id", $record_id, PDO::PARAM_INT);
			$stmt->bindParam(":farm_id", $farm_id, PDO::PARAM_INT);
			$stmt->bindParam(":parcel_id", $parcel_id, PDO::PARAM_INT);
			$stmt->bindParam(":lot_id", $lot_id, PDO::PARAM_INT);
			$stmt->bindParam(":gang_id", $gang_id, PDO::PARAM_INT);
			$stmt->bindParam(":ribbon_id", $ribbon_id, PDO::PARAM_INT);
			if(!$stmt->execute()){
				$err = print_r($stmt->errorInfo(), true);
				throw new Exception("Unable to execute log data statement object. {$err}");
			}
		} else {
			$err = print_r($this->_cn->errorInfo(), true);
			throw new Exception("Unable to prepare log data update statement object: {$err}");	
		}
	}
	
	public function log_sampling(
		$machine_id,
		$record_id,
		$bc,
		$fl,
		$nh,
		$fc,
		$hc
	){
		$sql = <<<SQL
insert into sampling (created, machine_id, record_id, bc, fl, nc, fc, hc
values (now(), :machine_id, :record_id, :bc, :fl, :nc, :fc, :hc)
SQL;
		$stmt = $this->_cn->prepare($sql);
		if($stmt){
			$stmt->bindParam(":machine_id", $machine_id, PDO::PARAM_INT);
			$stmt->bindParam(":record_id", $record_id, PDO::PARAM_INT);
			$stmt->bindParam(":bc", $bc);
			$stmt->bindParam(":fl", $fl);
			$stmt->bindParam(":nh", $nh);
			$stmt->bindParam(":fc", $fc);
			$stmt->bindParam(":hc", $hc);
			if(!$stmt->execute()){
				$err = print_r($stmt->errorInfo(), true);
				throw new Exception("Unable to execute log sampling statement object. {$err}");
			}
		} else {
			$err = print_r($this->_cn->errorInfo(), true);
			throw new Exception("Unable to prepare log sampling statement object: {$err}");	
		}
	}
	
}
