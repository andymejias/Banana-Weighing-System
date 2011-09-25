/*
 * csv.h
 * requires it6000e.h
 *
 *  Created on: Sep 25, 2011
 *      Author: ferd
 */

#ifndef CSV_H_
#define CSV_H_

#include "it6000e.h"

#define CSV_OPEN_ERROR 0

/**
 * Opens a csv file for writing
 * and writes the header
 * Returns: CSV_OPEN_ERROR
 */
int csv_open(int handle, string name, string headers){
	if(handle => FILE_HANDLE_MIN && handle <= FILE_HANDLE_MAX){
		if(fopen(handle, name) == FOPEN_SUCCESS){
			if(fwrite(handle, headers, len(headers)) == 0){
				return CSV_OPEN_ERROR;
			}
		}
	}
}

int csv_write(int handle, string data){
	return fwrite(handle, data, len(data)) != 0;
}

#endif /* CSV_H_ */
