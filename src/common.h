/*
 * common.h
 *
 *  Created on: May 30, 2016
 *      Author: aherne
 */

#ifndef LIBRARIES_COMMON_H_
#define LIBRARIES_COMMON_H_

extern "C" {
	#include "php5/main/php.h"
	#include "php5/Zend/zend_API.h"
	#include "php5/Zend/zend_exceptions.h"
	#include "php5/Zend/zend_operators.h"
	#include "php5/Zend/zend_interfaces.h"
}

#include "libraries/MemoryManager.h"
#include "libraries/Conversions.h"

#define TYPE_MIXED 0
#define TYPE_LONG 1
#define TYPE_DOUBLE 2
#define TYPE_BOOLEAN 3
#define TYPE_STRING 4
#define TYPE_OBJECT 5

#define TYPE_MIXED_STRING "mixed"
#define TYPE_LONG_STRING_1 "int"
#define TYPE_LONG_STRING_2 "integer"
#define TYPE_DOUBLE_STRING_1 "double"
#define TYPE_DOUBLE_STRING_2 "float"
#define TYPE_BOOLEAN_STRING "boolean"
#define TYPE_STRING_STRING "string"

static inline bool destroyIterator(const char& type) {
	if(type==TYPE_MIXED || type==TYPE_OBJECT) return false;
	else return true;
}

static inline char getDataType(zval*& type) {
	if(Z_TYPE_P(type)!=IS_STRING) throw std::runtime_error("Value must be string!");
	if(strcasecmp(Z_STRVAL_P(type),TYPE_STRING_STRING)==0) {
		return TYPE_STRING;
	} else if(strcasecmp(Z_STRVAL_P(type),TYPE_LONG_STRING_1) ==0 || strcasecmp(Z_STRVAL_P(type),TYPE_LONG_STRING_2)==0) {
		return TYPE_LONG;
	} else if(strcasecmp(Z_STRVAL_P(type),TYPE_DOUBLE_STRING_1) ==0 || strcasecmp(Z_STRVAL_P(type),TYPE_DOUBLE_STRING_2)==0) {
		return TYPE_DOUBLE;
	} else if(strcasecmp(Z_STRVAL_P(type),TYPE_BOOLEAN_STRING)==0) {
		return TYPE_BOOLEAN;
	} else if(strcasecmp(Z_STRVAL_P(type),TYPE_MIXED_STRING)==0) {
		return TYPE_MIXED;
	} else {
		zend_class_entry **ce;
		if(zend_lookup_class(Z_STRVAL_P(type), Z_STRLEN_P(type), &ce TSRMLS_CC) == SUCCESS){
			return TYPE_OBJECT;
		} else {
			char result[100]= "Class not found: ";
			strcat(result,Z_STRVAL_P(type));
			throw std::runtime_error(result);
		}
	}
}

#endif /* LIBRARIES_COMMON_H_ */
