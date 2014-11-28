<?php
	function week2date($week,$day){
		$days=($week-1)*7+$day;
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
		if($mm>=10&&$dd>=10)
			$date=$yy.'-'.$mm.'-'.$dd;
		else if($mm<10)
			$date=$yy.'-'.'0'.$mm.'-'.$dd;
		else if($dd<10)
			$date=$yy.'-'.$mm.'-'.'0'.$dd;
		return $date;
	}
	
	require_once "../google-api-php-client/autoload.php";
	
	session_start();

	$client =new Google_Client();
	$client->setAuthConfigFile('/home/sevenyuan/client_secret.json');
	$client->addScope('https://www.googleapis.com/auth/calendar');

	if(isset($_SESSION['access_token'])&&$_SESSION['access_token']){
			$client->setAccessToken($_SESSION['access_token']);
			$service=new Google_Service_Calendar($client);

			//get color
			$i=0;
			$colors=$service->colors->get();
			foreach($colors->getEvent() as $key=>$color){
				//print "colorId : {$key}\n";
				$colorHex[$i]=$color->getBackground();
				$i++;
			}
			$nums_of_color=$i;
		if(count($_POST)==0){
			require('../include/setclass.html.inc');
		}else{
			//create short variable
			//var_dump($_POST['reminder']);
			$class_name=$_POST['class_name'];
			$class_location=$_POST['class_location'];
			$teacher=$_POST['teacher'];
			
			$calendar_id=$_POST['calendar_id'];
			settype($_POST['calendar_id'],'string');
			
			$colorid=$_POST['color'];
			$days=$_POST['days'];
			$lession=$_POST['lession'];
			$week_start=$_POST['week_start'];
			$week_end=$_POST['week_end'];
			$week_exp=explode(',',$_POST['week_exp']);

			//确定上课的周数
			$weeks=range($week_start,$week_end);
			echo '<br/>';
			if(!$week_exp){
				foreach($week_exp as $key=>$value){
					$del=array_search($value,$weeks);
					array_splice($weeks,$del,1);
				}
			}

			//作息时间
			$class_time_start=array('08:00:00','10:10:00','14:00:00',
							   		'15:55:00','18:30:00','20:15:00');
			$class_time_end=array('09:40:00','11:50:00','15:35:00',
								  '17:30:00','20:05:00','21:50:00');
			//创建课表
			$class=new Google_Service_Calendar_Event();
			$start=new Google_Service_Calendar_EventDateTime();
			$end=new Google_Service_Calendar_EventDateTime();
			foreach($weeks as $key=>$value){
				$class->setSummary($class_name);
				$class->setLocation($class_location);
				$class->setDescription("教师:".$teacher);
				
				$start_time=week2Date($value,$days).'T'.
							$class_time_start[$lession].'+08:00';
				settype($start_time,'string');
				$start->setDateTime($start_time);
				$class->setStart($start);
				
				$end_time=week2Date($value,$days).'T'.
						  $class_time_end[$lession].'+08:00';
				settype($end_time,'string');
				$end->setDateTime($end_time);
				$class->setEnd($end);
				
				$class->setColorId($colorid);

				$i=0;
				$reminder=new Google_Service_Calendar_EventReminders();
				$reminder->setUseDefault(false);
				foreach($_POST['reminder'] as $value){
					$user_reminder[$i]=array('method'=>$value,
											 'minutes'=>$_POST[$value]);
				}
				$reminder->setOverrides($user_reminder);
				$class->setReminders($reminder);

				$created_event=$service->events->insert($calendar_id,$class);
				echo $created_event->getId();
			}
			
		}
	}else{
		require"../include/signin.html.inc";
	}

?>
