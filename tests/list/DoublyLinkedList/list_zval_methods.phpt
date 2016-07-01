--TEST--
CollectionsAPI: DoublyLinkedList: Methods (data type: zval* object)
--FILE--
<?php
$list = new DoublyLinkedList("mixed");
$list->addToBottom(1);
$list->addToBottom(2.3);
$list->addToTop(array("k"=>"v"));
$myobj = (object) 3;
$list->addToTop($myobj); // obj, array, double, long
echo "ADD/GET: ".($list->get(3)==2.3?"OK":"NOK")."\n";
$list->emplace(1,23);
echo "EMPLACE: ".($list->get(1)==23?"OK":"NOK")."\n";
$list->set(2, 3.4);
echo "SET: ".($list->get(2)==3.4?"OK":"NOK")."\n";
echo "SIZE: ".($list->size()==5?"OK":"NOK")."\n";
echo "IS_EMPTY: ".($list->isEmpty()==false?"OK":"NOK")."\n";
echo "CONTAINS_INDEX: ".($list->containsIndex(1)==true?"OK":"NOK")."\n";
echo "CONTAINS_VALUE: ".($list->containsValue($myobj)==true?"OK":"NOK")."\n";
$list->removeIndex(3);
echo "REMOVE_INDEX: ".($list->size()==4?"OK":"NOK")."\n";
$list->removeValue(2.3);
echo "REMOVE_VALUE ".($list->size()==3?"OK":"NOK")."\n";
$list->addToBottom(8);
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
    [0] => stdClass Object
        (
            [scalar] => 3
        )

    [1] => 23
    [2] => 3.4
    [3] => 8
)
CLEAR: OK
===DONE===
