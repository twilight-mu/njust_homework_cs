<%@ page language="java" import="java.util.*" contentType="text/html; charset=UTF-8"  pageEncoding="UTF-8"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'signupF.jsp' starting page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->

  </head>
  
  <body>
    注册失败 <br>
    <%
    int code = ((Integer)request.getAttribute("error_code")).intValue();
    switch(code){
      case 1:
         out.println("两次密码不匹配");
         break;
      case 2:
         out.println("用户名已存在!");
         break;
      case 3:
       	 out.println("未知错误!");
         break;
      case 4:
       	 out.println("验证码错误!");
         break;
    }   
     %>
     <br>
     <a href="signup.jsp">点此重新注册</a>
  </body>
</html>
