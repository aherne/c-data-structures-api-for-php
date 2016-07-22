/*
 * comparable_interface.h
 *
 *  Created on: Jul 22, 2016
 *      Author: aherne
 */

#ifndef CLASSES_COMPARABLE_INTERFACE_H_
#define CLASSES_COMPARABLE_INTERFACE_H_

#include "../common.h"

const char comparable_interface_name[] = "Comparable";

const zend_function_entry comparable_interface_methods[] = {
    PHP_ABSTRACT_ME(Comparable,  compareTo,        NULL)
    {NULL, NULL, NULL}
};



#endif /* CLASSES_COMPARABLE_INTERFACE_H_ */
