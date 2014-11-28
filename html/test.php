<?php
	function week2date($week){
		$days=($week-1)*7;
		$months=array(31,28,31,30,31,30,31,31,30,31,30,31);
		$yy=2014;$mm=8;$dd=31;
		while($days>0){
			$dd++;
			if($dd>$months[$mm-1]){
				$dd=$dd-$months[$mm-1];
				$mm++;
			}
			if($mm>12){
				$yy++;
				$mm=1;
			}
			$days--;
		}
		echo $yy.'/'.$mm.'/'.$dd;
	}
	week2date(20);

?>
