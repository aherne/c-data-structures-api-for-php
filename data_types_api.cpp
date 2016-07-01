#include "php_data_types_api.h"
#include "src/classes/arraylist.h"
#include "src/classes/linkedlist.h"
#include "src/classes/doublylinkedlist.h"
#include "src/classes/zend_list.h"
#include "src/classes/zend_interface.h"

#define PHP_DATA_TYPES_API_EXTNAME  "data_types_api"
#define PHP_DATA_TYPES_API_EXTVER   "0.1"

// Declares a callback function that Zend will call the first time a module is loaded into a particular instance of PHP.
PHP_MINIT_FUNCTION(data_types_api)
{
	ZendInterface listInterface(list_interface_name, list_interface_methods);

	ListZendClass arrayListClass(arraylist_class_name, arraylist_class_methods);
	arrayListClass.implements(listInterface.getInterfaceEntry());

	ListZendClass linkedListClass(linkedlist_class_name, linkedlist_class_methods);
	linkedListClass.implements(listInterface.getInterfaceEntry());

	ListZendClass doublyLinkedListClass(doublylinkedlist_class_name, doublylinkedlist_class_methods);
	doublyLinkedListClass.implements(listInterface.getInterfaceEntry());

    return SUCCESS;
}

zend_module_entry data_types_api_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_DATA_TYPES_API_EXTNAME,
    NULL,        /* Functions */
    PHP_MINIT(data_types_api),        /* MINIT */
    NULL,        /* MSHUTDOWN */
    NULL,        /* RINIT */
    NULL,        /* RSHUTDOWN */
    NULL,        /* MINFO */
#if ZEND_MODULE_API_NO >= 20010901
    PHP_DATA_TYPES_API_EXTVER,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_DATA_TYPES_API
extern "C" {
ZEND_GET_MODULE(data_types_api)
}
#endif
