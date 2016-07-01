--TEST--
CollectionsAPI: DoublyLinkedList: Methods (data type: double)
--FILE--
<?php
$list = new DoublyLinkedList("double");
$list->addToBottom(14.3);
$list->addToBottom(8.1);
$list->addToTop(2); 
$list->addToTop("11.2"); 
echo "ADD/GET: ".($list->get(3)==8.1?"OK":"NOK")."\n";
$list->emplace(0,"10"); // true, true, false, true, false
echo "EMPLACE: ".($list->get(0)==10?"OK":"NOK")."\n";
$list->set(2, 144.6);	// true, true, false, true, false
echo "SET: ".($list->get(2)==144.6?"OK":"NOK")."\n";
echo "SIZE: ".($list->size()==5?"OK":"NOK")."\n";
echo "IS_EMPTY: ".($list->isEmpty()==false?"OK":"NOK")."\n";
echo "CONTAINS_INDEX: ".($list->containsIndex(1)==true?"OK":"NOK")."\n";
echo "CONTAINS_VALUE: ".($list->containsValue("8.1")==true?"OK":"NOK")."\n";
$list->removeIndex(3);
echo "REMOVE_INDEX: ".($list->size()==4?"OK":"NOK")."\n";
$list->removeValue(8.1);
echo "REMOVE_VALUE ".($list->size()==3?"OK":"NOK")."\n";
$list->addToBottom(16.9);
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
    [0] => 10
    [1] => 11.2
    [2] => 144.6
    [3] => 16.9
)
CLEAR: OK
===DONE===
