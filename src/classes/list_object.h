/*
 * list_object.h
 *
 *  Created on: Jun 25, 2016
 *      Author: aherne
 */

#ifndef CLASSES_LIST_OBJECT_H_
#define CLASSES_LIST_OBJECT_H_

#include "../libraries/data_structures_api/List.h"

struct list_object {
    zend_object std;
	char type;
	void* object;							// since we expose a generic-based structure to a C api, void* is a must (unless we want separate classes for each type @ PHP)

	MemoryManager<char*>* memory_manager;	// specific to list_object<char*>.
    char* class_name;						// specific to list_object<zval*> where zval is of zend_class_entry type
};


#endif /* CLASSES_LIST_OBJECT_H_ */
