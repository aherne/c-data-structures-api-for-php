/*
 * linkedlist.h
 *
 *  Created on: Jun 26, 2016
 *      Author: aherne
 */

#ifndef CLASSES_LINKEDLIST_H_
#define CLASSES_LINKEDLIST_H_


#include "../common.h"
#include "../libraries/data_structures_api/LinkedList.h"
#include "list_object.h"

PHP_METHOD(LinkedList, __construct);
PHP_METHOD(LinkedList, __destruct);
PHP_METHOD(LinkedList, addToTop);
PHP_METHOD(LinkedList, addToBottom);
PHP_METHOD(LinkedList, emplace);
PHP_METHOD(LinkedList, set);
PHP_METHOD(LinkedList, get);
PHP_METHOD(LinkedList, size);
PHP_METHOD(LinkedList, isEmpty);
PHP_METHOD(LinkedList, containsIndex);
PHP_METHOD(LinkedList, containsValue);
PHP_METHOD(LinkedList, removeIndex);
PHP_METHOD(LinkedList, removeValue);
PHP_METHOD(LinkedList, clear);
PHP_METHOD(LinkedList, toValue);

const char linkedlist_class_name[] = "LinkedList";
const zend_function_entry linkedlist_class_methods[] = {
    PHP_ME(LinkedList,  __construct,    	NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(LinkedList,  __destruct,     	NULL, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)
    PHP_ME(LinkedList,  addToTop,    	NULL, ZEND_ACC_PUBLIC)
    PHP_ME(LinkedList,  addToBottom,    	NULL, ZEND_ACC_PUBLIC)
    PHP_ME(LinkedList,  emplace,    		NULL, ZEND_ACC_PUBLIC)
    PHP_ME(LinkedList,  set,           	NULL, ZEND_ACC_PUBLIC)
    PHP_ME(LinkedList,  get,           	NULL, ZEND_ACC_PUBLIC)
    PHP_ME(LinkedList,  size,           	NULL, ZEND_ACC_PUBLIC)
    PHP_ME(LinkedList,  isEmpty,         NULL, ZEND_ACC_PUBLIC)
    PHP_ME(LinkedList,  containsIndex,   NULL, ZEND_ACC_PUBLIC)
    PHP_ME(LinkedList,  containsValue,   NULL, ZEND_ACC_PUBLIC)
    PHP_ME(LinkedList,  removeIndex,     NULL, ZEND_ACC_PUBLIC)
    PHP_ME(LinkedList,  removeValue,     NULL, ZEND_ACC_PUBLIC)
    PHP_ME(LinkedList,  clear,     		NULL, ZEND_ACC_PUBLIC)
    PHP_ME(LinkedList,  toValue,         NULL, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};



#endif /* CLASSES_LINKEDLIST_H_ */
