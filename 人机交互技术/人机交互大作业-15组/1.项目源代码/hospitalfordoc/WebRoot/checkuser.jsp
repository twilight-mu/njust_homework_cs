<%@ page language="java" import="java.util.*" contentType="text/html; charset=UTF-8"  pageEncoding="UTF-8"%>
<%@ page import= "edu.njust.entity.*,edu.njust.dao.*,edu.njust.service.*" %>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>

<head>
	<base href="<%=basePath%>">

	<title>My JSP 'checkuser.jsp' starting page</title>

	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
	<link rel="stylesheet" type="text/css" href="./css/bootstrap.min.css">
	<link rel="stylesheet" type="text/css" href="./css/font-awesome.min.css">
	<script type="text/javascript" src="./js/jquery-3.3.1.slim.min.js"></script>
	<script type="text/javascript" src="./js/popper.min.js"></script>
	<script type="text/javascript" src="./js/bootstrap.min.js"></script>
	<link rel="stylesheet" type="text/css" href="./css/main.css">
</head>

<style>
	/* 下拉按钮样式 */
	.dropbtn {
		height: 30px;
		width: 30px;
		border: none;
		cursor: pointer;
		background-image: url("img/dropdown.png");
		background-size: cover;
	}

	/* 容器 <div> - 需要定位下拉内容 */
	.dropdown {
		position: relative;
		display: inline-block;
	}

	/* 下拉内容 (默认隐藏) */
	.dropdown-content {
		display: none;
		position: absolute;
		background-color: #f9f9f9;
		min-width: 160px;
		box-shadow: 0px 8px 16px 0px rgba(0, 0, 0, 0.2);
	}

	/* 下拉菜单的链接 */
	.dropdown-content a {
		color: black;
		padding: 12px 16px;
		text-decoration: none;
		display: block;
	}

	/* 鼠标移上去后修改下拉菜单链接颜色 */
	.dropdown-content a:hover {
		background-color: #f1f1f1
	}

	/* 在鼠标移上去后显示下拉菜单 */
	.dropdown:hover .dropdown-content {
		display: block;
	}

	/* 当下拉内容显示后修改下拉按钮的背景颜色 */
	.dropdown:hover .dropbtn {
		background-color: #3e8e41;
	}
</style>

