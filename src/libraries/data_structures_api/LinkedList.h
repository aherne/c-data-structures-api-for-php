/*
 * LinkedList.h
 *
 *  Created on: Apr 17, 2016
 *      Author: aherne
 */

#ifndef LIST_LINKEDLIST_H_
#define LIST_LINKEDLIST_H_

#include "../Comparator.h"
#include "List.h"

template<typename T>
struct LinkedListEntry {
	T value;
	LinkedListEntry* next;
};

template<typename T>
class LinkedList: public List<T> {
	public:

		LinkedList() {
			head = nullptr;
			tail = nullptr;
			currentItem = nullptr;
			currentIndex = 0;
			count = 0;
		}

		~LinkedList() {
			empty();
		}

		const T& operator[](const size_t& index) const {
			traverse(index);

			return currentItem->value;
		}

		void clear() {
			empty();

			head = nullptr;
			tail = nullptr;
			currentItem = nullptr;
			currentIndex = 0;
			count = 0;
		}

		void addToTop(const T& value) {
			// reset internal iterator
			currentIndex = 0;
			currentItem = nullptr;

			// add element
			LinkedListEntry<T>* element = new LinkedListEntry<T>;
			element->value = value;
			element->next = head;
			head = element;
			if(tail==nullptr) tail = head;

			// increment counter
			++ count;
		}

		void addToBottom(const T& value) {
			// reset internal iterator
			currentIndex = 0;
			currentItem = nullptr;

			// add element
			LinkedListEntry<T>* newNode = new LinkedListEntry<T>;
			newNode->value = value;
			newNode->next = nullptr;
			if(count==0) {
				head = newNode;
				tail = head;
			} else {
				tail->next = newNode;
				tail = newNode;
			}

			// increment counter
			++ count;
		}

		const T& get(const size_t& index) const {
			if(index>=count) throw std::out_of_range("Index must already exist!");

			traverse(index);

			return currentItem->value;
		}

		void set(const size_t& index, const T& value) {
			if(index>=count) throw std::out_of_range("Index must already exist!");

			traverse(index);

			currentItem->value = value;
		}

		void emplace(const size_t& index, const T& value) {
			if(index>count) throw std::out_of_range("Index cannot exceed list length!");

			if(index==0) {
				addToTop(value);

				currentIndex = 0;
				currentItem = head;
			} else if(index==count) {
				addToBottom(value);

				currentIndex = index;
				currentItem = tail;
			} else {
				std::size_t i = 0;
				LinkedListEntry<T>* temp = head;
				if(currentItem!=nullptr && index>currentIndex) {
					i = currentIndex;
					temp = currentItem;
				}
				while(temp!=nullptr) {
					if((i+1)==index) {
						LinkedListEntry<T>* newNode = new LinkedListEntry<T>;
						newNode->value = value;
						newNode->next = temp->next;

						temp->next = newNode;

						currentIndex = index;
						currentItem = newNode;

						++ count;
						return;
					}
					temp = temp->next;
					++i;
				}
			}
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
			LinkedListEntry<T>* temp = head;
			while(temp!=nullptr) {
				if(valueComparator(temp->value, value)==0) {
					return true;
				}
				temp = temp->next;
			}
			return false;
		}

		void removeIndex(const size_t& index) {
			if(index>=count) throw std::out_of_range("Index must already exist!");

			if(index==0) {
				deleteHead();
			} else {
				traverse(index-1);
				deleteNextItem();
			}
		}

		void removeValue(const T& value) {
			if(count==0) return;

			std::size_t oldCount = count;
			LinkedListEntry<T>* temp = head;
			std::size_t position = 0;
			while(temp!=nullptr) {
				if(temp == head) {
					if(valueComparator(temp->value, value)==0) {
						deleteHead();
						temp = head;
					}
				} else {
					if(temp->next!=nullptr) {
						if(valueComparator(temp->next->value, value)==0) {
							currentIndex = position;
							currentItem = temp;
							deleteNextItem();
							temp = currentItem;
						}
					}
				}


				temp = temp->next;
				++ position;
			}

			if(oldCount == count) throw std::out_of_range("Value not found!");
		}
	private:

		void deleteHead() {
			LinkedListEntry<T>* temp = head->next;
			delete head;
			head = temp;
			if(temp==nullptr) tail = nullptr;
			currentIndex = 0;
			currentItem = temp;
			-- count;
		}

		void deleteNextItem() {
			LinkedListEntry<T>* nextItem = currentItem->next;
			currentItem->next = nextItem->next;

			if(nextItem==tail) tail = currentItem;

			delete nextItem;

			-- count;
		}

		void traverse(const size_t& index) const {
			std::size_t i = 0;
			LinkedListEntry<T>* temp = head;
			if(currentItem!=nullptr && index>=currentIndex) {
				i = currentIndex;
				temp = currentItem;
			}
			while(temp!=nullptr) {
				if(i==index) {
					currentIndex = index;
					currentItem = temp;
					return;
				}
				temp = temp->next;
				++i;
			}
		}

		void empty(){
			LinkedListEntry<T>* temp = head;
			LinkedListEntry<T>* del = temp;
			while(del != nullptr) {
				temp = temp->next;
				delete del;
				del = temp;
			}
		}

		LinkedListEntry<T>* head;
		LinkedListEntry<T>* tail;
		std::size_t count;
		comparator<T> valueComparator;

		// for fast get/set iteration
		mutable std::size_t currentIndex;
		mutable LinkedListEntry<T>* currentItem;
};

