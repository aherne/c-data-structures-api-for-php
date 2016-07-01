#include "doublylinkedlist.h"

PHP_METHOD(DoublyLinkedList, __construct){
	zval* temp;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &temp) == FAILURE) {
		RETURN_NULL();
	}

	// get type
	char type = 0;
	try {
		type = getDataType(temp);
	} catch (const std::runtime_error& e) {
		zend_throw_exception(NULL, e.what(), 0 TSRMLS_CC);
		RETURN_NULL();
	}

	// create object
	list_object* obj = (list_object*) zend_object_store_get_object(getThis() TSRMLS_CC);
	obj->object = new list_union;
	obj->type = type;
	if(type == TYPE_LONG) {
		obj->object->object_long = new DoublyLinkedList<long>;
	} else if (type == TYPE_DOUBLE) {
		obj->object->object_double = new DoublyLinkedList<double>;
	} else if (type == TYPE_BOOLEAN) {
		obj->object->object_boolean = new DoublyLinkedList<char>;
	} else if (type == TYPE_STRING) {
		obj->memory_manager = new MemoryManager<char*>;
		obj->object->object_string = new DoublyLinkedList<char*>;
	} else if(type==TYPE_OBJECT) {
		obj->class_name = strdup(Z_STRVAL_P(temp));
		obj->object->object_zval = new DoublyLinkedList<zval*>;
	} else {
		obj->object->object_zval = new DoublyLinkedList<zval*>;
	}
}

PHP_METHOD(DoublyLinkedList, __destruct){
	list_object* obj = (list_object*) zend_object_store_get_object(getThis() TSRMLS_CC);
	if(obj->object != NULL) {
		delete obj->object;
		obj->object = NULL;

		if(obj->type == TYPE_STRING) {
			delete obj->memory_manager;
			obj->memory_manager = NULL;
		} else if(obj->type == TYPE_OBJECT) {
			delete obj->class_name;
			obj->class_name = NULL;
		}
	}
}

PHP_METHOD(DoublyLinkedList, addToTop){
	zval* temp;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &temp) == FAILURE) {
		RETURN_NULL();
	}

	list_object* obj = (list_object*) zend_object_store_get_object(getThis() TSRMLS_CC);
    if (obj->object != NULL) {
    	try {
    		if(obj->type == TYPE_LONG) {
    			obj->object->object_long->addToTop(zval2long(temp));
    		} else if (obj->type == TYPE_DOUBLE) {
    			obj->object->object_double->addToTop(zval2double(temp));
    		} else if (obj->type == TYPE_BOOLEAN) {
    			obj->object->object_boolean->addToTop(zval2bool(temp));
    		} else if (obj->type == TYPE_STRING) {
    			obj->object->object_string->addToTop(zval2str(temp, obj->memory_manager));
    		} else if (obj->type == TYPE_OBJECT) {
    			obj->object->object_zval->addToTop(zval2object(temp, obj->class_name));
    		} else {
    			obj->object->object_zval->addToTop(temp);
    		}
    	} catch (const std::runtime_error& e) {
    		zend_throw_exception(NULL, e.what(), 0 TSRMLS_CC);
    		RETURN_NULL();
    	}
    }
}

PHP_METHOD(DoublyLinkedList, addToBottom){
	zval* temp;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &temp) == FAILURE) {
		RETURN_NULL();
	}

	list_object* obj = (list_object*) zend_object_store_get_object(getThis() TSRMLS_CC);
    if (obj->object != NULL) {
    	try {
    		if(obj->type == TYPE_LONG) {
    			obj->object->object_long->addToBottom(zval2long(temp));
    		} else if (obj->type == TYPE_DOUBLE) {
    			obj->object->object_double->addToBottom(zval2double(temp));
    		} else if (obj->type == TYPE_BOOLEAN) {
    			obj->object->object_boolean->addToBottom(zval2bool(temp));
    		} else if (obj->type == TYPE_STRING) {
    			obj->object->object_string->addToBottom(zval2str(temp, obj->memory_manager));
    		} else if (obj->type == TYPE_OBJECT) {
    			obj->object->object_zval->addToBottom(zval2object(temp, obj->class_name));
    		} else {
    			obj->object->object_zval->addToBottom(temp);
    		}
    	} catch (const std::runtime_error& e) {
    		zend_throw_exception(NULL, e.what(), 0 TSRMLS_CC);
    		RETURN_NULL();
    	}
    }
}

