<%@ page language="java" import="java.util.*" contentType="text/html; charset=UTF-8" pageEncoding="utf-8"%>
<%@ page import= "edu.njust.entity.*,edu.njust.dao.*" %>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'userdetail.jsp' starting page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->

	<style>
			a{
				text-decoration: none;
				color:#33C6EB;
			}
			.top ul li a{
				text-decoration:none;
				display:inline-block;
				text-align:center;
				color:#33C6EB;
				padding: 0 15px;
				
				margin-top: 4px;
			}
			
			.box{
				width:50%;
				margin: 0 auto;
				page-break-inside: 0;
				margin-top: 15px;
			}
			.main{
				width:60%;
				height:600px;
				margin: 0 auto;
				padding: 0;
    			background-color: #a6d2f7;
   			    border-radius: 10px;
			}
			.main .title1{
				height: 50px;
				text-align: center;
				line-height: 50px;
			}
			.main .detail{
				width: 40%;
				height: 60px;
				line-height: 60px;
				margin: 10px auto;
				
				background-color: #c1e2f9;
				border-radius: 10px;
			}
			.main .state{
				text-align: right;
			}
a:link {
  text-decoration: none;
  color: blue;
}

a:visited {
  text-decoration: none;
  color: purple;
}

a:hover {
  text-decoration: underline;
   color: hotpink;
}

a:active {
  text-decoration: underline;
   color: blue;
}
		</style>

  </head>
  
  <body style="background:url(img/蓝色1.jpg)
   	;background-size:100%;background-attachment:fixed">
   <div class="top"><ul><li>
    <a
	    href="<%=request.getContextPath()%>/UserController?op=all">返回首页
	</a></li></div></div>
  <%
  	String type=(String)session.getAttribute("type");
  	if(type.equals("dt"))
  	{
  		Doctor user=(Doctor)session.getAttribute("udetail");
  	%>
  	<br>
	
  	
	<div class="main">
	<div class="title1"><font size="5">用户详细信息</font></div>
	<div>
	<center>
	<img style="border-radius:50%;height: 100px;width:100px;" src="img/<%=user.getPicture()%>"></div>
	</center>	
	<div class="detail"><font style="font-size:1vw;font-weight:bold;margin-left:30px;">用户名:</font>&#9;&#9;&#9;&#9;&#9;&#9;<%=user.getUname()%></div>
	<div class="detail"><font style="font-size:1vw;font-weight:bold;">真实姓名:</font>&#9;&#9;&#9;&#9;&#9;&#9;<%=user.getName() %></div>
	<div class="detail"><font style="font-size:1vw;font-weight:bold;">性别:</font>&#9;&#9;&#9;&#9;&#9;&#9;<%=user.getSex()%></div>
	<div class="detail"><font style="font-size:1vw;font-weight:bold;">年龄:</font>&#9;&#9;&#9;&#9;&#9;&#9;<%=user.getAge() %></div>
	<div class="detail"><font style="font-size:1vw;font-weight:bold;">电话号码:</font>&#9;&#9;&#9;&#9;&#9;&#9;<%=user.getPhone() %></div>
	<div class="detail"><font style="font-size:1vw;font-weight:bold;">详细信息:</font>&#9;&#9;&#9;&#9;&#9;&#9;<%=user.getDetail() %></div>
	</div>

  	<%
  	}
  	%>
  	
  	<% 
  	if(type.equals("pt"))
  	{
  		Patient user=(Patient)session.getAttribute("udetail");
  	%>	
  	
  	 	<br>
  	 
	<div class="main">
	
	<div class="title1"><font size="5">用户详细信息</font></div>

	<div>
	<center>
	<img style="border-radius:50%;height: 100px;width:100px;" src="img/<%=user.getPicture()%>"></div>	
	</center>
	<div class="detail"><font style="font-size:1vw;font-weight:bold;">用户名:</font>&#9;&#9;&#9;&#9;&#9;&#9;<%=user.getUname()%></div>
	<div class="detail"><font style="font-size:1vw;font-weight:bold;">真实姓名:</font>&#9;&#9;&#9;&#9;&#9;&#9;<%=user.getName() %></div>
	<div class="detail"><font style="font-size:1vw;font-weight:bold;">性别:</font>&#9;&#9;&#9;&#9;&#9;&#9;<%=user.getSex()%></div>
	<div class="detail"><font style="font-size:1vw;font-weight:bold;">年龄:</font>&#9;&#9;&#9;&#9;&#9;&#9;<%=user.getAge() %></div>
	<div class="detail"><font style="font-size:1vw;font-weight:bold;">电话号码:</font>&#9;&#9;&#9;&#9;&#9;&#9;<%=user.getPhone() %></div>
	<div class="detail"><font style="font-size:1vw;font-weight:bold;">详细信息:</font>&#9;&#9;&#9;&#9;&#9;&#9;<%=user.getDetail() %></div>

	

	</div>

  <% 	
  	}
  %>
  
	
  </body>
</html>
