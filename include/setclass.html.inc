<?php

	$calendar_list=$service->calendarList->listCalendarList();
	$i=0;
	while(true){
		foreach($calendar_list->getItems() as $calendar_entry){
			$calendar_id[$i]=$calendar_entry->getID();
			$calendar_summary[$i]=$calendar_entry->getSummary();
			$i++;
		}
		$next=$calendar_list->getNextPageToken();
		if($next){
			$opt_par=array("$PageToken"=>$next);
			$calendar_list=$service->calendarList->listcalendarlist($opt_par);
			$i=$i+1;
			//echo $i;
		}else{
			break;
		}
	}
	$nums_of_calendar=$i;
	$i=0;

?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<title>Classtable2Calendar</title>
	<link rel="stylesheet" type="text/css"href="../css/style.css">
</head>
<body>
	<div id="wrap_body">
		<header>
		<div id="wrap-header">
			<h1>Set your Class</h1>
		</div>
		</header>
	<form action="<?php $_SERVER['PHP_SELF'] ?>"method='post'>
	<div id="set_content"class="floatleft">
		课程名称: <input type='text'name='class_name'><br/>
		课程地点: <input type='text'name='class_location'><br/>
		主讲教师: <input type='text'name='teacher'><br/>
		上课时间:<br/>
		&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp
		周数:<input type='text'size=1 name='week_start'>
		到 <input type='text'size=1 name='week_end'>	
		除 <input type='text'size=10 name='week_exp'><br/>
		&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp 星期几:
		<select name='days'>
			<option value=0>星期日</option>
			<option value=1>星期一</option>
			<option value=2>星期二</option>
			<option value=3>星期三</option>
			<option value=4>星期四</option>
			<option value=5>星期五</option>
			<option value=6>星期六</option>
		</select>
		&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp节数:
		<select name='lession'>
			<option value=0>1~2</option>
			<option value=1>3~4</option>
			<option value=2>5~6</option>
			<option value=3>7~8</option>
			<option value=4>9~10</option>
			<option value=5>11~12</option>
		</select>
		<br/>
		日历: <select name='calendar_id'>
			<?php
			for($j=0;$j<$nums_of_calendar;$j++){
				echo '<option value='.$calendar_id[$j].'>'
					 .$calendar_summary[$j].'</option>';
			}
			?>
		</select><br/>
		颜色:<br/>
		<table>
		<tr>
			<?php
			for($i=0;$i<$nums_of_color;$i++){
				$a=$i+1;
				echo'<td width=\'30px\'bgcolor=\''.$colorHex[$i].'\'>
					 <input type=\'radio\'name=\'color\'value='.$a.'>
				</td>';
			}
			?>
		</tr>
		</table>
		通知:<input type='checkbox'name='reminder[]'value='email'checked>
		<input type='text'name='email'value='30'size=1
		> minutes before as 邮件<br/>
		
		&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp
		<input type='checkbox'name='reminder[]'value='sms'checked>
		<input type='text'name='sms'value='30'size=1
		> minutes before as 短信<br/>
		
		&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp
		<input type='checkbox'name='reminder[]'value='popup'checked>
		<input type='text'name='popup'value='30'size=1
		> minutes before as 弹窗<br/>
		<input type='submit'value='添加'>
	</div>
	</form>
	<div id="classtime"class="floatleft">
	1~2节课:<br/>
	8:00~9:40<br/>
	3~4节课:<br/>
	10:10~11:50<br/>
	5~6节课:<br/>
	秋:14:00~15:35<br/>
	夏:14:30~16:05<br/>
	7~8节课<br/>
	秋:15:55~17:30<br/>
	夏:16:25~18:00<br/>
	9~10节课:<br/>
	秋:18:30~20:05<br/>
	夏:19:00~20:35<br/>
	10~11节课:<br/>
	秋:20:15~21:50<br/>
	夏:20:45~22:20
	</div>
</div>
</body>
</html>
<?php

?>