PHP_METHOD(DoublyLinkedList, set){
	size_t index;
	zval* temp;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz", &index, &temp) == FAILURE) {
		RETURN_NULL();
	}

	list_object* obj = (list_object*) zend_object_store_get_object(getThis() TSRMLS_CC);
    if (obj->object != NULL) {
    	try {
    		if(obj->type == TYPE_LONG) {
    			obj->object->object_long->set(index, zval2long(temp));
    		} else if (obj->type == TYPE_DOUBLE) {
    			obj->object->object_double->set(index, zval2double(temp));
    		} else if (obj->type == TYPE_BOOLEAN) {
    			obj->object->object_boolean->set(index, zval2bool(temp));
    		} else if (obj->type == TYPE_STRING) {
    			obj->object->object_string->set(index, zval2str(temp, obj->memory_manager));
    		} else if (obj->type == TYPE_OBJECT) {
    			obj->object->object_zval->set(index, zval2object(temp, obj->class_name));
    		} else {
    			obj->object->object_zval->set(index, temp);
    		}
    	} catch (const std::runtime_error& e) {
    		zend_throw_exception(NULL, e.what(), 0 TSRMLS_CC);
    		RETURN_NULL();
    	} catch (const std::out_of_range& e) {
    		zend_throw_exception(NULL, e.what(), 0 TSRMLS_CC);
    		RETURN_NULL();
    	}
    }
}

PHP_METHOD(DoublyLinkedList, emplace){
	size_t index;
	zval* temp;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz", &index, &temp) == FAILURE) {
		RETURN_NULL();
	}

	list_object* obj = (list_object*) zend_object_store_get_object(getThis() TSRMLS_CC);
    if (obj->object != NULL) {
    	try {
    		if(obj->type == TYPE_LONG) {
    			obj->object->object_long->emplace(index, zval2long(temp));
    		} else if (obj->type == TYPE_DOUBLE) {
    			obj->object->object_double->emplace(index, zval2double(temp));
    		} else if (obj->type == TYPE_BOOLEAN) {
    			obj->object->object_boolean->emplace(index, zval2bool(temp));
    		} else if (obj->type == TYPE_STRING) {
    			obj->object->object_string->emplace(index, zval2str(temp, obj->memory_manager));
    		} else if (obj->type == TYPE_OBJECT) {
    			obj->object->object_zval->emplace(index, zval2object(temp, obj->class_name));
    		} else {
    			obj->object->object_zval->emplace(index, temp);
    		}
    	} catch (const std::runtime_error& e) {
    		zend_throw_exception(NULL, e.what(), 0 TSRMLS_CC);
    		RETURN_NULL();
    	} catch (const std::out_of_range& e) {
    		zend_throw_exception(NULL, e.what(), 0 TSRMLS_CC);
    		RETURN_NULL();
    	}
    }
}

PHP_METHOD(DoublyLinkedList, get){
	long index;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &index) == FAILURE) {
		RETURN_NULL();
	}

	list_object* obj = (list_object*) zend_object_store_get_object(getThis() TSRMLS_CC);
    if (obj->object != NULL) {
    	try {
    		if(obj->type == TYPE_LONG) {
    			RETURN_LONG(obj->object->object_long->get(index));
    		} else if (obj->type == TYPE_DOUBLE) {
    			RETURN_DOUBLE(obj->object->object_double->get(index));
    		} else if (obj->type == TYPE_BOOLEAN) {
    			RETURN_BOOL(obj->object->object_boolean->get(index));
    		} else if (obj->type == TYPE_STRING) {
    			RETURN_STRING(obj->object->object_string->get(index),1);
    		} else {
    			RETURN_ZVAL(obj->object->object_zval->get(index),1,0);
    		}
    	} catch (const std::out_of_range& e) {
    		zend_throw_exception(NULL, e.what(), 0 TSRMLS_CC);
    		RETURN_NULL();
    	}
    }
}

