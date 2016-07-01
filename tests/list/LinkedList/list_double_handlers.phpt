--TEST--
CollectionsAPI: LinkedList: Handlers (data type: double)
--FILE--
<?php
$list = new LinkedList("double");
$list[]=14;
$list[]=12.1;
$list[]="8";
$list[1]= "44.6";
echo "ADD/SET/GET: ".($list[1]==44.6?"OK":"NOK")."\n";
echo "SIZE: ".($list->size()==3?"OK":"NOK")."\n";
echo "IS_EMPTY: ".($list->isEmpty()==false?"OK":"NOK")."\n";
echo "CONTAINS_INDEX: ".($list->containsIndex(1)==true?"OK":"NOK")."\n";
echo "CONTAINS_VALUE: ".($list->containsValue(44.6)==true?"OK":"NOK")."\n";
unset($list[1]);
echo "[UNSET]: ".($list->size()==2?"OK":"NOK")."\n";
$list[]=24.5;
foreach($list as $k=>$v) {
	var_dump($k);
	var_dump($v);
}
?>
===DONE===
<?php exit(0); ?>
--EXPECTF--
ADD/SET/GET: OK
SIZE: OK
IS_EMPTY: OK
CONTAINS_INDEX: OK
CONTAINS_VALUE: OK
[UNSET]: OK
int(0)
float(14)
int(1)
float(8)
int(2)
float(24.5)
===DONE===
