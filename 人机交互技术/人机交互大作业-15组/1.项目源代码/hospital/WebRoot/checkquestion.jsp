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

	<title>My JSP 'checkquestion.jsp' starting page</title>

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

<body style="background-color: #f4f4f4;">
	<nav class="navbar navbar-expand-lg navbar-light " style="background-color: #F9A1B6;">
		<a class="navbar-brand" href="#">云医生平台</a>
		<button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarSupportedContent"
			aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
			<span class="navbar-toggler-icon"></span>
		</button>

		<div class="collapse navbar-collapse" id="navbarSupportedContent" style="font-size: larger;">
			<ul class="navbar-nav mr-auto">
				<li class="nav-item active">
					<a class="nav-link" href="<%=request.getContextPath()%>/MainController?op=main">首页 <span
							class="sr-only">(current)</span></a>
				</li>
				<li class="nav-item dropdown">
					<a class="nav-link dropdown-toggle" href="#" id="navbarDropdown" role="button"
						data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
						问题栏
					</a>
					<div class="dropdown-menu" aria-labelledby="navbarDropdown">
						<a class="dropdown-item"
							href="<%=request.getContextPath()%>/MainController?op=qb&major=all">查看问题</a>
						<div class="dropdown-divider"></div>
						<a class="dropdown-item" href="addquestion.jsp">发布问题</a>
					</div>
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
								href="<%=request.getContextPath()%>/MainController?op=myquestion">我的问题</a>
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
	<% 
   		ArrayList al=(ArrayList)session.getAttribute("al");
		Iterator iter=al.iterator();
		Question qt=(Question)session.getAttribute("qt");
		UserService us=new UserService();
		String picture=us.getpicture(qt.getPublisher());
   		%>
	<div class="QuestionHeader">
		<div class="QuestionHeader-content">
			<div class="QuestionHeader-main">
				<div>
					<p><img style="border-radius: 50%;height: 20px;width:20px;" src="img/<%=picture%>">
						<a
							href="<%=request.getContextPath()%>/CheckUserController?op=user&uname=<%=qt.getPublisher()%>"><%=qt.getPublisher() %></a>
						问：
					</p>
				</div>
				<h1 class="QuestionHeader-title"><%=qt.getTitle()%></h1>
				<div class="LabelContainer-wrapper"></div>
				<div>
					<div class="css-eew49z">
						<div class="QuestionRichText QuestionRichText--collapsed">
							<div><span class="RichText ztext css-hnrfcf" itemprop="text"><%=qt.getContent() %></span>
							</div>
						</div>
					</div>
				</div>
			</div>

			<!--todo-->
			<!-- <div class="QuestionHeader-side">
				<div class="QuestionHeader-follow-status">
					<div class="QuestionFollowStatus">
						<div class="NumberBoard QuestionFollowStatus-counts NumberBoard--divider">
							<div class="Button NumberBoard-item Button--plain">
								<div class="NumberBoard-itemInner">
									<div class="NumberBoard-itemName">关注者</div><strong class="NumberBoard-itemValue"
										title="19303">1</strong>
								</div>
							</div>
							<div class="NumberBoard-item">
								<div class="NumberBoard-itemInner">
									<div class="NumberBoard-itemName">被浏览</div><strong class="NumberBoard-itemValue"
										title="40961904">6</strong>
								</div>
							</div>

						</div>
					</div>

				</div>
			</div> -->
		</div>
		<div class="QuestionHeader-footer">
			<div class="QuestionHeader-footer-inner">
				<div class="QuestionHeader-main QuestionHeader-footer-main">
					<div class="QuestionButtonGroup">
						<!-- <button type="button"
							class="Button FollowButton Button--primary Button--blue">关注问题</button> -->

					</div>
					<div class="QuestionHeaderActions">
						<!-- <button type="button" class="Button Button--grey Button--withIcon Button--withLabel"
							style="margin-right: 16px;">
							<span style="display: inline-flex; align-items: center;">&ZeroWidthSpace;
								<svg class="Zi Zi--Invite Button-zi" fill="currentColor" viewBox="0 0 24 24"
									width="1.2em" height="1.2em">
									<path
										d="M4 10V8a1 1 0 1 1 2 0v2h2a1 1 0 0 1 0 2H6v2a1 1 0 0 1-2 0v-2H2a1 1 0 0 1 0-2h2zm10.455 2c-2.21 0-4-1.79-4-4s1.79-4 4-4 4 1.79 4 4-1.79 4-4 4zm-7 6c0-2.66 4.845-4 7.272-4C17.155 14 22 15.34 22 18v1.375c0 .345-.28.625-.625.625H8.08a.625.625 0 0 1-.625-.625V18z"
										fill-rule="evenodd">
									</path>
								</svg></span>
							邀请回答
						</button> -->
						<div class="QuestionHeader-Comment">
							<button type="button" class="Button Button--plain Button--withIcon Button--withLabel">
								<span style="display: inline-flex; align-items: center;">&ZeroWidthSpace;
									<svg class="Zi Zi--Comment Button-zi" fill="currentColor" viewBox="0 0 24 24"
										width="1.2em" height="1.2em">
										<path
											d="M10.241 19.313a.97.97 0 0 0-.77.2 7.908 7.908 0 0 1-3.772 1.482.409.409 0 0 1-.38-.637 5.825 5.825 0 0 0 1.11-2.237.605.605 0 0 0-.227-.59A7.935 7.935 0 0 1 3 11.25C3 6.7 7.03 3 12 3s9 3.7 9 8.25-4.373 9.108-10.759 8.063z"
											fill-rule="evenodd"></path>
									</svg></span><%=qt.getReplynum() %> 条回答</button></div>

						<div class="QuestionHeader-actions"></div>
					</div>
				</div>
			</div>
		</div>
	</div>

	<div class="Question-main">
		<div>
			<div class="Question-mainColumn">
				<%
   			while(iter.hasNext())
  			{
  			Reply reply=(Reply)iter.next();
  			DoctorService ds=new DoctorService();
  			Doctor doctor=ds.findByUname(reply.getReplier());
  		%>
				<div class="Card AnswerCard">
					<div class="QuestionAnswer-content">
						<p><img style="border-radius: 50%;height: 40px;width:40px;" src="img/<%=doctor.getPicture()%>">
							<a
								href="<%=request.getContextPath()%>/CheckUserController?op=doctor&uname=<%=doctor.getUname()%>"><%=doctor.getName() %></a>
						</p>
						<p><%=reply.getContent() %></p>
					</div>


				</div>
				<%
  			}
  		%>
			</div>

		</div>


	</div>

</body>

</html>