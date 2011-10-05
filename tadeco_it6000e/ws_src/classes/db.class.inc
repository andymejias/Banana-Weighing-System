<?php

define("LOG_DATA",1);

/**
 * Database class
 * @author ferd
 * @created 10/4/2011
 */
class Db {
	
	private static $_cn = null;
	
	private function __construct(){
		
	}
	
	public static function get_instance(){
		if(!isset(self::$_cn)){
			// DB_URL should have been defined in settings.php
			if(defined(DB_URL)){
				$url = parse_url(DB_URL);
				self::$_cn = new PDO(
					"{$url["scheme"]}:host={$url["host"]};dbname={$url["path"]}", 
					$url["user"], 
					$url["pass"], 
					array()
				);
			} else {
				throw new Exception("DB_URL has not been defined");
			}
		}
		return self::$_cn;
	}
	
	public function log_request($request_data){
		
		$sql = <<<SQL
insert into log (type_id, created, entry) values
(:type_id, now(), :entry)
SQL;
		$stmt = $this->_cn->prepare($sql);
		if($stmt){
			$stmt->bindParam(":type_id", LOG_DATA, PDO::PARAM_INT);
			$stmt->bindParam(":entry", print_r($request_data, true), PDO::PARAM_STR);
			if(!$stmt->execute()){
				$err = print_r($this->_cn->errorInfo(), true);
				throw new Exception("Unable to execute log statement object: {$err}");
			}
		} else {
			$err = print_r($this->_cn->errorInfo(), true);
			throw new Exception("Unable to prepare log statement object: {$err}");
		}
		
	}
	
	public function log_data($data){
		
	}
	
}