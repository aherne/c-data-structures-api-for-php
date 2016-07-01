/*
 * Validators.h
 *
 *  Created on: Jun 6, 2016
 *      Author: aherne
 */

#ifndef LIBRARIES_VALIDATORS_H_
#define LIBRARIES_VALIDATORS_H_

template<typename T>
T validateSet(zval*& value) {
	return;
}

template<>
zval*& validateSet(zval*& value) {
	return value;
}


template<typename T>
struct validateGet {
    void operator()(zval*& value) {
    	return;
    }
};

template<>
struct validateGet<zval*> {
    zval*& operator()(zval*& value) {
    	return value;
    }
};


#endif /* LIBRARIES_VALIDATORS_H_ */
