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
					retval = long2zval(((List<long>*) obj->object)->get(index));
				} else if(obj->type==TYPE_DOUBLE){
					retval = double2zval(((List<double>*) obj->object)->get(index));
				} else if(obj->type==TYPE_BOOLEAN){
					retval = bool2zval(((List<char>*) obj->object)->get(index));
				} else if(obj->type==TYPE_STRING){
					retval = str2zval(((List<char*>*) obj->object)->get(index));
				} else {
					retval = ((List<zval*>*) obj->object)->get(index);
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
		    			((List<long>*) obj->object)->addToBottom(zval2long(value));
		    		} else if (obj->type == TYPE_DOUBLE) {
		    			((List<double>*) obj->object)->addToBottom(zval2double(value));
		    		} else if (obj->type == TYPE_BOOLEAN) {
		    			((List<char>*) obj->object)->addToBottom(zval2bool(value));
		    		} else if (obj->type == TYPE_STRING) {
		    			((List<char*>*) obj->object)->addToBottom(zval2str(value, obj->memory_manager));
		    		} else if (obj->type == TYPE_OBJECT) {
		    			((List<zval*>*) obj->object)->addToBottom(zval2object(value, obj->class_name));
		    		} else {
		    			((List<zval*>*) obj->object)->addToBottom(value);
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
		    			((List<long>*) obj->object)->set(index, zval2long(value));
		    		} else if (obj->type == TYPE_DOUBLE) {
		    			((List<double>*) obj->object)->set(index, zval2double(value));
		    		} else if (obj->type == TYPE_BOOLEAN) {
		    			((List<char>*) obj->object)->set(index, zval2bool(value));
		    		} else if (obj->type == TYPE_STRING) {
		    			((List<char*>*) obj->object)->set(index, zval2str(value, obj->memory_manager));
		    		} else if (obj->type == TYPE_OBJECT) {
		    			((List<zval*>*) obj->object)->set(index, zval2object(value, obj->class_name));
		    		} else {
		    			((List<zval*>*) obj->object)->set(index, value);
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
				return ((List<long>*) obj->object)->containsIndex(index);
			} else if(obj->type==TYPE_DOUBLE){
				return ((List<double>*) obj->object)->containsIndex(index);
			} else if(obj->type==TYPE_BOOLEAN){
				return ((List<char>*) obj->object)->containsIndex(index);
			} else if(obj->type==TYPE_STRING){
				return ((List<char*>*) obj->object)->containsIndex(index);
			} else {
				return ((List<zval*>*) obj->object)->containsIndex(index);
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
					((List<long>*) obj->object)->removeIndex(index);
				} else if(obj->type==TYPE_DOUBLE){
					((List<double>*) obj->object)->removeIndex(index);
				} else if(obj->type==TYPE_BOOLEAN){
					((List<char>*) obj->object)->removeIndex(index);
				} else if(obj->type==TYPE_STRING){
					((List<char*>*) obj->object)->removeIndex(index);
				} else {
					((List<zval*>*) obj->object)->removeIndex(index);
				}
			} catch (const std::out_of_range& e) {
				zend_throw_exception(NULL, "Key must already exist!", 0 TSRMLS_CC);
			}
		}
	}

	static int count_elements(zval *object, long *count TSRMLS_DC) {
		list_object *obj = (list_object *)zend_object_store_get_object(object TSRMLS_CC);
		if (obj->object != NULL) {
			if(obj->type==TYPE_LONG){
				*count = ((List<long>*) obj->object)->size();
			} else if(obj->type==TYPE_DOUBLE){
				*count = ((List<double>*) obj->object)->size();
			} else if(obj->type==TYPE_BOOLEAN){
				*count = ((List<char>*) obj->object)->size();
			} else if(obj->type==TYPE_STRING){
				*count = ((List<char*>*) obj->object)->size();
			} else {
				*count = ((List<zval*>*) obj->object)->size();
			}
			return SUCCESS;
		}
		return FAILURE;
	}
};

#endif /* SRC_ZEND_CLASSES_LISTHANDLERS_H_ */
