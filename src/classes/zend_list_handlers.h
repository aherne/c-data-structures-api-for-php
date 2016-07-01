/*
 * ListHandlers.h
 *
 *  Created on: Nov 13, 2015
 *      Author: aherne
 */

#ifndef SRC_ZEND_CLASSES_LISTHANDLERS_H_
#define SRC_ZEND_CLASSES_LISTHANDLERS_H_

class ListHandlers {
public:
	static void setHandlers(zend_object_handlers& class_object_handlers) {
		class_object_handlers.clone_obj = NULL;
		class_object_handlers.read_dimension = read_dimension;
		class_object_handlers.write_dimension = write_dimension;
		class_object_handlers.has_dimension = has_dimension;
		class_object_handlers.unset_dimension = unset_dimension;
		class_object_handlers.count_elements = count_elements;
	}
private:
	static zval* read_dimension(zval *object, zval *zv_offset, int type TSRMLS_DC) {
	    size_t index;
		zval *retval;
		if(!zv_offset || Z_TYPE_P(zv_offset) != IS_LONG) {
			zend_throw_exception(NULL, "Key must be integer!", 0 TSRMLS_CC);
			return retval;
		}
		index = Z_LVAL_P(zv_offset);

		list_object *obj = (list_object *) zend_object_store_get_object(object TSRMLS_CC);
		if (obj->object != NULL) {
			try {
				if(obj->type==TYPE_LONG){
					retval = long2zval(obj->object->object_long->get(index));
				} else if(obj->type==TYPE_DOUBLE){
					retval = double2zval(obj->object->object_double->get(index));
				} else if(obj->type==TYPE_BOOLEAN){
					retval = bool2zval(obj->object->object_boolean->get(index));
				} else if(obj->type==TYPE_STRING){
					retval = str2zval(obj->object->object_string->get(index));
				} else {
					retval = obj->object->object_zval->get(index);
				}
			} catch (const std::out_of_range& e) {
				zend_throw_exception(NULL, "Key must already exist!", 0 TSRMLS_CC);
		        return NULL;
			}
		}
	    return retval;
	}

	static void write_dimension(zval *object, zval *zv_offset, zval *value TSRMLS_DC) {
		list_object *obj = (list_object *)zend_object_store_get_object(object TSRMLS_CC);
		if (obj->object != NULL) {
			if(!zv_offset) {
				try{
		    		if(obj->type == TYPE_LONG) {
		    			obj->object->object_long->addToBottom(zval2long(value));
		    		} else if (obj->type == TYPE_DOUBLE) {
		    			obj->object->object_double->addToBottom(zval2double(value));
		    		} else if (obj->type == TYPE_BOOLEAN) {
		    			obj->object->object_boolean->addToBottom(zval2bool(value));
		    		} else if (obj->type == TYPE_STRING) {
		    			obj->object->object_string->addToBottom(zval2str(value, obj->memory_manager));
		    		} else if (obj->type == TYPE_OBJECT) {
		    			obj->object->object_zval->addToBottom(zval2object(value, obj->class_name));
		    		} else {
		    			obj->object->object_zval->addToBottom(value);
		    		}
				} catch(const std::runtime_error& e) {
					zend_throw_exception(NULL, e.what(), 0 TSRMLS_CC);
			        return;
				}
			} else {
			    size_t index;
				if(Z_TYPE_P(zv_offset) != IS_LONG) {
					zend_throw_exception(NULL, "Key must be integer!", 0 TSRMLS_CC);
					return;
				}
				index = Z_LVAL_P(zv_offset);
				try {
		    		if(obj->type == TYPE_LONG) {
		    			obj->object->object_long->set(index, zval2long(value));
		    		} else if (obj->type == TYPE_DOUBLE) {
		    			obj->object->object_double->set(index, zval2double(value));
		    		} else if (obj->type == TYPE_BOOLEAN) {
		    			obj->object->object_boolean->set(index, zval2bool(value));
		    		} else if (obj->type == TYPE_STRING) {
		    			obj->object->object_string->set(index, zval2str(value, obj->memory_manager));
		    		} else if (obj->type == TYPE_OBJECT) {
		    			obj->object->object_zval->set(index, zval2object(value, obj->class_name));
		    		} else {
		    			obj->object->object_zval->set(index, value);
		    		}
				} catch(const std::runtime_error& e) {
					zend_throw_exception(NULL, e.what(), 0 TSRMLS_CC);
			        return;
				} catch (const std::out_of_range& e) {
					zend_throw_exception(NULL, "Key must already exist!", 0 TSRMLS_CC);
			        return;
				}
			}
		}
	}

	static int has_dimension(zval *object, zval *zv_offset, int check_empty TSRMLS_DC) {
	    size_t index;
		if(!zv_offset || Z_TYPE_P(zv_offset) != IS_LONG) {
			zend_throw_exception(NULL, "Key must be integer!", 0 TSRMLS_CC);
			return 0;
		}
		index = Z_LVAL_P(zv_offset);

		list_object *obj = (list_object *)zend_object_store_get_object(object TSRMLS_CC);
		if (obj->object != NULL) {
			if(obj->type==TYPE_LONG){
				return obj->object->object_long->containsIndex(index);
			} else if(obj->type==TYPE_DOUBLE){
				return obj->object->object_double->containsIndex(index);
			} else if(obj->type==TYPE_BOOLEAN){
				return obj->object->object_boolean->containsIndex(index);
			} else if(obj->type==TYPE_STRING){
				return obj->object->object_string->containsIndex(index);
			} else {
				return obj->object->object_zval->containsIndex(index);
			}
		}
		return 0;
	}

	static void unset_dimension(zval *object, zval *zv_offset TSRMLS_DC){
	    size_t index;
		if(!zv_offset || Z_TYPE_P(zv_offset) != IS_LONG) {
			zend_throw_exception(NULL, "Key must be integer!", 0 TSRMLS_CC);
			return;
		}
		index = Z_LVAL_P(zv_offset);

		list_object *obj = (list_object *)zend_object_store_get_object(object TSRMLS_CC);
		if (obj->object != NULL) {
			try {
				if(obj->type==TYPE_LONG){
					obj->object->object_long->removeIndex(index);
				} else if(obj->type==TYPE_DOUBLE){
					obj->object->object_double->removeIndex(index);
				} else if(obj->type==TYPE_BOOLEAN){
					obj->object->object_boolean->removeIndex(index);
				} else if(obj->type==TYPE_STRING){
					obj->object->object_string->removeIndex(index);
				} else {
					obj->object->object_zval->removeIndex(index);
				}
			} catch (const std::out_of_range& e) {
				zend_throw_exception(NULL, "Key must already exist!", 0 TSRMLS_CC);
			}
		}
	}

	static int count_elements(zval *object, long *count TSRMLS_DC) {
		list_object *obj = (list_object *)zend_object_store_get_object(object TSRMLS_CC);
		if (obj->object != NULL) {
			*count = obj->object->size();
			return SUCCESS;
		}
		return FAILURE;
	}
};

#endif /* SRC_ZEND_CLASSES_LISTHANDLERS_H_ */
