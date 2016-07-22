#include "zend_list.h"

zend_object_handlers ListZendClass::class_object_handlers;

ListZendClass::ListZendClass(const char name[], const zend_function_entry methods[]) {
	// create class entry
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "", methods);
	ce.name = strdup(name);
	ce.name_length = strlen(name);
	class_ce = zend_register_internal_class(&ce TSRMLS_CC);
	class_ce->create_object = &ListZendClass::create_object;
	class_ce->ce_flags |= ZEND_ACC_FINAL_CLASS;

	// set iterator
	class_ce->get_iterator = &ListIterator::getIterator;
	zend_class_implements(class_ce TSRMLS_CC, 1, zend_ce_traversable);

	// set object handlers
	memcpy(&class_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	ListHandlers::setHandlers(class_object_handlers);
}

ListZendClass::~ListZendClass() {

}

zend_class_entry* ListZendClass::getClassEntry() {
	return class_ce;
}

void ListZendClass::free_object(void *object TSRMLS_DC){
	list_object* obj = (list_object*) object;

	// free c++ elements
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
	}

	if(obj->memory_manager!=NULL) {
		delete obj->memory_manager;
		obj->memory_manager = NULL;
	}

	// free the array of properties
	zend_hash_destroy(obj->std.properties);
	FREE_HASHTABLE(obj->std.properties);

	// free the whole struct
	efree(obj);
}

zend_object_value ListZendClass::create_object(zend_class_entry *type TSRMLS_DC)
{
	list_object* obj = (list_object*) emalloc(sizeof(list_object));
	memset(obj, 0, sizeof(list_object));

	// set class type
	obj->std.ce = type;

	// allocate the array of properties
	zval *tmp;
	ALLOC_HASHTABLE(obj->std.properties);
	zend_hash_init(obj->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
	zend_hash_copy(obj->std.properties, &type->properties_info, (copy_ctor_func_t)zval_add_ref, (void *)&tmp, sizeof(zval *));

	// generates an object zval
	zend_object_value retval;
	retval.handle = zend_objects_store_put(obj, NULL, &ListZendClass::free_object, NULL TSRMLS_CC);
	retval.handlers = &class_object_handlers;
	return retval;
}

void ListZendClass::implements(zend_class_entry* interface) {
	zend_class_implements(class_ce TSRMLS_CC, 1, interface);
}