template<>
class LinkedList<zval*>: public List<zval*> {
	public:
		LinkedList() {
			head = nullptr;
			tail = nullptr;
			currentItem = nullptr;
			currentIndex = 0;
			count = 0;
		}

		~LinkedList() {
			empty();
		}

		zval*& operator[](const size_t& index) const {
			traverse(index);
			return currentItem->value;
		}

		void clear() {
			empty();

			head = nullptr;
			tail = nullptr;
			currentItem = nullptr;
			currentIndex = 0;
			count = 0;
		}

		void addToTop(zval*& value) {
	    	Z_ADDREF_P(value);

			// reset internal iterator
			currentIndex = 0;
			currentItem = nullptr;

			// add element
			LinkedListEntry<zval*>* element = new LinkedListEntry<zval*>;
			element->value = value;
			element->next = head;
			head = element;
			if(tail==nullptr) tail = head;

			// increment counter
			++ count;
		}

		void addToBottom(zval*& value) {
	    	Z_ADDREF_P(value);

			// reset internal iterator
			currentIndex = 0;
			currentItem = nullptr;

			// add element
			LinkedListEntry<zval*>* newNode = new LinkedListEntry<zval*>;
			newNode->value = value;
			newNode->next = nullptr;
			if(count==0) {
				head = newNode;
				tail = head;
			} else {
				tail->next = newNode;
				tail = newNode;
			}

			// increment counter
			++ count;
		}

		zval*& get(const size_t& index) const {
			if(index>=count) throw std::out_of_range("Index must already exist!");

			traverse(index);

			return currentItem->value;
		}

		void set(const size_t& index, zval*& value) {
			if(index>=count) throw std::out_of_range("Index must already exist!");
	    	Z_ADDREF_P(value);

			traverse(index);

			zval_ptr_dtor(&(currentItem->value));

			currentItem->value = value;
		}

		void emplace(const size_t& index, zval*& value) {
			if(index>count) throw std::out_of_range("Index cannot exceed list length!");
	    	Z_ADDREF_P(value);

			if(index==0) {
				addToTop(value);

				currentIndex = 0;
				currentItem = head;
			} else if(index==count) {
				addToBottom(value);

				currentIndex = index;
				currentItem = tail;
			} else {
				std::size_t i = 0;
				LinkedListEntry<zval*>* temp = head;
				if(currentItem!=nullptr && index>currentIndex) {
					i = currentIndex;
					temp = currentItem;
				}
				while(temp!=nullptr) {
					if((i+1)==index) {
						LinkedListEntry<zval*>* newNode = new LinkedListEntry<zval*>;
						newNode->value = value;
						newNode->next = temp->next;

						temp->next = newNode;

						currentIndex = index;
						currentItem = newNode;

						++ count;
						return;
					}
					temp = temp->next;
					++i;
				}
			}
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
			LinkedListEntry<zval*>* temp = head;
			while(temp!=nullptr) {
				if(valueComparator(temp->value, value)==0) {
					return true;
				}
				temp = temp->next;
			}
			return false;
		}

		void removeIndex(const size_t& index) {
			if(index>=count) throw std::out_of_range("Index must already exist!");

			if(index==0) {
				deleteHead();
			} else {
				traverse(index-1);
				deleteNextItem();
			}
		}

		void removeValue(zval*& value) {
			if(count==0) return;

			std::size_t oldCount = count;
			LinkedListEntry<zval*>* temp = head;
			std::size_t position = 0;
			while(temp!=nullptr) {
				if(temp == head) {
					if(valueComparator(temp->value, value)==0) {
						deleteHead();
						temp = head;
					}
				} else {
					if(temp->next!=nullptr) {
						if(valueComparator(temp->next->value, value)==0) {
							currentIndex = position;
							currentItem = temp;
							deleteNextItem();
							temp = currentItem;
						}
					}
				}


				temp = temp->next;
				++ position;
			}

			if(oldCount == count) throw std::out_of_range("Value not found!");
		}
	private:

		void deleteHead() {
			LinkedListEntry<zval*>* temp = head->next;
			remove(head);
			head = temp;
			if(temp==nullptr) tail = nullptr;
			currentIndex = 0;
			currentItem = temp;
			-- count;
		}

		void deleteNextItem() {
			LinkedListEntry<zval*>* nextItem = currentItem->next;
			currentItem->next = nextItem->next;

			if(nextItem==tail) tail = currentItem;

			remove(nextItem);

			-- count;
		}
		void traverse(const size_t& index) const {
			std::size_t i = 0;
			LinkedListEntry<zval*>* temp = head;
			if(currentItem!=nullptr && index>=currentIndex) {
				i = currentIndex;
				temp = currentItem;
			}
			while(temp!=nullptr) {
				if(i==index) {
					currentIndex = index;
					currentItem = temp;
					return;
				}
				temp = temp->next;
				++i;
			}
		}

		void empty(){
			LinkedListEntry<zval*>* temp = head;
			LinkedListEntry<zval*>* del = temp;
			while(del != nullptr) {
				temp = temp->next;
				remove(del);
				del = temp;
			}
		}

		void remove(LinkedListEntry<zval*>*& element) {
			zval_ptr_dtor(&(element->value));
			delete element;
		}

		LinkedListEntry<zval*>* head;
		LinkedListEntry<zval*>* tail;
		std::size_t count;
		comparator<zval*> valueComparator;

		// for fast get/set iteration
		mutable std::size_t currentIndex;
		mutable LinkedListEntry<zval*>* currentItem;
};

#endif /* LIST_LINKEDLIST_H_ */
