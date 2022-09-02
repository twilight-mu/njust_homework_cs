<%@ page language="java" import="java.util.*" contentType="text/html; charset=UTF-8"  pageEncoding="UTF-8"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>

<head>
	<meta name="author" content="Yeeku.H.Lee(CrazyIt.org)" />
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
	<title>WebSocket聊天室 </title>
	<link rel="stylesheet" type="text/css" href="./css/main.css">
	<link rel="stylesheet" type="text/css" href="./css/bootstrap.min.css">
	<link rel="stylesheet" type="text/css" href="./css/font-awesome.min.css">
	<script type="text/javascript" src="./js/jquery-3.3.1.slim.min.js"></script>
	<script type="text/javascript" src="./js/popper.min.js"></script>
	<script type="text/javascript" src="./js/bootstrap.min.js"></script>
	<style>
		.height {
			height: 6px;
		}

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
	<script type="text/javascript">
		//创建客户端使用的用户名
		var userName;
		var websocket = null;
		//穿件websocket函数
		function ws() {
			userName = document.getElementById('user').value;
			webSocket = new WebSocket("ws://" + location.host + "/hospital/chat?user=" + userName);

			// 为onmessage事件绑定监听器，接收消息
			webSocket.onmessage = function (event) {
				//分析json,如果没有to则是用户列表，否则为普通消息
				var json = JSON.parse(event.data);
				if ((typeof json.to) == 'undefined') {
					var html = '<option>All</option>';
					for (var user in json) {
						html += '<option>' + json[user] + '</option>';
					}
					document.getElementById('select').innerHTML = html;
				} else {
					var show = document.getElementById('show');
					//判断json,如果发送者为自己，则显示在右侧
					if (json.from == userName) {
						show.innerHTML += '<p class="height" align="right">' + json.from + ": &nbsp" + json.msg + '</p>';
					} else {
						show.innerHTML += '<p class="height" align="left">' + json.from + ":&nbsp" + json.msg + '</p>';
					}
					show.scrollTop = show.scrollHeight;
				}
			}

			webSocket.onclose = function () {
				Console.log('WebSocket已经被关闭。');
			};
		}
		//发送消息
		function sendMsg() {
			var inputMsg = document.getElementById('msg');
			var selectTo = document.getElementById('select');
			//普通消息格式
			var msg = {
				from: userName,
				to: selectTo.value,
				msg: inputMsg.value
			}
			// 发送消息
			webSocket.send(JSON.stringify(msg));
			// 清空单行文本框
			inputMsg.value = "";
		}
	</script>
</head>

<body>
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
					<a class="nav-link" href="download/平台教程手册.docx">帮助</a>
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
	<center>
	<div>
		欢迎用户<%=session.getAttribute("user_name") %>,请点击右侧按钮接入服务器!
		<input type="hidden" size="80" id="user" name="user" value="<%=session.getAttribute("user_name") %>" />
		<input type="button" value="链接" id="coon" onclick="ws()" />
	</div></center>
	<div class="container">
		<div class="row justify-content-md-center">
			<div class="col col-md-auto question" style="width: calc(100% - 80px);padding: 50px;">
				<div class="text-center">
					<h2>聊天室</h2>
				</div>
				<div style="height: 400px; overflow-y:auto;border:1px solid #333;font-size: 20px;padding: 10px;margin-bottom: 20px;"
					id="show"></div>
				<div class="input-group">
					<div class="input-group-prepend">
						<select id="select"></select>
					</div>
					<input type="text" class="form-control" id="msg" placeholder="输入聊天内容" />
					<div class="input-group-append">
						<input type="button" value="发送" id="sendBn" onclick="sendMsg()" />
					</div>
				</div>

			</div>
		</div>
	</div>
	
	
</body>

</html>