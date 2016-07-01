/*
 * list_object_iterator.h
 *
 *  Created on: Jun 25, 2016
 *      Author: aherne
 */

#ifndef CLASSES_LIST_OBJECT_ITERATOR_H_
#define CLASSES_LIST_OBJECT_ITERATOR_H_

struct list_object_iterator {
    zend_object_iterator intern;
    list_object* view;
    size_t offset;
    zval* current;
};

#endif /* CLASSES_LIST_OBJECT_ITERATOR_H_ */
