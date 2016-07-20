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
	char key_type;
	char value_type;
	void* object;
	MemoryManager<char*>* memory_manager;
    char* class_name;
};



#endif /* CLASSES_MAP_OBJECT_H_ */
