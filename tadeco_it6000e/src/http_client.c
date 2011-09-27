/*
 * http_client.c
 *
 * http client for it6000e systec weighing scale
 *
 *  Created on: Sep 27, 2011
 *      Author: ferd
 */


/**
 * Does a http post to a web server
 *
 */
int http_client_post(string target_ip, int target_port, string path, string host_header, string post_data){
	if(port > PORT_INTERNAL_2100 && port != PORT_INTERNAL_6000){
		if(http_client_valid_ip(target_ip)){
			if(popen(PORT_ETH0, concat(target_ip, ":", target_port) == PORT_OPT_SUCCESS)){
				string s[1000];
				s = concat("POST ", target_ip, ":", target_port, "/", path, "HTTP 1.1", "\n");
				s = concat(s, "HOST:", host_header, "\n");
				s = concat(s, "Content-Type: application/x-form-urlencoded\n");
				s = concat(s, "Content-Length: ", length(post_data), "\n");
				s = concat(s, post_data);
				return pwritestring(PORT_ETH0, s, length(s));
			} else {
				return HTTP_CLIENT_ERR_OPEN;
			}
		} else {
			return HTTP_CLIENT_ERR_BAD_IP;
		}
	} else {
		return HTTP_CLIENT_ERR_OPEN;
	}
}

bool http_client_valid_ip(string ip){
	int i;
	i = cssub(ip, '.', 0);

	return true;
}
