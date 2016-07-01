/*
 * list_interface.h
 *
 *  Created on: Jun 26, 2016
 *      Author: aherne
 */

#ifndef CLASSES_LIST_INTERFACE_H_
#define CLASSES_LIST_INTERFACE_H_

#include "../common.h"

const char list_interface_name[] = "Lists";

const zend_function_entry list_interface_methods[] = {
    PHP_ABSTRACT_ME(Lists,  addToTop,  		NULL)
    PHP_ABSTRACT_ME(Lists,  addToBottom,	NULL)
    PHP_ABSTRACT_ME(Lists,  emplace,  		NULL)
	PHP_ABSTRACT_ME(Lists,  set,           	NULL)
	PHP_ABSTRACT_ME(Lists,  get,           	NULL)
	PHP_ABSTRACT_ME(Lists,  size,           NULL)
	PHP_ABSTRACT_ME(Lists,  clear,          NULL)
	PHP_ABSTRACT_ME(Lists,  isEmpty,        NULL)
	PHP_ABSTRACT_ME(Lists,  containsIndex,  NULL)
	PHP_ABSTRACT_ME(Lists,  containsValue,  NULL)
	PHP_ABSTRACT_ME(Lists,  removeIndex,    NULL)
	PHP_ABSTRACT_ME(Lists,  removeValue,    NULL)
	PHP_ABSTRACT_ME(Lists,  toValue,        NULL)
    {NULL, NULL, NULL}
};


#endif /* CLASSES_LIST_INTERFACE_H_ */
