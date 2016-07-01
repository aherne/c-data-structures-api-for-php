--TEST--
CollectionsAPI: DoublyLinkedList: Methods (data type: string)
--FILE--
<?php
$list = new DoublyLinkedList("string");
$list->addToBottom("xox");
$list->addToBottom(8.1);
$list->addToTop(2); 
$list->addToTop("11.2"); 
echo "ADD/GET: ".($list->get(2)=="xox"?"OK":"NOK")."\n";
$list->emplace(0,"zaz"); // true, true, false, true, false
echo "EMPLACE: ".($list->get(0)=="zaz"?"OK":"NOK")."\n";
$list->set(2, "144");
echo "SET: ".($list->get(2)==144?"OK":"NOK")."\n";
echo "SIZE: ".($list->size()==5?"OK":"NOK")."\n";
echo "IS_EMPTY: ".($list->isEmpty()==false?"OK":"NOK")."\n";
echo "CONTAINS_INDEX: ".($list->containsIndex(1)==true?"OK":"NOK")."\n";
echo "CONTAINS_VALUE: ".($list->containsValue("zaz")==true?"OK":"NOK")."\n";
$list->removeIndex(3);
echo "REMOVE_INDEX: ".($list->size()==4?"OK":"NOK")."\n";
$list->removeValue("zaz");
echo "REMOVE_VALUE ".($list->size()==3?"OK":"NOK")."\n";
$list->addToBottom("luk");
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
    [0] => 11.2
    [1] => 144
    [2] => 8.1
    [3] => luk
)
CLEAR: OK
===DONE===
