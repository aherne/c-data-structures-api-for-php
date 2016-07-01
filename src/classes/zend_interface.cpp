#include "zend_interface.h"

ZendInterface::ZendInterface(const char name[], const zend_function_entry methods[]) {
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "", methods);
	ce.name = strdup(name);
	ce.name_length = strlen(name);
	interface_ce = zend_register_internal_interface(&ce TSRMLS_CC);
}

zend_class_entry* ZendInterface::getInterfaceEntry() {
	return interface_ce;
}

ZendInterface::~ZendInterface() {
}
