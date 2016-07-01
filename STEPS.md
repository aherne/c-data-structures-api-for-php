Implementation Guide
______________________________________________________________________________________________________________________________________________________________________________________

HEADERS
______________________________________________________________________________________________________________________________________________________________________________________
LIST: template specialization for zval* and char*
	char validateSet(zval*& value) {					T (*validateSet)(zval*& value);
	long validateSet(zval*& value) {					T (*validateSet)(zval*& value);
 	double validateSet(zval*& value) {				T (*validateSet)(zval*& value);
	char* validateSet(zval*& value) {				T (*validateSet)(zval*& value);
	zval*& validateSet(zval*& value) {	!!!@mixed	T& (*validateSet)(zval*& value);
	zval*& validateSet(zval*& value) {	!!!@object	T& (*validateSet)(zval*& value);
	zval* validateGet(const char& value) {			zval* (*validateGet)(const T& value);
	zval* validateGet(const double& value) {			zval* (*validateGet)(const T& value);
	zval* validateGet(const long& value) {			zval* (*validateGet)(const T& value);
	zval* validateGet(char*& value) {				zval* (*validateGet)(T& value);
	zval*& validateGet(zval*& value) {				zval*& (*validateGet)(T& value);

SET: same as list

MAP: same as list: validateSetKey/validateGetKey/validateSetValue/validateGetValue +:
	void validateGetKey(const long& value, zval*& retval) {		T (*validateGetKey)(const T& value, zval*& retval);
	void validateGetKey(char*& value, zval*& retval) {			T (*validateGetKey)(T& value, zval*& retval);
	...
______________________________________________________________________________________________________________________________________________________________________________________

SOURCES:
______________________________________________________________________________________________________________________________________________________________________________________

LIST:
different constructors and destructors (by type of value and type of list)
	@string (!!!): Solution use a class instead of struct with constructor and destructor
		constructor: initialize memory manager
		destructor & clear: destroy memory manager
List::get
	RETURN_BOOL(obj->object->get(index));
	RETURN_DOUBLE(obj->object->get(index));
	RETURN_LONG(obj->object->get(index));
	RETURN_STRING(obj->object->get(index),1);
	RETURN_ZVAL(obj->object->get(index),1,0);
List::toValue
	add_next_index_bool(return_value,*it);
	add_next_index_double(return_value,*it);
	add_next_index_long(return_value,*it);
	add_next_index_string(return_value,*it,1);
	Z_ADDREF_P(*it);
	add_next_index_zval(return_value,*it);
List::sort (! logic differs according to type, but it's not an essential operation)

SET:
same observations as to list, only that Set::get doesn't exist

MAP:
Map::get
	RETURN_BOOL(obj->object->get(obj->validateSetKey(key)));
	...
Map::getValues
	add_next_index_bool(return_value, (*it)->second);
	...
	Z_ADDREF_P((*it)->second);
	add_next_index_zval(return_value, (*it)->second);
Map::getKeys
	add_next_index_bool(return_value, (*it)->first); @ long key
	add_next_index_string(return_value, (*it)->first, 1); @ string key
	...
Map::toValue
	add_index_bool(return_value, (*it)->first, (*it)->second); @ long key
	add_assoc_bool(return_value, (*it)->first, (*it)->second); @ string key
	...
	Z_ADDREF_P((*it)->second);
    add_index_zval(return_value, (*it)->first, (*it)->second); @ long key
    add_assoc_zval(return_value, (*it)->first, (*it)->second); @ string key
    
