--TEST--
CollectionsAPI: DoublyLinkedList: Handlers (data type: boolean)
--FILE--
<?php
$list = new DoublyLinkedList("boolean");
$list[]=true;
$list[]=false;
$list[]=1;
$list[]="0";
$list[1]= true;
echo "[SET/GET]: ".($list[1]==true?"OK":"NOK")."\n";
echo "SIZE: ".($list->size()==4?"OK":"NOK")."\n";
echo "IS_EMPTY: ".($list->isEmpty()==false?"OK":"NOK")."\n";
echo "CONTAINS_INDEX: ".($list->containsIndex(1)==true?"OK":"NOK")."\n";
echo "CONTAINS_VALUE: ".($list->containsValue(true)==true?"OK":"NOK")."\n";
unset($list[1]);
echo "[UNSET]: ".($list->size()==3?"OK":"NOK")."\n";
$list[]=false;
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
bool(true)
int(1)
bool(true)
int(2)
bool(false)
int(3)
bool(false)
===DONE===
