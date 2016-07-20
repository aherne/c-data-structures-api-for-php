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
	obj->type = type;
	if(type == TYPE_LONG) {
		obj->object = new DoublyLinkedList<long>;
	} else if (type == TYPE_DOUBLE) {
		obj->object = new DoublyLinkedList<double>;
	} else if (type == TYPE_BOOLEAN) {
		obj->object = new DoublyLinkedList<char>;
	} else if (type == TYPE_STRING) {
		obj->memory_manager = new MemoryManager<char*>;
		obj->object = new DoublyLinkedList<char*>;
	} else if(type==TYPE_OBJECT) {
		obj->class_name = strdup(Z_STRVAL_P(temp));
		obj->object = new DoublyLinkedList<zval*>;
	} else {
		obj->object = new DoublyLinkedList<zval*>;
	}
}

PHP_METHOD(DoublyLinkedList, __destruct){
	list_object* obj = (list_object*) zend_object_store_get_object(getThis() TSRMLS_CC);
	if(obj->object != NULL) {
		if(obj->type == TYPE_LONG) {
			delete ((List<long>*) obj->object);
		} else if (obj->type == TYPE_DOUBLE) {
			delete ((List<double>*) obj->object);
		} else if (obj->type == TYPE_BOOLEAN) {
			delete ((List<char>*) obj->object);
		} else if (obj->type == TYPE_STRING) {
			delete ((List<char*>*) obj->object);
		} else {
			delete ((List<zval*>*) obj->object);
		}
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
    			((List<long>*) obj->object)->addToTop(zval2long(temp));
    		} else if (obj->type == TYPE_DOUBLE) {
    			((List<double>*) obj->object)->addToTop(zval2double(temp));
    		} else if (obj->type == TYPE_BOOLEAN) {
    			((List<char>*) obj->object)->addToTop(zval2bool(temp));
    		} else if (obj->type == TYPE_STRING) {
    			((List<char*>*) obj->object)->addToTop(zval2str(temp, obj->memory_manager));
    		} else if (obj->type == TYPE_OBJECT) {
    			((List<zval*>*) obj->object)->addToTop(zval2object(temp, obj->class_name));
    		} else {
    			((List<zval*>*) obj->object)->addToTop(temp);
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
    			((List<long>*) obj->object)->addToBottom(zval2long(temp));
    		} else if (obj->type == TYPE_DOUBLE) {
    			((List<double>*) obj->object)->addToBottom(zval2double(temp));
    		} else if (obj->type == TYPE_BOOLEAN) {
    			((List<char>*) obj->object)->addToBottom(zval2bool(temp));
    		} else if (obj->type == TYPE_STRING) {
    			((List<char*>*) obj->object)->addToBottom(zval2str(temp, obj->memory_manager));
    		} else if (obj->type == TYPE_OBJECT) {
    			((List<zval*>*) obj->object)->addToBottom(zval2object(temp, obj->class_name));
    		} else {
    			((List<zval*>*) obj->object)->addToBottom(temp);
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
    			((List<long>*) obj->object)->set(index, zval2long(temp));
    		} else if (obj->type == TYPE_DOUBLE) {
    			((List<double>*) obj->object)->set(index, zval2double(temp));
    		} else if (obj->type == TYPE_BOOLEAN) {
    			((List<char>*) obj->object)->set(index, zval2bool(temp));
    		} else if (obj->type == TYPE_STRING) {
    			((List<char*>*) obj->object)->set(index, zval2str(temp, obj->memory_manager));
    		} else if (obj->type == TYPE_OBJECT) {
    			((List<zval*>*) obj->object)->set(index, zval2object(temp, obj->class_name));
    		} else {
    			((List<zval*>*) obj->object)->set(index, temp);
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
    			((List<long>*) obj->object)->emplace(index, zval2long(temp));
    		} else if (obj->type == TYPE_DOUBLE) {
    			((List<double>*) obj->object)->emplace(index, zval2double(temp));
    		} else if (obj->type == TYPE_BOOLEAN) {
    			((List<char>*) obj->object)->emplace(index, zval2bool(temp));
    		} else if (obj->type == TYPE_STRING) {
    			((List<char*>*) obj->object)->emplace(index, zval2str(temp, obj->memory_manager));
    		} else if (obj->type == TYPE_OBJECT) {
    			((List<zval*>*) obj->object)->emplace(index, zval2object(temp, obj->class_name));
    		} else {
    			((List<zval*>*) obj->object)->emplace(index, temp);
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
    			RETURN_LONG(((List<long>*) obj->object)->get(index));
    		} else if (obj->type == TYPE_DOUBLE) {
    			RETURN_DOUBLE(((List<double>*) obj->object)->get(index));
    		} else if (obj->type == TYPE_BOOLEAN) {
    			RETURN_BOOL(((List<char>*) obj->object)->get(index));
    		} else if (obj->type == TYPE_STRING) {
    			RETURN_STRING(((List<char*>*) obj->object)->get(index),1);
    		} else {
    			RETURN_ZVAL(((List<zval*>*) obj->object)->get(index),1,0);
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
			RETURN_LONG(((List<long>*) obj->object)->size());
		} else if (obj->type == TYPE_DOUBLE) {
			RETURN_LONG(((List<double>*) obj->object)->size());
		} else if (obj->type == TYPE_BOOLEAN) {
			RETURN_LONG(((List<char>*) obj->object)->size());
		} else if (obj->type == TYPE_STRING) {
			RETURN_LONG(((List<char*>*) obj->object)->size());
		} else {
			RETURN_LONG(((List<zval*>*) obj->object)->size());
		}
    }
}

