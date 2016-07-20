/*
 * ArrayList.h
 *
 *  Created on: Apr 17, 2016
 *      Author: aherne
 */

#ifndef LIST_ARRAYLIST_H_
#define LIST_ARRAYLIST_H_

#include "../Comparator.h"
#include "List.h"

template<typename T>
class ArrayList: public List<T> {
public:
	ArrayList() {
		maximum_size = 8;
		contents = (T*) malloc(maximum_size*sizeof(T));
		count = 0;
	}

	~ArrayList() {
		free(contents);
	}

	const T& operator[](const size_t& index) const {
		return contents[index];
	}

	void clear() {
		free(contents);

		maximum_size = 8;
		contents = (T*) malloc(maximum_size*sizeof(T));
		count = 0;

	}

	void addToBottom(const T& value) {
		if(count == maximum_size) {
			resize();
		}
		contents[count] = value;
		++count;
	}

	void addToTop(const T& value) {
		if(count == maximum_size) {
			resize();
		}
		for(std::size_t i = count; i>0; --i) {
			contents[i]=contents[i-1];
		}
		contents[0] = value;
		++ count;
	}

	const T& get(const size_t& index) const {
		if(index>=count) throw std::out_of_range("Index must already exist!");
		return contents[index];
	}

	void set(const size_t& index, const T& value) {
		if(index>=count) throw std::out_of_range("Index must already exist!");
		contents[index] = value;
	}

	void emplace(const size_t& index, const T& value) {
		if(index>count) throw std::out_of_range("Index cannot exceed list length!");
		if(count == maximum_size) {
			resize();
		}
		for(std::size_t i = count; i>index; --i) {
			contents[i]=contents[i-1];
		}
		contents[index] = value;
		++ count;
	}

	bool isEmpty() const {
		return count==0;
	}

	const std::size_t& size() const {
		return count;
	}

	bool containsIndex(const size_t& index) const {
		return (index>=count?false:true);
	}

	bool containsValue(const T& value) const {
		for(std::size_t i=0; i<count; ++i) {
			if(valueComparator(contents[i], value)==0) {
				return true;
			}
		}
		return false;
	}

	void removeIndex(const size_t& index) {
		if(index>=count) throw std::out_of_range("Index must already exist!");
		for(std::size_t j=index; j< count; ++j) {
			if((j+1)!=count) {
				contents[j] = contents[j+1];
			}
		}
		--count;
	}

	void removeValue(const T& value) {
		int reduce = 0;
		for(std::size_t j=0; j< count; ++j) {
			if(valueComparator(contents[j], value)==0) {
				reduce ++;
			} else {
				if(reduce>0) {
					contents[j-reduce] = contents[j];
				}
			}
		}
		if(reduce==0) throw std::out_of_range("Value must already exist!");
		count -= reduce;
	}

	T* begin() {
		if(count==0) return nullptr;
		return &contents[0];
	}

	T* end() {
		return &contents[count];
	}
private:
	void resize() {
		maximum_size = 2*maximum_size;
		contents = (T*) realloc(contents, maximum_size*sizeof(T));
	}

	std::size_t maximum_size;
	std::size_t count;
	T* contents;

	comparator<T> valueComparator;
};


template<>
class ArrayList<zval*>: public List<zval*> {
public:
	ArrayList() {
		maximum_size = 8;
		contents = (zval**) malloc(maximum_size*sizeof(zval*));
		count = 0;
	}

	~ArrayList() {
		for(size_t i=0; i<count; ++i) {
			zval_ptr_dtor(&(contents[i]));
		}
		free(contents);
	}

	zval*& operator[](const size_t& index) const {
		return contents[index];
	}

	void clear() {
		for(size_t i=0; i<count; ++i) {
			zval_ptr_dtor(&(contents[i]));
		}
		free(contents);

		maximum_size = 8;
		contents = (zval**) malloc(maximum_size*sizeof(zval*));
		count = 0;

	}

	void addToBottom(zval*& value) {
    	Z_ADDREF_P(value);
		if(count == maximum_size) {
			resize();
		}
		contents[count] = value;
		++count;
	}

	void addToTop(zval*& value) {
    	Z_ADDREF_P(value);
		if(count == maximum_size) {
			resize();
		}
		for(std::size_t i = count; i>0; --i) {
			contents[i]=contents[i-1];
		}
		contents[0] = value;
		++ count;
	}

	zval*& get(const size_t& index) const {
		if(index>=count) throw std::out_of_range("Index must already exist!");
		return contents[index];
	}

	void set(const size_t& index, zval*& value) {
		if(index>=count) throw std::out_of_range("Index must already exist!");
    	Z_ADDREF_P(value);
		zval_ptr_dtor(&contents[index]);
		contents[index] = value;
	}

	void emplace(const size_t& index, zval*& value) {
		if(index>count) throw std::out_of_range("Index cannot exceed list length!");
    	Z_ADDREF_P(value);
		if(count == maximum_size) {
			resize();
		}
		for(std::size_t i = count; i>index; --i) {
			contents[i]=contents[i-1];
		}
		contents[index] = value;
		++ count;
	}

	bool isEmpty() const {
		return count==0;
	}

	const std::size_t& size() const {
		return count;
	}

	bool containsIndex(const size_t& index) const {
		return (index>=count?false:true);
	}

	bool containsValue(zval*& value) const {
		for(std::size_t i=0; i<count; ++i) {
			if(valueComparator(contents[i], value)==0) {
				return true;
			}
		}
		return false;
	}

	void removeIndex(const size_t& index) {
		if(index>=count) throw std::out_of_range("Index must already exist!");
		zval_ptr_dtor(&contents[index]);
		for(std::size_t j=index; j< count; ++j) {
			if((j+1)!=count) {
				contents[j] = contents[j+1];
			}
		}
		--count;
	}

	void removeValue(zval*& value) {
		int reduce = 0;
		for(std::size_t j=0; j< count; ++j) {
			if(valueComparator(contents[j], value)==0) {
				zval_ptr_dtor(&contents[j]);
				reduce ++;
			} else {
				if(reduce>0) {
					contents[j-reduce] = contents[j];
				}
			}
		}
		if(reduce==0) throw std::out_of_range("Value must already exist!");
		count -= reduce;
	}

	zval** begin() {
		if(count==0) return nullptr;
		return &contents[0];
	}

	zval** end() {
		return &contents[count];
	}
private:
	void resize() {
		maximum_size = 2*maximum_size;
		contents = (zval**) realloc(contents, maximum_size*sizeof(zval*));
	}

	std::size_t maximum_size;
	std::size_t count;
	zval** contents;

	comparator<zval*> valueComparator;
};

#endif /* LIST_ARRAYLIST_H_ */
