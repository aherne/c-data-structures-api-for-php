/*
 * List.h
 *
 *  Created on: Apr 17, 2016
 *      Author: aherne
 */

#ifndef LIST_LIST_H_
#define LIST_LIST_H_

#include <stdlib.h>
#include <algorithm>

template<typename T>
class List {
public:
	virtual ~List() {}
	virtual const T& operator[](const size_t& index) const=0;

	virtual void clear()=0;
	virtual void addToTop(const T& value)=0;
	virtual void addToBottom(const T& value)=0;
	virtual const T& get(const size_t& index) const =0;
	virtual void set(const size_t& index, const T& value)=0;
	virtual void emplace(const size_t& index, const T& value)=0;
	virtual bool isEmpty() const = 0;
	virtual const std::size_t& size() const = 0;
	virtual bool containsIndex(const size_t& index) const = 0;
	virtual bool containsValue(const T& value) const = 0;
	virtual void removeIndex(const size_t& index) = 0;
	virtual void removeValue(const T& value) = 0;
};

template<>
class List<zval*> {
public:
	virtual ~List() {}
	virtual zval*& operator[](const size_t& index) const=0;

	virtual void clear()=0;
	virtual void addToTop(zval*& value)=0;
	virtual void addToBottom(zval*& value)=0;
	virtual zval*& get(const size_t& index) const=0;
	virtual void set(const size_t& index, zval*& value)=0;
	virtual void emplace(const size_t& index, zval*& value)=0;
	virtual bool isEmpty() const = 0;
	virtual const std::size_t& size() const = 0;
	virtual bool containsIndex(const size_t& index) const = 0;
	virtual bool containsValue(zval*& value) const = 0;
	virtual void removeIndex(const size_t& index) = 0;
	virtual void removeValue(zval*& value) = 0;
};
#endif /* LIST_LIST_H_ */
