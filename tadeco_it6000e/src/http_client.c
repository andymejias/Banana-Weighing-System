/*
 * http_client.c
 *
 * http client for it6000e systec weighing scale
 *
 *  Created on: Sep 27, 2011
 *      Author: ferd
 */

bool http_client_valid_ip(string ip){
	int i;
	i = cssub(ip, '.', 0);

	return (true);
}

/**
 * Does a http post to a web server
 *
 */
void http_client_post(int channel, string target_ip, string target_port, string path, string host_header, string post_data){
      string s[255];
      int ret;
      ret = popen(channel, concat(target_ip, ":", target_port));
      if(ret == PORT_OPT_SUCCESS){
				s = concat("POST http://", host_header, "/", path, " HTTP/1.1", "\n");
        ret = pwritestring(channel, s, length(s));
        
				s = concat("HOST: ", host_header, "\n");
        ret = pwritestring(channel, s, length(s));
        
				s = concat("Content-Type: application/x-form-urlencoded\n");
        ret = pwritestring(channel, s, length(s));
        
				s = concat("Content-Length: ", length(post_data), "\n");
        ret = pwritestring(channel, s, length(s));
        
        s = "\n";
        ret = pwritestring(channel, s, length(s));
        
        s = concat(post_data, "\n");
        ret = pwritestring(channel, s, length(s));
        
        s = "\n";
        ret = pwritestring(channel, s, length(s));
        
//        ret = pwritestring(channel, s, length(s));
        pclose(channel);
			}
}