<body>
	<nav class="navbar navbar-expand-lg navbar-light " style="background-color: #F9A1B6;">
		<a class="navbar-brand" href="javasript:void(0);">云医生平台</a>
		<button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarSupportedContent"
			aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
			<span class="navbar-toggler-icon"></span>
		</button>

		<div class="collapse navbar-collapse" id="navbarSupportedContent" style="font-size: larger;">
			<ul class="navbar-nav mr-auto">
				<li class="nav-item">
					<a class="nav-link" href="<%=request.getContextPath()%>/MainController?op=main">首页 <span
							class="sr-only">(current)</span></a>
				</li>
				<li class="nav-item">
					<a class="nav-link" href="<%=request.getContextPath()%>/MainController?op=qb&major=all">
						问题栏
					</a>
				</li>
				<li class="nav-item">
					<a class="nav-link" href="chat.jsp">聊天室</a>
				</li>
				<li class="nav-item">
					<a class="nav-link" href="help.jsp">帮助</a>
				</li>

			</ul>
			<form class="form-inline my-2 my-lg-0">
				<ul class="navbar-nav">
					<img style="border-radius: 50%;height: 40px;width:40px;"
						src="img/<%=(String)session.getAttribute("picture")%>">
					<li class="nav-item dropdown">
						<a class="nav-link dropdown-toggle" href="#" id="navbarDropdown" role="button"
							data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"
							href="<%=request.getContextPath()%>/PersonalinfoController?op=check">
							<%=(String)session.getAttribute("user_name") %>
						</a>
						<div class="dropdown-menu" aria-labelledby="navbarDropdown">
							<a class="dropdown-item text-center"
								href="<%=request.getContextPath()%>/PersonalinfoController?op=check">个人中心</a>
							<div class="dropdown-divider"></div>
							<a class="dropdown-item text-center"
								href="<%=request.getContextPath()%>/MainController?op=myreply">我的回答</a>
							<div class="dropdown-divider"></div>
							<a class="dropdown-item text-center"
								href="<%=request.getContextPath()%>/MessageController?op=check">我的留言</a>
						</div>
					</li>
				</ul>
				<input class="form-control mr-sm-2" type="search" placeholder="Search" aria-label="Search">
				<button class="btn btn-outline-success my-2 my-sm-0" type="submit">Search</button>

			</form>

		</div>

	</nav>

	<form name="add" action="MessageController" method="get">
		<input type="hidden" name="op" value="add">
		<div class="modal fade" id="exampleModal" tabindex="-1" aria-labelledby="exampleModalLabel" aria-hidden="true">
			<div class="modal-dialog modal-dialog-centered">
				<div class="modal-content">
					<div class="modal-header">
						<h5 class="modal-title" id="exampleModalLabel">留言</h5>
						<button type="button" class="close" data-dismiss="modal" aria-label="Close">
							<span aria-hidden="true">&times;</span>
						</button>
					</div>
					<div class="modal-body">
						<div class="input-group">
							<textarea class="form-control" name="content" style="height: 300px;"></textarea>
						</div>

					</div>
					<div class="modal-footer">
						<button type="button" class="btn btn-secondary" data-dismiss="modal">关闭</button>
						<button type="submit" class="btn btn-primary">确认</button>
					</div>
				</div>
			</div>
		</div>
	</form>


	<%
	String op=(String)session.getAttribute("op");
	if(op.equals("user"))
	{
		User user=(User)session.getAttribute("info");
		session.setAttribute("writeto",user.getUname());
	%>
	<div class="container">
		<div class="row justify-content-md-center">
			<div class="col col-md-auto question" style="width: calc(100% - 50px);padding: 50px;">
				<div class="UserMessage">
					<img style="border-radius: 50%;height: 80px;width: 80px;" src="img/<%=user.getPicture()%>">
					<h2><%=user.getUname() %></h2>
				</div>
				<div class="Card" style="padding: 15px;">
					<div class="Card-Title">
						基本资料<button class="btn btn-primary" style="float: right;color: white;" data-toggle="modal"
							data-target="#exampleModal">留言</button>
					</div>
					<div class="Card-Content">
						<table class="table" style="margin-bottom: 0;">
							<td>用户名:</td>
							<td><%=user.getUname() %></td>
							</tr>
							<tr>
								<td>真实姓名:</td>
								<td><%=user.getName() %></td>
							</tr>
							<tr>
								<td>性别:</td>
								<td><%=user.getSex() %></td>
							</tr>
							<tr>
								<td>年龄:</td>
								<td><%=user.getAge() %></td>
							</tr>
							<tr>
								<td>手机号:</td>
								<td><%=user.getPhone() %></td>
							</tr>
							<tr>
								<td>个人简介:</td>
								<td><%=user.getDetail() %></td>
							</tr>
						</table>
					</div>

				</div>

			</div>
		</div>
	</div>
	<%
   		}
   		else if(op.equals("patient"))
   		{
   			Patient patient=(Patient)session.getAttribute("info");
   			session.setAttribute("writeto",patient.getUname());
   		%>
	<div class="container">
		<div class="row justify-content-md-center">
			<div class="col col-md-auto question" style="width: calc(100% - 50px);padding: 50px;">
				<div class="UserMessage">
					<img style="border-radius: 50%;height: 80px;width: 80px;" src="img/<%=patient.getPicture()%>">
					<h2><%=patient.getUname() %></h2>
				</div>
				<div class="Card" style="padding: 15px;">
					<div class="Card-Title">
						基本资料<button class="btn btn-primary" style="float: right;color: white;" data-toggle="modal"
							data-target="#exampleModal">留言</button>
					</div>
					<div class="Card-Content">
						<table class="table" style="margin-bottom: 0;">
							<td>用户名:</td>
							<td><%=patient.getUname() %></td>
							</tr>
							<tr>
								<td>真实姓名:</td>
								<td><%=patient.getName() %></td>
							</tr>
							<tr>
								<td>性别:</td>
								<td><%=patient.getSex() %></td>
							</tr>
							<tr>
								<td>年龄:</td>
								<td><%=patient.getAge() %></td>
							</tr>
							<tr>
								<td>手机号:</td>
								<td><%=patient.getPhone() %></td>
							</tr>
							<tr>
								<td>个人简介:</td>
								<td><%=patient.getDetail() %></td>
							</tr>
						</table>
					</div>

				</div>

			</div>
		</div>
	</div>

	<% 
}

%>


</body>

</html>