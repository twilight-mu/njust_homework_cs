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
    
    <title>My JSP 'userlist.jsp' starting page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
	
	<style type="text/css">
			*{
				margin: 0;
				padding: 0;
			}
			.top{
				height: 40px;
			}
			.top ul{
				line-height: 40px;
				float:right;
			}
			.top ul li{
				float:left;
				margin:0;
				padding:0;
				list-style: none;
			}
			.top ul li a{
				text-decoration:none;
				display:inline-block;
				text-align:center;
				color:white;
				padding: 0 15px;
				
				margin-top: 4px;
			}
			.top ul li a:hover{
				height: 40px;
				margin-top: 0;
				background: #27bdea;
				border-color: black;
			}
		.main{
				margin: 0 auto;
				width:70%;
				margin-top: 30px;
    		border:1px solid #33c6eb;
    		background-color: rgba(135,206,235,0.6);	
   		 border-radius: 10px;	
   	
			}
			table,table td{
				
				border-collapse: collapse;
				border-radius: inherit;
			}
			table td,th{
				padding-left: 10px;
				align-items: center;
				border:1px solid #33c6eb;
			}
			td {
  				border: 1px solid black;
  				padding-top: 10px;
  				padding-right: 15px;
  				padding-bottom: 10px;
  				padding-left: 15px;
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
  
  <body style="background:url(img/蓝色1.jpg);background-size:100%;background-attachment:fixed">
    <div  class="top" style="background:url(img/头.jpg);background-size:100%">
    <center>
    
        <ul>
          <li><a href ="<%=request.getContextPath()%>/UserController?op=all">用户列表</a></li>
          <li><a href ="<%=request.getContextPath()%>/QuestionController?op=all">问题列表</a></li>
          <li><a href ="<%=request.getContextPath()%>/ReplyController?op=all">回答列表</a></li>
          <li><a href ="<%=request.getContextPath()%>/MessageController?op=all" >留言列表</a></li>
          <li>欢迎,管理员<%=(String)session.getAttribute("user_name") %><a href=login.jsp>登出></a></li>
        </ul>

   </center></div>
   <br><div class="main">
   <center>
   <font style="font-size:1.5vw;">病人用户列表</font>
   <br>
   <table border="1"width="100%" style="table-layout: fixed;" frame="void">
  		<tr style="font-size:1vw;"><th>用户名</th><th>账号状态</th><th></th><th></th></tr>
  		<%
  			ArrayList al1=(ArrayList)session.getAttribute("al1");
  			Iterator iter1=al1.iterator();
  			while(iter1.hasNext())
  			{
  			Patient pt=(Patient)iter1.next();
  		%>
  			<tr><td><%=pt.getUname() %></td>
  				<td>
  				<%if(pt.getIsLocked()==0){ %>
  				 <font color="green">正常</font>
  				<%}else{ %>
  			     <font color="red">封禁中</font>
  				<%} %>
  				</td>
  				
  				<td><a href="<%=request.getContextPath()%>/UserController?op=detailpt&user=<%=pt.getUname()%>">查看详细</a></td>
  				
  				<td>
  			
  				<%if(pt.getIsLocked()==0){ %>
  				 <a href="<%=request.getContextPath()%>/UserController?op=lockpt&user=<%=pt.getUname()%>">封禁该账号</a>
  				<%}else{ %>
  			    <a href="<%=request.getContextPath()%>/UserController?op=releasept&user=<%=pt.getUname()%>">解封该账号</a>
  				<%} 
  				%>
  				</td>
  		<%
  			} 
  		%>
  	</table>
   </center></div>
   
   <br><div class="main">
   <center>
    <font style="font-size:1.5vw;">医生用户列表</font>
    <br>
   <table border="1"width="100%" style="table-layout: fixed;" frame="void">
  		<tr style="font-size:1vw;"><th>用户名</th><th>账号状态</th><th></th><th></th></tr>
  		<%
  			ArrayList al2=(ArrayList)session.getAttribute("al2");
  			Iterator iter2=al2.iterator();
  			while(iter2.hasNext())
  			{
  			Doctor dt=(Doctor)iter2.next();
  		%>
  			<tr><td><%=dt.getUname() %></td>
  				<td>
  				<%if(dt.getIsLocked()==0){ %>
  				 <font color="green">正常</font>
  				<%}else{ %>
  			     <font color="red">封禁中</font>
  				<%} %>
  				</td>
  				<td><a href="<%=request.getContextPath()%>/UserController?op=detaildt&user=<%=dt.getUname()%>">查看详细</a></td>
  				<td>
  			
  				<%if(dt.getIsLocked()==0){ %>
  				 <a href="<%=request.getContextPath()%>/UserController?op=lockdt&user=<%=dt.getUname()%>">封禁该账号</a>
  				<%}else{ %>
  			    <a href="<%=request.getContextPath()%>/UserController?op=releasedt&user=<%=dt.getUname()%>">解封该账号</a>
  				<%} 
  				%>
  				</td>
  		<%
  			} 
  		%>
  	</table>
   </center></div>
   
  </body>
</html>
