/*
 * arraylist_boolean.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: aherne
 */

#ifndef SRC_PHP_OBJECTS_ARRAYLIST_H_
#define SRC_PHP_OBJECTS_ARRAYLIST_H_


#include "../common.h"
#include "../libraries/data_structures_api/ArrayList.h"
#include "list_object.h"

PHP_METHOD(ArrayList, __construct);
PHP_METHOD(ArrayList, __destruct);
PHP_METHOD(ArrayList, addToTop);
PHP_METHOD(ArrayList, addToBottom);
PHP_METHOD(ArrayList, emplace);
PHP_METHOD(ArrayList, set);
PHP_METHOD(ArrayList, get);
PHP_METHOD(ArrayList, size);
PHP_METHOD(ArrayList, isEmpty);
PHP_METHOD(ArrayList, containsIndex);
PHP_METHOD(ArrayList, containsValue);
PHP_METHOD(ArrayList, removeIndex);
PHP_METHOD(ArrayList, removeValue);
PHP_METHOD(ArrayList, clear);
PHP_METHOD(ArrayList, toValue);

const char arraylist_class_name[] = "ArrayList";
const zend_function_entry arraylist_class_methods[] = {
    PHP_ME(ArrayList,  __construct,    	NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(ArrayList,  __destruct,     	NULL, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)
    PHP_ME(ArrayList,  addToTop,    	NULL, ZEND_ACC_PUBLIC)
    PHP_ME(ArrayList,  addToBottom,    	NULL, ZEND_ACC_PUBLIC)
    PHP_ME(ArrayList,  emplace,    		NULL, ZEND_ACC_PUBLIC)
    PHP_ME(ArrayList,  set,           	NULL, ZEND_ACC_PUBLIC)
    PHP_ME(ArrayList,  get,           	NULL, ZEND_ACC_PUBLIC)
    PHP_ME(ArrayList,  size,           	NULL, ZEND_ACC_PUBLIC)
    PHP_ME(ArrayList,  isEmpty,         NULL, ZEND_ACC_PUBLIC)
    PHP_ME(ArrayList,  containsIndex,   NULL, ZEND_ACC_PUBLIC)
    PHP_ME(ArrayList,  containsValue,   NULL, ZEND_ACC_PUBLIC)
    PHP_ME(ArrayList,  removeIndex,     NULL, ZEND_ACC_PUBLIC)
    PHP_ME(ArrayList,  removeValue,     NULL, ZEND_ACC_PUBLIC)
    PHP_ME(ArrayList,  clear,     		NULL, ZEND_ACC_PUBLIC)
    PHP_ME(ArrayList,  toValue,         NULL, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

#endif /* SRC_PHP_OBJECTS_ARRAYLIST_CPP_ */
