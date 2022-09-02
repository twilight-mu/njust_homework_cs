package edu.njust.utils;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

public class CalendarUtil {

/**
* 日期格式化
* @param date
* @return
*/
public static String dateFormat(Date date) {
	SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:ss:mm");
	return sdf.format(date);
}

/****
* 传入具体日期 ，和传入的修改时间，返回具体日期加几月
*
*/
public static String subMonth(String date,int monthCount) throws ParseException {
	SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
	Date dt = sdf.parse(date);
	Calendar rightNow = Calendar.getInstance();
	rightNow.setTime(dt);

	rightNow.add(Calendar.MONTH, monthCount);
	Date dt1 = rightNow.getTime();
	String reStr = sdf.format(dt1);

	return reStr;
}

/***
* 日期减一天、加一天
*/
public static String checkOption(String option, String _date) {
	SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
	Calendar cl = Calendar.getInstance();
	Date date = null;

	try {
		date = (Date) sdf.parse(_date);
	} catch (ParseException e) {
		e.printStackTrace();
	}
	cl.setTime(date);
	if ("pre".equals(option)) {
	// 时间减一天
		cl.add(Calendar.DAY_OF_MONTH, -1);
	
	} else if ("next".equals(option)) {
	// 时间加一天
		cl.add(Calendar.DAY_OF_YEAR, 1);
	} else {
	// do nothing
	}
	date = cl.getTime();
	return sdf.format(date);
}


/**测试
* @param args
* @throws Exception
*/
  public static void main(String[] args) throws Exception {
	String string = CalendarUtil.subMonth("2018-07-05 17:34:57",10);
	String s = CalendarUtil.dateFormat(new Date());
	System.out.println(s);
	System.out.println(string);
  }
}
