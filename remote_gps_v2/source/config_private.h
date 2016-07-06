/*
 * config_private.h
 *
 *  Created on: Jul 6, 2016
 *      Author: Visakhan
 */

#ifndef SOURCE_CONFIG_PRIVATE_H_
#define SOURCE_CONFIG_PRIVATE_H_

/* Replace this with your mobile number which will be used to communicate with GSM module
 * Call/massage from this number only will be accepted */
#define AUTH_CALLER	"+1234567890"

/* Replace this will URL used to save location samples at the server */
#define LOG_API_URL	"example.com/myscript.php?"

/* Defines API used for reverse geolocation */
#define MAPS_API_URL "http://maps.googleapis.com/maps/api/geocode/json?latlng="

#endif /* SOURCE_CONFIG_PRIVATE_H_ */
