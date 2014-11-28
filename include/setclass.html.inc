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
<html>
<head>
	<title>Classtable2Calendar</title>
</head>
<body>
	<h1><font size=7>Set your class</font></h1>
	<hr/>
	<form action="<?php $_SERVER['PHP_SELF'] ?>"method='post'>
		课程名称:<input type='text'name='class_name'><br/>
		课程地点:<input type='text'name='class_location'><br/>
		主讲教师:<input type='text'name='teacher'><br/>
		上课时间:<br/>
		&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp
		周数:<input type='text'size=1 name='week_start'>
		到<input type='text'size=1 name='week_end'>	
		除<input type='text'size=5 name='week_exp'><br/>
		&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp星期几:
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
		日历:<select name='calendar_id'>
			<?php
			for($j=0;$j<$nums_of_calendar;$j++){
				echo '<option value='.$calendar_id[$j].'>'
					 .$calendar_summary[$j].'</option>';
			}
			?>
		</select><br/>
		颜色:<br/>
		<table border=1>
		<tr>
			<?php
			for($i=0;$i<$nums_of_color;$i++){
				echo'<td width=\'10\'bgcolor=\''.$colorHex[$i].'\'>color</td>';
			}
			?>
		</tr>
		<tr>
			<?php
			for($i=0;$i<$nums_of_color;$i++){
				$a=$i+1;
				echo'<td align=\'center\'>
					<input type=\'radio\'name=\'color\'value='.$a.'></td>';
			}
			?>
		</tr>
		</table>
		通知:<input type='checkbox'name='reminder[]'value='email'checked>
		<input type='text'name='email'value='30'size=1
		>minutes before as 电子邮件<br/>
		
		&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp
		<input type='checkbox'name='reminder[]'value='sms'checked>
		<input type='text'name='sms'value='30'size=1
		>minutes before as 短信<br/>
		
		&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp
		<input type='checkbox'name='reminder[]'value='popup'checked>
		<input type='text'name='popup'value='30'size=1
		>minutes before as 弹窗<br/>
		<input type='submit'value='添加'>
	</form>
</body>
</html>
<?php

?>
