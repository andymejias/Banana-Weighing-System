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
		$path = $_SERVER["REQUEST_URI"];
		$path = str_replace("http://", "", $path);
		$path = str_replace($_SERVER["SERVER_NAME"], "", $path);
		$path = trim($path, "/");
		if(isset($this->_callbacks[$path])){
			$callback = $this->_callbacks[$path];
			if($callback["method"] == $_SERVER["REQUEST_METHOD"]){
				$function = $callback["callback"];
				$args = array();
				parse_str(file_get_contents("php://input"), $args);
				$params = array(
					"server_variables"=>$_SERVER,
					"args"=>$args
				);
				call_user_func_array($function, $params);
			} else {
				// throw 404 not found
				throw new Exception("Path not found: {$path}");
			}
		} else {
			// throw 404 not found
			throw new Exception("Path not found: {$path}");
		}
		
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
