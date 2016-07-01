/*
 * MemoryManager.h
 *
 *  Created on: Dec 10, 2015
 *      Author: aherne
 */

#ifndef SRC_MEMORYMANAGER_H_
#define SRC_MEMORYMANAGER_H_

#include <vector>

template<typename T>
class MemoryManager {
public:
	MemoryManager(){

	}

	~MemoryManager() {
		for(auto it=contents.begin(); it!=contents.end(); ++it) {
			free(*it);
		}
	}

	void add(T& elem) {
		contents.push_back(elem);
	}

	void add(const T& elem) {
		contents.push_back(elem);
	}

	void clear() {
		for(auto it=contents.begin(); it!=contents.end(); ++it) {
			free(*it);
		}
		contents.clear();
	}
private:
	std::vector<T> contents;
};



#endif /* SRC_MEMORYMANAGER_H_ */
