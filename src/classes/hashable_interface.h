/*
 * hashable_interface.h
 *
 *  Created on: Jul 22, 2016
 *      Author: aherne
 */

#ifndef CLASSES_HASHABLE_INTERFACE_H_
#define CLASSES_HASHABLE_INTERFACE_H_

#include "../common.h"

const char hashable_interface_name[] = "Hashable";

const zend_function_entry hashable_interface_methods[] = {
    PHP_ABSTRACT_ME(Hashable,  getHash,        NULL)
    {NULL, NULL, NULL}
};



#endif /* CLASSES_HASHABLE_INTERFACE_H_ */
