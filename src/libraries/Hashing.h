/*
 * Hashing.h
 *
 *  Created on: Mar 2, 2016
 *      Author: lucian p
 */

#ifndef SRC_HASHING_H_
#define SRC_HASHING_H_
#include <stdexcept>

template<typename T>
struct hash {
	std::size_t operator()(const T& item) const {
		throw std::out_of_range("No key/value hashing function found!");
		return 0;
	}
};

template<>
struct hash<long> {
	std::size_t operator()(const long& item) const {
		return item;
	}
};

template<>
struct hash<char> {
	std::size_t operator()(const char& item) const {
		return item;
	}
};

template<>
struct hash<double> {
	std::size_t operator()(const double& item) const {
		return item;
	}
};

template<>
struct hash<zval*> {
	std::size_t operator()(zval*& object) const {
		zval *retval = NULL;
		zend_call_method_with_0_params(&object, NULL, NULL, "getHash", &retval);
		long response;
		convert_to_long_ex(&retval);
		response = Z_LVAL_P(retval);
		zval_ptr_dtor(&retval);
		return response;
	}
};

template<>
struct hash<char*> {
	std::size_t operator()(const char* item) const {
		unsigned long hash = 5381;
		int c;

		while ((c = *item++)) {
			hash = ((hash << 5) + hash) + c;
		}

		return hash;
	}
};



#endif /* SRC_HASHING_H_ */
