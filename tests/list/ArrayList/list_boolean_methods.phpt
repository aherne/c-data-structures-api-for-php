--TEST--
CollectionsAPI: ArrayList: Methods (data type: boolean)
--FILE--
<?php
$list = new ArrayList("boolean");
$list->addToBottom(true);
$list->addToBottom(false);
$list->addToTop(0);
$list->addToTop("1"); // true, false, true, false
echo "ADD/GET: ".($list->get(3)==false?"OK":"NOK")."\n";
$list->emplace(1,true); // true, true, false, true, false
echo "EMPLACE: ".($list->get(1)==true?"OK":"NOK")."\n";
$list->set(2, "1");	// true, true, false, true, false
echo "SET: ".($list->get(2)==true?"OK":"NOK")."\n";
echo "SIZE: ".($list->size()==5?"OK":"NOK")."\n";
echo "IS_EMPTY: ".($list->isEmpty()==false?"OK":"NOK")."\n";
echo "CONTAINS_INDEX: ".($list->containsIndex(1)==true?"OK":"NOK")."\n";
echo "CONTAINS_VALUE: ".($list->containsValue(true)==true?"OK":"NOK")."\n";
$list->removeIndex(3);
echo "REMOVE_INDEX: ".($list->size()==4?"OK":"NOK")."\n";
$list->removeValue(false);
echo "REMOVE_VALUE ".($list->size()==3?"OK":"NOK")."\n";
$list->addToBottom(true);
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
    [0] => 1
    [1] => 1
    [2] => 1
    [3] => 1
)
CLEAR: OK
===DONE===
