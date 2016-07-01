--TEST--
CollectionsAPI: DoublyLinkedList: Handlers (data type: long)
--FILE--
<?php
$list = new DoublyLinkedList("integer");
$list[]=14;
$list[]=8;
$list[]="2";
$list[1]= 10;
echo "[SET/GET]: ".($list[1]==10?"OK":"NOK")."\n";
echo "SIZE: ".($list->size()==3?"OK":"NOK")."\n";
echo "IS_EMPTY: ".($list->isEmpty()==false?"OK":"NOK")."\n";
echo "CONTAINS_INDEX: ".($list->containsIndex(1)==true?"OK":"NOK")."\n";
echo "CONTAINS_VALUE: ".($list->containsValue(2)==true?"OK":"NOK")."\n";
unset($list[1]);
echo "[UNSET]: ".($list->size()==2?"OK":"NOK")."\n";
$list[]=245;
foreach($list as $k=>$v) {
	var_dump($k);
	var_dump($v);
}
?>
===DONE===
<?php exit(0); ?>
--EXPECTF--
[SET/GET]: OK
SIZE: OK
IS_EMPTY: OK
CONTAINS_INDEX: OK
CONTAINS_VALUE: OK
[UNSET]: OK
int(0)
int(14)
int(1)
int(2)
int(2)
int(245)
===DONE===
