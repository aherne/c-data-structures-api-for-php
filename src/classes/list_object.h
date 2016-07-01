/*
 * list_object.h
 *
 *  Created on: Jun 25, 2016
 *      Author: aherne
 */

#ifndef CLASSES_LIST_OBJECT_H_
#define CLASSES_LIST_OBJECT_H_

#include "../libraries/data_structures_api/List.h"

struct list_union {
	List<char>* object_boolean;
	List<double>* object_double;
	List<long>* object_long;
	List<char*>* object_string;
	List<zval*>* object_zval;

	list_union(){
		object_boolean = nullptr;
		object_double = nullptr;
		object_long = nullptr;
		object_string = nullptr;
		object_zval = nullptr;
	}

	~list_union() {
		if(object_boolean!=nullptr) delete object_boolean;
		if(object_double!=nullptr) delete object_double;
		if(object_long!=nullptr) delete object_long;
		if(object_string!=nullptr) delete object_string;
		if(object_zval!=nullptr) delete object_zval;
	}

	const std::size_t& size() {
		if(object_boolean!=nullptr) return object_boolean->size();
		else if(object_double!=nullptr) return object_double->size();
		else if(object_long!=nullptr) return object_long->size();
		else if(object_string!=nullptr) return object_string->size();
		else return object_zval->size();
	}
};

struct list_object {
    zend_object std;
	char type;
	list_union* object;
	MemoryManager<char*>* memory_manager;
    char* class_name;
};


#endif /* CLASSES_LIST_OBJECT_H_ */
