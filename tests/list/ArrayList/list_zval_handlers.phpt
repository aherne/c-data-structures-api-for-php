--TEST--
CollectionsAPI: ArrayList: Handlers (data type: zval* object)
--FILE--
<?php
$list = new ArrayList("mixed");
$list[]=1;
$list[]=2.3;
$list[]=array("k"=>"v");
$myobj = (object) 3;
$list[]=$myobj; // obj, array, double, long
$list[1]= 3.4;
echo "[SET/GET]: ".($list[1]==3.4?"OK":"NOK")."\n";
echo "SIZE: ".($list->size()==4?"OK":"NOK")."\n";
echo "IS_EMPTY: ".($list->isEmpty()==false?"OK":"NOK")."\n";
echo "CONTAINS_INDEX: ".($list->containsIndex(1)==true?"OK":"NOK")."\n";
echo "CONTAINS_VALUE: ".($list->containsValue($myobj)==true?"OK":"NOK")."\n";
unset($list[1]);
echo "[UNSET]: ".($list->size()==3?"OK":"NOK")."\n";
$list[]=8;
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
011Array
(
    [k] => v
)
2stdClass Object
(
    [scalar] => 3
)
38===DONE===
