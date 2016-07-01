--TEST--
CollectionsAPI: LinkedList: Handlers (data type: string)
--FILE--
<?php
$list = new LinkedList("string");
$list[]="xox";
$list[]=12.1;
$list[]="8";
$list[1]= "44.6";
echo "ADD/SET/GET: ".($list[0]=="xox"?"OK":"NOK")."\n";
echo "SIZE: ".($list->size()==3?"OK":"NOK")."\n";
echo "IS_EMPTY: ".($list->isEmpty()==false?"OK":"NOK")."\n";
echo "CONTAINS_INDEX: ".($list->containsIndex(1)==true?"OK":"NOK")."\n";
echo "CONTAINS_VALUE: ".($list->containsValue(44.6)==true?"OK":"NOK")."\n";
unset($list[1]);
echo "[UNSET]: ".($list->size()==2?"OK":"NOK")."\n";
$list[]="lux";
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
string(3) "xox"
int(1)
string(1) "8"
int(2)
string(3) "lux"
===DONE===
