<%@ page language="java" import="java.util.*" contentType="text/html; charset=UTF-8"  pageEncoding="UTF-8"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>新增课程</title>
    
    <meta name="content-type" content="text/html; charset=UTF-8">
    <?xml encoding="UTF-8"?>
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
	<style type="text/css">
      .selectCSS{ width:200px}
    </style>
    
	<script type="text/javascript" src="js/My97DatePicker/WdatePicker.js"></script>
    <script type="text/javascript" >
    
      function validateForm(){
		  var cName = document.forms["addCourse"]["cName"].value;
		  var cCreator = document.forms["addCourse"]["cCreator"].value;
		  if (cName ==null || cName =="")
		  {
		    alert("课程名称必须填写！");
		    return false;
		  }else if (cCreator ==null || cCreator =="")
		  {
		    alert("创建者不能为空！");
		    return false;
		  }	  
	  }
    </script>
    
  </head>
  
 <body>
  <br>
  <br>

  <H2>费用提取</H2>
  <form name="addCourse"  action="courseReview" onsubmit="return validateForm()" method = "get">
  <% 

java.text.SimpleDateFormat formatter = new java.text.SimpleDateFormat("yyyy-MM-dd HH:mm:ss"); 

java.util.Date currentTime = new java.util.Date();//得到当前系统时间 

String s[]=request.getParameterValues("chk");
int sum=0;
for(int i=0;i<s.length;i++)
{
	sum+=Integer.parseInt(s[i]);
}
%>
    <table>
      <tr>  <td><input type = "hidden" name = "operation" value="add"> </td> 
      		<td><input type = "hidden" name = "pg" value="none"> </td> 
      </tr>
      <tr>  <td> 姓名：   </td><td><input  type = "text" name = "name"> </td> </tr>
      <tr>  <td> 银行卡号：   </td><td><input  type = "text" name = "banknumber"></td> </tr>
      <tr>  <td> 费用总额：</td><td><input  type = "text" name = "amount" value="<%=sum %>"></td> </tr>
		<tr><td>时间:</td>
            <td><input  type = "text" name = "time" value="<%=currentTime.toLocaleString() %>"></td>          
      </tr>
    
    </table>
      <input  type = "submit" value = "提交"><A href ="courseReview?operation=query&pg=none"><input  type = "button" value = "返回"></a><br/>
      <script type="text/javascript" >
      alter("支付成功");
      </script>
      
      
  </form>

 </body> 

</html>
