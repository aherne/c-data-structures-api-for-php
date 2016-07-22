/*
 * conversions.h
 *
 *  Created on: Nov 17, 2015
 *      Author: aherne
 */

#ifndef SRC_CONVERSIONS_H_
#define SRC_CONVERSIONS_H_
#include <limits>
#include <stdexcept>
#include <iostream>

static inline long str2long(char*& s) {
    char* end;
    if (s[0] == '\0' || isspace(s[0]))
        throw std::runtime_error("Value must be of integer type!");
    long l = strtol(s, &end, 10);
    if (l > INT_MAX || (errno == ERANGE && l == LONG_MAX))
        throw std::runtime_error("Value must be of integer type!");
    if (l < INT_MIN || (errno == ERANGE && l == LONG_MIN))
        throw std::runtime_error("Value must be of integer type!");
    if (*end != '\0')
        throw std::runtime_error("Value must be of integer type!");
    return l;
}

static inline double str2double(char*& s) {
    char* end;
    if (s[0] == '\0' || isspace(s[0]))
        throw std::runtime_error("Value must be of numeric type!");
    double l = strtod(s, &end);
    if (l > INT_MAX || (errno == ERANGE && l == LONG_MAX))
        throw std::runtime_error("Value must be of numeric type!");
    if (l < INT_MIN || (errno == ERANGE && l == LONG_MIN))
        throw std::runtime_error("Value must be of numeric type!");
    if (*end != '\0')
        throw std::runtime_error("Value must be of numeric type!");
    return l;
}

static inline char zval2bool(zval*& value) {
	if(Z_TYPE_P(value)==IS_BOOL) {
		return Z_LVAL_P(value);
	} else if(Z_TYPE_P(value)==IS_LONG) {
		if(Z_LVAL_P(value)==1) {
			return 1;
		} else if(Z_LVAL_P(value)==0) {
			return 0;
		} else {
			throw std::runtime_error("Value must be of boolean type!");
		}
	} else if(Z_TYPE_P(value)==IS_STRING) {
		if(strcmp(Z_STRVAL_P(value),"1")==0 || strcmp(Z_STRVAL_P(value),"true")==0) {
			return 1;
		} else if (strcmp(Z_STRVAL_P(value),"0")==0 || strcmp(Z_STRVAL_P(value),"false")==0) {
			return 0;
		} else {
			throw std::runtime_error("Value must be of boolean type!");
		}
	} else {
		throw std::runtime_error("Value must be of boolean type!");
	}
	return 0;
}

static inline double zval2double(zval*& value) {
	if(Z_TYPE_P(value)==IS_DOUBLE) {
		return Z_DVAL_P(value);
	} else if(Z_TYPE_P(value)==IS_LONG) {
		return (double)Z_LVAL_P(value);
	} else if(Z_TYPE_P(value)==IS_STRING) {
		return str2double(Z_STRVAL_P(value));
	} else {
		throw std::runtime_error("Value must be of numeric type!");
	}
}

static inline long zval2long(zval*& value) {
	if(Z_TYPE_P(value)==IS_LONG) {
		return Z_LVAL_P(value);
	} else if(Z_TYPE_P(value)==IS_STRING) {
		return str2long(Z_STRVAL_P(value));
	} else {
		throw std::runtime_error("Value must be of integer type!");
	}
}

static inline char* zval2str(zval*& value, MemoryManager<char*>*& mm) {
	if(Z_TYPE_P(value)==IS_STRING) {
	} else if(Z_TYPE_P(value)==IS_LONG) {
		Z_STRLEN_P(value) = zend_spprintf(&Z_STRVAL_P(value), 0, "%ld", Z_LVAL_P(value));
		Z_TYPE_P(value) = IS_STRING;
	} else if(Z_TYPE_P(value)==IS_DOUBLE) {
		Z_STRLEN_P(value) = zend_spprintf(&Z_STRVAL_P(value), 0, "%.*G", (int) EG(precision), Z_DVAL_P(value));
		Z_TYPE_P(value) = IS_STRING;
	} else {
		throw std::runtime_error("Value must be of numeric or string type!");
	}

	if(IS_INTERNED(Z_STRVAL_P(value))) {
		return Z_STRVAL_P(value);
	} else {
		int newLength = Z_STRLEN_P(value)+1;
		char* temp = (char*) malloc(newLength);
		memcpy(temp, Z_STRVAL_P(value), newLength);
		mm->add(temp);
		return temp;
	}
}

static inline zval*& zval2object(zval*& value, zend_class_entry*& class_entry) {
	if(Z_TYPE_P(value)!=IS_OBJECT) {
		throw std::runtime_error("Value must be object!");
	}
	if(!instanceof_function(class_entry, Z_OBJCE_P(value))) {
		char result[100]= "Value must be instance of: ";
		strcat(result,class_entry->name);
		throw std::runtime_error(result);
	}
	return value;
}

static inline zval* long2zval(const long& value) {
	zval* retval;
	ALLOC_INIT_ZVAL(retval);
	Z_TYPE_P(retval) = IS_LONG;
	Z_LVAL_P(retval) = value;
	return retval;
}

static inline zval* str2zval(char* const& value) {
	zval* retval;
	ALLOC_INIT_ZVAL(retval);
	Z_TYPE_P(retval) = IS_STRING;
	Z_STRVAL_P(retval) = estrdup(value);
	Z_STRLEN_P(retval) = strlen(value);
	return retval;
}

static inline zval* double2zval(const double& value) {
	zval* retval;
	ALLOC_INIT_ZVAL(retval);
	Z_TYPE_P(retval) = IS_DOUBLE;
	Z_DVAL_P(retval) = value;
	return retval;
}

static inline zval* bool2zval(const char& value) {
	zval* retval;
	ALLOC_INIT_ZVAL(retval);
	Z_TYPE_P(retval) = IS_BOOL;
	Z_LVAL_P(retval) = value;
	return retval;
}
#endif /* SRC_CONVERSIONS_H_ */
