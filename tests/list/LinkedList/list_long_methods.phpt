--TEST--
CollectionsAPI: LinkedList: Methods (data type: long)
--FILE--
<?php
$list = new LinkedList("integer");
$list->addToBottom(14);
$list->addToBottom(8);
$list->addToTop(2);
$list->addToTop("11"); 
echo "ADD/GET: ".($list->get(3)==8?"OK":"NOK")."\n";
$list->emplace(1,"10"); // true, true, false, true, false
echo "EMPLACE: ".($list->get(1)==10?"OK":"NOK")."\n";
$list->set(2, "112");	// true, true, false, true, false
echo "SET: ".($list->get(2)==112?"OK":"NOK")."\n";
echo "SIZE: ".($list->size()==5?"OK":"NOK")."\n";
echo "IS_EMPTY: ".($list->isEmpty()==false?"OK":"NOK")."\n";
echo "CONTAINS_INDEX: ".($list->containsIndex(1)==true?"OK":"NOK")."\n";
echo "CONTAINS_VALUE: ".($list->containsValue(112)==true?"OK":"NOK")."\n";
$list->removeIndex(3);
echo "REMOVE_INDEX: ".($list->size()==4?"OK":"NOK")."\n";
$list->removeValue(112);
echo "REMOVE_VALUE ".($list->size()==3?"OK":"NOK")."\n";
$list->addToBottom(16);
print_r($list->toValue());
$list->clear();
echo "CLEAR: ".($list->size()==0?"OK":"NOK")."\n";
?>
===DONE===
<?php exit(0); ?>
--EXPECTF--
ADD/GET: OK
EMPLACE: OK
SET: OK
SIZE: OK
IS_EMPTY: OK
CONTAINS_INDEX: OK
CONTAINS_VALUE: OK
REMOVE_INDEX: OK
REMOVE_VALUE OK
Array
(
    [0] => 11
    [1] => 10
    [2] => 8
    [3] => 16
)
CLEAR: OK
===DONE===
