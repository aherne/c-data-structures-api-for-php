/*
 * map_object_iterator.h
 *
 *  Created on: Jul 10, 2016
 *      Author: aherne
 */

#ifndef CLASSES_MAP_OBJECT_ITERATOR_H_
#define CLASSES_MAP_OBJECT_ITERATOR_H_

struct map_object_iterator {
    zend_object_iterator intern;
    map_object* view;
    void* iterator;
    size_t offset;
    zval* current;
};

#endif /* CLASSES_MAP_OBJECT_ITERATOR_H_ */