PHP_METHOD(DoublyLinkedList, size) {
	list_object* obj = (list_object*) zend_object_store_get_object(getThis() TSRMLS_CC);
    if (obj->object != NULL) {
		if(obj->type == TYPE_LONG) {
			RETURN_LONG(obj->object->object_long->size());
		} else if (obj->type == TYPE_DOUBLE) {
			RETURN_LONG(obj->object->object_double->size());
		} else if (obj->type == TYPE_BOOLEAN) {
			RETURN_LONG(obj->object->object_boolean->size());
		} else if (obj->type == TYPE_STRING) {
			RETURN_LONG(obj->object->object_string->size());
		} else {
			RETURN_LONG(obj->object->object_zval->size());
		}
    }
}

PHP_METHOD(DoublyLinkedList, isEmpty) {
	list_object* obj = (list_object*) zend_object_store_get_object(getThis() TSRMLS_CC);
    if (obj->object != NULL) {
		if(obj->type == TYPE_LONG) {
			RETURN_BOOL(obj->object->object_long->isEmpty());
		} else if (obj->type == TYPE_DOUBLE) {
			RETURN_BOOL(obj->object->object_double->isEmpty());
		} else if (obj->type == TYPE_BOOLEAN) {
			RETURN_BOOL(obj->object->object_boolean->isEmpty());
		} else if (obj->type == TYPE_STRING) {
			RETURN_BOOL(obj->object->object_string->isEmpty());
		} else {
			RETURN_BOOL(obj->object->object_zval->isEmpty());
		}
    }
}

PHP_METHOD(DoublyLinkedList, containsIndex){
	long index;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &index) == FAILURE) {
		RETURN_NULL();
	}

	list_object* obj = (list_object*) zend_object_store_get_object(getThis() TSRMLS_CC);
    if (obj->object != NULL) {
		if(obj->type == TYPE_LONG) {
			RETURN_BOOL(obj->object->object_long->containsIndex(index));
		} else if (obj->type == TYPE_DOUBLE) {
			RETURN_BOOL(obj->object->object_double->containsIndex(index));
		} else if (obj->type == TYPE_BOOLEAN) {
			RETURN_BOOL(obj->object->object_boolean->containsIndex(index));
		} else if (obj->type == TYPE_STRING) {
			RETURN_BOOL(obj->object->object_string->containsIndex(index));
		} else {
			RETURN_BOOL(obj->object->object_zval->containsIndex(index));
		}
    }
}

PHP_METHOD(DoublyLinkedList, removeIndex){
	size_t index;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &index) == FAILURE) {
		RETURN_NULL();
	}

	list_object* obj = (list_object*) zend_object_store_get_object(getThis() TSRMLS_CC);
	if (obj->object != NULL) {
		try {
    		if(obj->type == TYPE_LONG) {
    			obj->object->object_long->removeIndex(index);
    		} else if (obj->type == TYPE_DOUBLE) {
    			obj->object->object_double->removeIndex(index);
    		} else if (obj->type == TYPE_BOOLEAN) {
    			obj->object->object_boolean->removeIndex(index);
    		} else if (obj->type == TYPE_STRING) {
    			obj->object->object_string->removeIndex(index);
    		} else {
    			obj->object->object_zval->removeIndex(index);
    		}
		} catch (const std::out_of_range& e) {
			zend_throw_exception(NULL, e.what(), 0 TSRMLS_CC);
			RETURN_NULL();
		}
    }
}

PHP_METHOD(DoublyLinkedList, containsValue) {
	zval* temp;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &temp) == FAILURE) {
		RETURN_NULL();
	}

	list_object* obj = (list_object*) zend_object_store_get_object(getThis() TSRMLS_CC);
    if (obj->object != NULL) {
    	try {
    		if(obj->type == TYPE_LONG) {
    			RETURN_BOOL(obj->object->object_long->containsValue(zval2long(temp)));
    		} else if (obj->type == TYPE_DOUBLE) {
    			RETURN_BOOL(obj->object->object_double->containsValue(zval2double(temp)));
    		} else if (obj->type == TYPE_BOOLEAN) {
    			RETURN_BOOL(obj->object->object_boolean->containsValue(zval2bool(temp)));
    		} else if (obj->type == TYPE_STRING) {
    			RETURN_BOOL(obj->object->object_string->containsValue(zval2str(temp, obj->memory_manager)));
    		} else if (obj->type == TYPE_OBJECT) {
    			RETURN_BOOL(obj->object->object_zval->containsValue(zval2object(temp, obj->class_name)));
    		} else {
    			RETURN_BOOL(obj->object->object_zval->containsValue(temp));
    		}
		} catch (const std::runtime_error& e) {
			zend_throw_exception(NULL, e.what(), 0 TSRMLS_CC);
			RETURN_NULL();
		}
    }
}

