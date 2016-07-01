/*
 * doublylinkedlist.h
 *
 *  Created on: Jun 26, 2016
 *      Author: aherne
 */

#ifndef CLASSES_DOUBLYLINKEDLIST_H_
#define CLASSES_DOUBLYLINKEDLIST_H_



#include "../common.h"
#include "../libraries/data_structures_api/DoublyLinkedList.h"
#include "list_object.h"

PHP_METHOD(DoublyLinkedList, __construct);
PHP_METHOD(DoublyLinkedList, __destruct);
PHP_METHOD(DoublyLinkedList, addToTop);
PHP_METHOD(DoublyLinkedList, addToBottom);
PHP_METHOD(DoublyLinkedList, emplace);
PHP_METHOD(DoublyLinkedList, set);
PHP_METHOD(DoublyLinkedList, get);
PHP_METHOD(DoublyLinkedList, size);
PHP_METHOD(DoublyLinkedList, isEmpty);
PHP_METHOD(DoublyLinkedList, containsIndex);
PHP_METHOD(DoublyLinkedList, containsValue);
PHP_METHOD(DoublyLinkedList, removeIndex);
PHP_METHOD(DoublyLinkedList, removeValue);
PHP_METHOD(DoublyLinkedList, clear);
PHP_METHOD(DoublyLinkedList, toValue);

const char doublylinkedlist_class_name[] = "DoublyLinkedList";
const zend_function_entry doublylinkedlist_class_methods[] = {
    PHP_ME(DoublyLinkedList,  __construct,    	NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(DoublyLinkedList,  __destruct,     	NULL, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)
    PHP_ME(DoublyLinkedList,  addToTop,    	NULL, ZEND_ACC_PUBLIC)
    PHP_ME(DoublyLinkedList,  addToBottom,    	NULL, ZEND_ACC_PUBLIC)
    PHP_ME(DoublyLinkedList,  emplace,    		NULL, ZEND_ACC_PUBLIC)
    PHP_ME(DoublyLinkedList,  set,           	NULL, ZEND_ACC_PUBLIC)
    PHP_ME(DoublyLinkedList,  get,           	NULL, ZEND_ACC_PUBLIC)
    PHP_ME(DoublyLinkedList,  size,           	NULL, ZEND_ACC_PUBLIC)
    PHP_ME(DoublyLinkedList,  isEmpty,         NULL, ZEND_ACC_PUBLIC)
    PHP_ME(DoublyLinkedList,  containsIndex,   NULL, ZEND_ACC_PUBLIC)
    PHP_ME(DoublyLinkedList,  containsValue,   NULL, ZEND_ACC_PUBLIC)
    PHP_ME(DoublyLinkedList,  removeIndex,     NULL, ZEND_ACC_PUBLIC)
    PHP_ME(DoublyLinkedList,  removeValue,     NULL, ZEND_ACC_PUBLIC)
    PHP_ME(DoublyLinkedList,  clear,     		NULL, ZEND_ACC_PUBLIC)
    PHP_ME(DoublyLinkedList,  toValue,         NULL, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};



#endif /* CLASSES_DOUBLYLINKEDLIST_H_ */
