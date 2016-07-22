/*
 * ListZendInterface.h
 *
 *  Created on: Nov 12, 2015
 *      Author: aherne
 */

#ifndef SRC_ZEND_CLASSES_LISTZENDINTERFACE_H_
#define SRC_ZEND_CLASSES_LISTZENDINTERFACE_H_

class ZendInterface {
public:
	ZendInterface(const char name[], const zend_function_entry methods[]);
	~ZendInterface();
	zend_class_entry* getInterfaceEntry();
private:
	zend_class_entry *interface_ce;
};

#endif /* SRC_ZEND_CLASSES_LISTZENDINTERFACE_H_ */
