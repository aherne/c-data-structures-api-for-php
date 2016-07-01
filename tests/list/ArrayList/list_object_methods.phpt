--TEST--
CollectionsAPI: ArrayList: Methods (data type: zval*)
--FILE--
<?php
$list = new ArrayList("stdClass");
$myobj1 = (object) 1;
$list->addToBottom($myobj1);
$myobj2 = (object) 2;
$list->addToBottom($myobj2);
$myobj3 = (object) 3;
$list->addToTop($myobj3);
$myobj4 = (object) 4;
$list->addToTop($myobj4);
echo "ADD/GET: ".($list->get(3)==$myobj2?"OK":"NOK")."\n";
$myobj5 = (object) 5;
$list->emplace(1,$myobj5);
echo "EMPLACE: ".($list->get(1)==$myobj5?"OK":"NOK")."\n";
$myobj6 = (object) 6;
$list->set(2, $myobj6);
echo "SET: ".($list->get(2)==$myobj6?"OK":"NOK")."\n";
echo "SIZE: ".($list->size()==5?"OK":"NOK")."\n";
echo "IS_EMPTY: ".($list->isEmpty()==false?"OK":"NOK")."\n";
echo "CONTAINS_INDEX: ".($list->containsIndex(1)==true?"OK":"NOK")."\n";
echo "CONTAINS_VALUE: ".($list->containsValue($myobj1)==true?"OK":"NOK")."\n";
$list->removeIndex(3);
echo "REMOVE_INDEX: ".($list->size()==4?"OK":"NOK")."\n";
$list->removeValue($myobj2);
echo "REMOVE_VALUE ".($list->size()==3?"OK":"NOK")."\n";
$myobj7 = (object) 7;
$list->addToBottom($myobj7);
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
            [scalar] => 4
        )

    [1] => stdClass Object
        (
            [scalar] => 5
        )

    [2] => stdClass Object
        (
            [scalar] => 6
        )

    [3] => stdClass Object
        (
            [scalar] => 7
        )

)
CLEAR: OK
===DONE===
