/*
 * map_object.h
 *
 *  Created on: Jul 10, 2016
 *      Author: aherne
 */

#ifndef CLASSES_MAP_OBJECT_H_
#define CLASSES_MAP_OBJECT_H_

#include "../libraries/data_structures_api/Map.h"

struct map_object {
    zend_object std;
	char type_key;
	char type_value;
	void* object;

	MemoryManager<char*>* memory_manager;	// specific to map_object<char*>.
    zend_class_entry* class_entry_key;			// specific to map_object<zval*> where zval is of zend_class_entry type
    zend_class_entry* class_entry_value;			// specific to map_object<zval*> where zval is of zend_class_entry type
};



#endif /* CLASSES_MAP_OBJECT_H_ */
