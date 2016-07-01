#ifndef PHP_DATA_TYPES_API_H
#define PHP_DATA_TYPES_API_H

#define PHP_DATA_TYPES_API_EXTNAME  "data_types_api"
#define PHP_DATA_TYPES_API_EXTVER   "0.1"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

extern "C" {
	#include "/usr/include/php5/main/php.h"
	#include "/usr/include/php5/Zend/zend_API.h"
	#include "/usr/include/php5/Zend/zend_exceptions.h"
	#include "/usr/include/php5/Zend/zend_interfaces.h"
}

extern zend_module_entry data_types_api_module_entry;
#define phpext_data_types_api_ptr &data_types_api_module_entry;

#endif /* PHP_DATA_TYPES_API_H */
