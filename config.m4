PHP_ARG_ENABLE(data_types_api,
    [Whether to enable the "data_types_api" extension],
    [  --enable-data_types_api      Enable "data_types_api" extension support])
 
if test $PHP_DATA_TYPES_API != "no"; then
    PHP_REQUIRE_CXX()
    PHP_SUBST(DATA_TYPES_API_SHARED_LIBADD)
    PHP_ADD_LIBRARY(stdc++, 1, DATA_TYPES_API_SHARED_LIBADD)
	export CPPFLAGS="$CPPFLAGS $INCLUDES -std=c++11"
    PHP_NEW_EXTENSION(data_types_api, src/classes/arraylist.cpp src/classes/linkedlist.cpp src/classes/doublylinkedlist.cpp src/classes/zend_list.cpp src/classes/zend_interface.cpp data_types_api.cpp, $ext_shared)
    
fi