PHP_METHOD(DoublyLinkedList, removeValue) {
	zval* temp;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &temp) == FAILURE) {
		RETURN_NULL();
	}

	list_object* obj = (list_object*) zend_object_store_get_object(getThis() TSRMLS_CC);
    if (obj->object != NULL) {
		try {
    		if(obj->type == TYPE_LONG) {
    			obj->object->object_long->removeValue(zval2long(temp));
    		} else if (obj->type == TYPE_DOUBLE) {
    			obj->object->object_double->removeValue(zval2double(temp));
    		} else if (obj->type == TYPE_BOOLEAN) {
    			obj->object->object_boolean->removeValue(zval2bool(temp));
    		} else if (obj->type == TYPE_STRING) {
    			obj->object->object_string->removeValue(zval2str(temp, obj->memory_manager));
    		} else if (obj->type == TYPE_OBJECT) {
    			obj->object->object_zval->removeValue(zval2object(temp, obj->class_name));
    		} else {
    			obj->object->object_zval->removeValue(temp);
    		}
		} catch (const std::runtime_error& e) {
    		zend_throw_exception(NULL, e.what(), 0 TSRMLS_CC);
    		RETURN_NULL();
    	} catch (const std::out_of_range& e) {
			zend_throw_exception(NULL, e.what(), 0 TSRMLS_CC);
			RETURN_NULL();
		}
    }
}

PHP_METHOD(DoublyLinkedList, clear) {
	list_object* obj = (list_object*) zend_object_store_get_object(getThis() TSRMLS_CC);
	if(obj->object != NULL) {
		if(obj->type == TYPE_LONG) {
			obj->object->object_long->clear();
		} else if (obj->type == TYPE_DOUBLE) {
			obj->object->object_double->clear();
		} else if (obj->type == TYPE_BOOLEAN) {
			obj->object->object_boolean->clear();
		} else if (obj->type == TYPE_STRING) {
			obj->object->object_string->clear();
		} else {
			obj->object->object_zval->clear();
		}
	}
}
PHP_METHOD(DoublyLinkedList, toValue) {
	array_init(return_value);
	list_object* obj = (list_object*) zend_object_store_get_object(getThis() TSRMLS_CC);
    if (obj->object != NULL) {
		if(obj->type == TYPE_LONG) {
	    	std::size_t size = obj->object->object_long->size();
			for (std::size_t i=0; i<size; ++i) {
				add_next_index_long(return_value,(*obj->object->object_long)[i]);
			}
		} else if (obj->type == TYPE_DOUBLE) {
	    	std::size_t size = obj->object->object_double->size();
			for (std::size_t i=0; i<size; ++i) {
				add_next_index_double(return_value,(*obj->object->object_double)[i]);
			}
		} else if (obj->type == TYPE_BOOLEAN) {
	    	std::size_t size = obj->object->object_boolean->size();
			for (std::size_t i=0; i<size; ++i) {
				add_next_index_bool(return_value,(*obj->object->object_boolean)[i]);
			}
		} else if (obj->type == TYPE_STRING) {
	    	std::size_t size = obj->object->object_string->size();
			for (std::size_t i=0; i<size; ++i) {
				add_next_index_string(return_value,(*obj->object->object_string)[i],1);
			}
		} else {
	    	std::size_t size = obj->object->object_zval->size();
			for (std::size_t i=0; i<size; ++i) {
				Z_ADDREF_P((*obj->object->object_zval)[i]);
				add_next_index_zval(return_value,(*obj->object->object_zval)[i]);
			}
		}
    }
}
