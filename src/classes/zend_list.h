/*
 * ArrayListZendClass.h
 *
 *  Created on: Nov 12, 2015
 *      Author: aherne
 */

#ifndef SRC_ZEND_CLASSES_MIXEDLISTZENDCLASS_H_
#define SRC_ZEND_CLASSES_MIXEDLISTZENDCLASS_H_

#include "../common.h"
#include "list_object.h"
#include "list_object_iterator.h"
#include "zend_list_iterator.h"
#include "zend_list_handlers.h"

class ListZendClass {
public:
	ListZendClass(const char name[], const zend_function_entry methods[]);
	~ListZendClass();
	zend_class_entry* getClassEntry();
	void implements(zend_class_entry*);
private:
	zend_class_entry *class_ce;

	// helpers for object creation
	static zend_object_value create_object(zend_class_entry*);
	static void free_object(void*);

	// object handler helpers
	static zend_object_handlers class_object_handlers;
};

#endif /* SRC_ZEND_CLASSES_MIXEDLISTZENDCLASS_H_ */
