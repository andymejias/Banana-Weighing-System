<?php
class RestService {
	
	private $_callbacks;
	
	/**
	 * creates an instance of the REST Service handler
	 * @param associative array $callbacks
	 * 	an array of callbacks with keys named:
	 * 	'GET', 'POST', 'PUT', 'DELETE'	
	 */
	public function __construct($callbacks = array()){
		$this->_callbacks = $callbacks;
	}
	
	public function handle(){
		$method = isset($_SERVER['REQUEST_METHOD']) ? $_SERVER['REQUEST_METHOD'] : "POST";
		if(isset($this->_callbacks[$method])){
			$args = array();
			parse_str(file_get_contents("php://input"), $args);
			$params = array(
				"server_variables"=>$_SERVER,
				"args"=>$args
			);
			call_user_func_array($this->_callbacks[$method], $params);
		} else {
			throw new Exception("No handler for method '{$method}'");
		}
	}
	
}
