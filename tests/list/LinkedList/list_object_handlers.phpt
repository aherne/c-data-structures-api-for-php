--TEST--
CollectionsAPI: LinkedList: Handlers (data type: zval*)
--FILE--
<?php
$list = new LinkedList("stdClass");
$myobj1 = (object) 1;
$list[]=$myobj1;
$myobj2 = (object) 2;
$list[]=$myobj2;
$myobj3 = (object) 3;
$list[]=$myobj3;
$myobj4 = (object) 4;
$list[]=$myobj4;
$myobj5 = (object) 5;
$list[1]= $myobj5;
echo "[SET/GET]: ".($list[1]==$myobj5?"OK":"NOK")."\n";
echo "SIZE: ".($list->size()==4?"OK":"NOK")."\n";
echo "IS_EMPTY: ".($list->isEmpty()==false?"OK":"NOK")."\n";
echo "CONTAINS_INDEX: ".($list->containsIndex(1)==true?"OK":"NOK")."\n";
echo "CONTAINS_VALUE: ".($list->containsValue($myobj4)==true?"OK":"NOK")."\n";
unset($list[1]);
echo "[UNSET]: ".($list->size()==3?"OK":"NOK")."\n";
$myobj6 = (object) 5;
$list[]=$myobj6;
foreach($list as $k=>$v) {
	print_r($k);
	print_r($v);
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
0stdClass Object
(
    [scalar] => 1
)
1stdClass Object
(
    [scalar] => 3
)
2stdClass Object
(
    [scalar] => 4
)
3stdClass Object
(
    [scalar] => 5
)
===DONE===
