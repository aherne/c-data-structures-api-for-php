/*
 * ListIterator.h
 *
 *  Created on: Nov 13, 2015
 *      Author: aherne
 */

#ifndef SRC_ZEND_CLASSES_LISTITERATOR_H_
#define SRC_ZEND_CLASSES_LISTITERATOR_H_

class ListIterator {
public:
	static zend_object_iterator* getIterator(zend_class_entry *ce, zval *object, int by_ref TSRMLS_DC) {
	    if (by_ref) {
	        zend_throw_exception(NULL, "Cannot iterate buffer view by reference", 0 TSRMLS_CC);
	        return NULL;
	    }

	    list_object_iterator *iter;
	    iter = (list_object_iterator*) emalloc(sizeof(list_object_iterator));
	    iter->intern.funcs = (zend_object_iterator_funcs*) emalloc(sizeof(zend_object_iterator_funcs));
	    iter->intern.funcs->dtor = &dtor;
	    iter->intern.funcs->get_current_data = &get_current_data;
	    iter->intern.funcs->get_current_key = &get_current_key;
	    iter->intern.funcs->move_forward = &move_forward;
	    iter->intern.funcs->rewind = &rewind;
	    iter->intern.funcs->valid = &valid;
	    iter->intern.data = object;
	    Z_ADDREF_P(object);

	    iter->view = (list_object*) zend_object_store_get_object(object TSRMLS_CC);
	    iter->offset = 0;
	    iter->current = NULL;

	    return (zend_object_iterator*) iter;
	}
private:
	static void dtor(zend_object_iterator *intern TSRMLS_DC){
		list_object_iterator *iter = (list_object_iterator*) intern;
	    zval_ptr_dtor((zval **) &intern->data);
	    if(destroyIterator(iter->view->type)) {
			if (iter->current) {
				zval_ptr_dtor(&iter->current);
			}
	    }
	    efree(iter);
	}

	static int valid(zend_object_iterator *intern TSRMLS_DC){
		list_object_iterator *iter = (list_object_iterator*) intern;
		if(iter->view->type==TYPE_LONG) 		return iter->offset < ((List<long>*) iter->view->object)->size() ? SUCCESS : FAILURE;
		else if(iter->view->type==TYPE_DOUBLE) 	return iter->offset < ((List<double>*) iter->view->object)->size() ? SUCCESS : FAILURE;
		else if(iter->view->type==TYPE_BOOLEAN) return iter->offset < ((List<char>*) iter->view->object)->size() ? SUCCESS : FAILURE;
		else if(iter->view->type==TYPE_STRING) 	return iter->offset < ((List<char*>*) iter->view->object)->size() ? SUCCESS : FAILURE;
		else 									return iter->offset < ((List<zval*>*) iter->view->object)->size() ? SUCCESS : FAILURE;
	}

	static void get_current_data(zend_object_iterator *intern, zval ***data TSRMLS_DC) {
		list_object_iterator *iter = (list_object_iterator*) intern;
	    if(destroyIterator(iter->view->type)) {
			if (iter->current) {
				zval_ptr_dtor(&iter->current);
			}
	    }
		if(iter->view->type==TYPE_LONG){
		    if (iter->offset < ((List<long>*) iter->view->object)->size()) {
		        iter->current = long2zval((*((List<long>*) iter->view->object))[iter->offset]);
		        *data = &iter->current;
		    } else {
		        *data = NULL;
		    }
		} else if(iter->view->type==TYPE_DOUBLE){
		    if (iter->offset < ((List<double>*) iter->view->object)->size()) {
		        iter->current = double2zval((*((List<double>*) iter->view->object))[iter->offset]);
		        *data = &iter->current;
		    } else {
		        *data = NULL;
		    }
		} else if(iter->view->type==TYPE_BOOLEAN){
		    if (iter->offset < ((List<char>*) iter->view->object)->size()) {
		        iter->current = bool2zval((*((List<char>*) iter->view->object))[iter->offset]);
		        *data = &iter->current;
		    } else {
		        *data = NULL;
		    }
		} else if(iter->view->type==TYPE_STRING){
		    if (iter->offset < ((List<char*>*) iter->view->object)->size()) {
		        iter->current = str2zval((*((List<char*>*) iter->view->object))[iter->offset]);
		        *data = &iter->current;
		    } else {
		        *data = NULL;
		    }
		} else {
		    if (iter->offset <((List<zval*>*) iter->view->object)->size()) {
		        iter->current = (*((List<zval*>*) iter->view->object))[iter->offset];
		        *data = &iter->current;
		    } else {
		        *data = NULL;
		    }
		}
	}

	static void get_current_key(zend_object_iterator *intern, zval *key TSRMLS_DC) {
		list_object_iterator *iter = (list_object_iterator*) intern;
	    ZVAL_LONG(key, iter->offset);
	}

	static void move_forward(zend_object_iterator *intern TSRMLS_DC){
		list_object_iterator* iter = (list_object_iterator*) intern;
	    iter->offset++;
	}

	static void rewind(zend_object_iterator *intern TSRMLS_DC){
		list_object_iterator* iter = (list_object_iterator*) iter;
	    iter->offset = 0;
	    iter->current = NULL;
	}
};

#endif /* SRC_ZEND_CLASSES_LISTITERATOR_H_ */