PHP_METHOD(DoublyLinkedList, isEmpty) {
	list_object* obj = (list_object*) zend_object_store_get_object(getThis() TSRMLS_CC);
    if (obj->object != NULL) {
		if(obj->type == TYPE_LONG) {
			RETURN_BOOL(((List<long>*) obj->object)->isEmpty());
		} else if (obj->type == TYPE_DOUBLE) {
			RETURN_BOOL(((List<double>*) obj->object)->isEmpty());
		} else if (obj->type == TYPE_BOOLEAN) {
			RETURN_BOOL(((List<char>*) obj->object)->isEmpty());
		} else if (obj->type == TYPE_STRING) {
			RETURN_BOOL(((List<char*>*) obj->object)->isEmpty());
		} else {
			RETURN_BOOL(((List<zval*>*) obj->object)->isEmpty());
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
			RETURN_BOOL(((List<long>*) obj->object)->containsIndex(index));
		} else if (obj->type == TYPE_DOUBLE) {
			RETURN_BOOL(((List<double>*) obj->object)->containsIndex(index));
		} else if (obj->type == TYPE_BOOLEAN) {
			RETURN_BOOL(((List<char>*) obj->object)->containsIndex(index));
		} else if (obj->type == TYPE_STRING) {
			RETURN_BOOL(((List<char*>*) obj->object)->containsIndex(index));
		} else {
			RETURN_BOOL(((List<zval*>*) obj->object)->containsIndex(index));
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
    			((List<long>*) obj->object)->removeIndex(index);
    		} else if (obj->type == TYPE_DOUBLE) {
    			((List<double>*) obj->object)->removeIndex(index);
    		} else if (obj->type == TYPE_BOOLEAN) {
    			((List<char>*) obj->object)->removeIndex(index);
    		} else if (obj->type == TYPE_STRING) {
    			((List<char*>*) obj->object)->removeIndex(index);
    		} else {
    			((List<zval*>*) obj->object)->removeIndex(index);
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
    			RETURN_BOOL(((List<long>*) obj->object)->containsValue(zval2long(temp)));
    		} else if (obj->type == TYPE_DOUBLE) {
    			RETURN_BOOL(((List<double>*) obj->object)->containsValue(zval2double(temp)));
    		} else if (obj->type == TYPE_BOOLEAN) {
    			RETURN_BOOL(((List<char>*) obj->object)->containsValue(zval2bool(temp)));
    		} else if (obj->type == TYPE_STRING) {
    			RETURN_BOOL(((List<char*>*) obj->object)->containsValue(zval2str(temp, obj->memory_manager)));
    		} else if (obj->type == TYPE_OBJECT) {
    			RETURN_BOOL(((List<zval*>*) obj->object)->containsValue(zval2object(temp, obj->class_name)));
    		} else {
    			RETURN_BOOL(((List<zval*>*) obj->object)->containsValue(temp));
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
    			((List<long>*) obj->object)->removeValue(zval2long(temp));
    		} else if (obj->type == TYPE_DOUBLE) {
    			((List<double>*) obj->object)->removeValue(zval2double(temp));
    		} else if (obj->type == TYPE_BOOLEAN) {
    			((List<char>*) obj->object)->removeValue(zval2bool(temp));
    		} else if (obj->type == TYPE_STRING) {
    			((List<char*>*) obj->object)->removeValue(zval2str(temp, obj->memory_manager));
    		} else if (obj->type == TYPE_OBJECT) {
    			((List<zval*>*) obj->object)->removeValue(zval2object(temp, obj->class_name));
    		} else {
    			((List<zval*>*) obj->object)->removeValue(temp);
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
			((List<long>*) obj->object)->clear();
		} else if (obj->type == TYPE_DOUBLE) {
			((List<double>*) obj->object)->clear();
		} else if (obj->type == TYPE_BOOLEAN) {
			((List<char>*) obj->object)->clear();
		} else if (obj->type == TYPE_STRING) {
			((List<char*>*) obj->object)->clear();
		} else {
			((List<zval*>*) obj->object)->clear();
		}
	}
}
PHP_METHOD(DoublyLinkedList, toValue) {
	array_init(return_value);
	list_object* obj = (list_object*) zend_object_store_get_object(getThis() TSRMLS_CC);
    if (obj->object != NULL) {
		if(obj->type == TYPE_LONG) {
			DoublyLinkedList<long>* list = (DoublyLinkedList<long>*) obj->object;
	    	for (auto it=list->begin(); it!=list->end(); ++it) {
				add_next_index_long(return_value,*it);
			}
		} else if (obj->type == TYPE_DOUBLE) {
			DoublyLinkedList<double>* list = (DoublyLinkedList<double>*) obj->object;
	    	for (auto it=list->begin(); it!=list->end(); ++it) {
				add_next_index_double(return_value,*it);
			}
		} else if (obj->type == TYPE_BOOLEAN) {
			DoublyLinkedList<char>* list = (DoublyLinkedList<char>*) obj->object;
	    	for (auto it=list->begin(); it!=list->end(); ++it) {
				add_next_index_bool(return_value,*it);
			}
		} else if (obj->type == TYPE_STRING) {
			DoublyLinkedList<char*>* list = (DoublyLinkedList<char*>*) obj->object;
	    	for (auto it=list->begin(); it!=list->end(); ++it) {
				add_next_index_string(return_value,*it,1);
			}
		} else {
			DoublyLinkedList<zval*>* list = (DoublyLinkedList<zval*>*) obj->object;
	    	for (auto it=list->begin(); it!=list->end(); ++it) {
				Z_ADDREF_P(*it);
				add_next_index_zval(return_value,*it);
			}
		}
    }
}
