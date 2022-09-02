<%@ page language="java" import="java.util.*" contentType="text/html; charset=UTF-8"  pageEncoding="UTF-8"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>

<head>
	<base href="<%=basePath%>">

	<title>登录</title>

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
	<link rel="stylesheet" type="text/css" href="./css/main.css">
	<link rel="stylesheet" type="text/css" href="./css/bootstrap.min.css">
	<link rel="stylesheet" type="text/css" href="./css/font-awesome.min.css">
	<script type="text/javascript" src="./js/jquery-3.3.1.slim.min.js"></script>
	<script type="text/javascript" src="./js/popper.min.js"></script>
	<script type="text/javascript" src="./js/bootstrap.min.js"></script>
	<script type="text/javascript">
		function validate_login() {
			var uname = document.forms["login"]["uname"].value;
			var upwd = document.forms["login"]["upwd"].value;
			if (uname == null || uname == "") {
				$("#alert-content").text("姓名不能为空");
				$("#alert").addClass("show");
				return false;
			} else if (upwd == null || upwd == "") {
				$("#alert-content").text("密码不能为空");
				$("#alert").addClass("show");
				return false;
			}
		}
	</script>
	<script type="text/javascript">
		function hide() {
			alert(1);
			$("#alert").removeClass("show");
			return true;
		}

		function hide1() {
			$("#alert-suc").removeClass("show");
		}

		function validateForm() {
			var cNu = document.forms["add"]["newuser"].value;
			var cNp1 = document.forms["add"]["newpwd1"].value;
			var cNp2 = document.forms["add"]["newpwd2"].value;
			var Ph = document.forms["add"]["phone"].value;
			var Ck = document.forms["add"]["checkcode"].value;
			if (cNu == null || cNu == "") {
				$("#alert-content").text("请输入用户名！");
				$("#alert").addClass("show");
				return false;
			} else if (cNp1 == null || cNp1 == "") {
				$("#alert-content").text("请输入密码！");
				$("#alert").addClass("show");
				return false;
			} else if (cNp2 == null || cNp2 == "") {
				$("#alert-content").text("请再次输入密码！");
				$("#alert").addClass("show");
				return false;
			} else if (Ph == null || Ph == "") {
				$("#alert-content").text("请输入手机号！");
				$("#alert").addClass("show");
				return false;
			} else if (Ck == null || Ck == "") {
				$("#alert-content").text("请输入验证码！");
				$("#alert").addClass("show");
				return false;
			} else if (cNp1 != cNp2) {
				$("#alert-content").text("两次密码输入不一致");
				$("#alert").addClass("show");
			}
		}

		function reloadCheckImg() {
			$("img").attr("src", "img.jsp?t=" + (new Data().getTime()));
		}

		$(document).ready(function () {
			$("checkcodeId").blur(function () {
				var $checkcode = $("#checkcodeId").val();
				$.post(
					"LoginServlet",
					"checcode=" + $checkcode,
					function (result) {
						var result = $("<img src = '" + result + "' height='15' width='15px' />");
					});
			});
			$(".close").click(function () {
				$("#alert").removeClass("show");
			});
			var code = <%=request.getAttribute("error_code") %>;
			if (code != null) {
				switch (code) {
					case 1:
						$("#alert-content").text("用户不存在");
						$("#alert").addClass("show");
						break;
					case 2:
						$("#alert-content").text("密码错误");
						$("#alert").addClass("show");
						break;
					case 3:
						$("#alert-content").text("两次密码不匹配");
						$("#alert").addClass("show");
						break;
					case 4:
						$("#alert-content").text("用户名已存在");
						$("#alert").addClass("show");
						break;
					case 5:
						$("#alert-content").text("未知错误");
						$("#alert").addClass("show");
						break;
					case 6:
						$("#alert-content").text("验证码错误");
						$("#alert").addClass("show");
						break;
					case 7:
						$("#alert-content").text("您的账号已被封禁");
						$("#alert").addClass("show");
						break;
				}
			}
			var scode = <%=request.getAttribute("suc_code")%> ;
			if (scode != null) {
				if (scode == 1) {
					$("#suc-content").text("注册成功！");
					$("#alert-suc").addClass("show");
				}
			}
		});
	</script>
</head>

<body>
	<nav class="navbar navbar-expand-lg navbar-light " style="background-color: #F9A1B6;">
		<a class="navbar-brand" href="#">云医生平台</a>
		<button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarSupportedContent"
			aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
			<span class="navbar-toggler-icon"></span>
		</button>

		

	</nav>
	<div class="alert alert-warning alert-dismissible fade text-center " id="alert" role="alert">
		<strong id="alert-content">密码错误！</strong>
		<button type="button" class="close" aria-label="Close">
			<span aria-hidden="true">&times;</span>
		</button>
	</div>

	<!-- <div class="alert alert-success alert-dismissible fade text-center " id="alert-suc" role="alert">
		<strong id="suc-content">登录成功</strong>
		<button type="button" class="close" aria-label="Close" onclick="hide1();">
			<span aria-hidden="true">&times;</span>
		</button>
	</div> -->

	<form name="add" action="SignupController" onsubmit="return validateForm()" method="get">
		<div class="modal fade" id="exampleModal" tabindex="-1" role="dialog" aria-labelledby="sign-up"
			aria-hidden="true">
			<div class="modal-dialog modal-dialog-centered" role="document">
				<div class="modal-content" style="box-shadow: 4px 4px 10px 1px #645858;">
					<div class="modal-header" style="background-color: #F9A1B6;">
						<h5 class="modal-title" id="exampleModalLabel"> 注册 </h5>
						<button type="button" class="close" data-dismiss="modal" aria-label="Close">
							<span aria-hidden="true">&times;</span>
						</button>
					</div>
					<div class="modal-body text-center">
						<div class="input-group mb-3">
							<div class="input-group-prepend">
								<span class="input-group-text text-center" id="basic-addon1"><i
										class="fa fa-user"></i></span>
							</div>
							<input type="text" class="form-control" name="newuser" placeholder="请输入您的用户名"
								aria-label="Username" aria-describedby="basic-addon1">
						</div>
						<div class="input-group mb-3">
							<div class="input-group-prepend">
								<span class="input-group-text text-center" id="basic-addon1"><i
										class="fa fa-unlock-alt"></i></span>
							</div>
							<input type="password" class="form-control" placeholder="请输入密码" name="newpwd1"
								aria-label="Username" aria-describedby="basic-addon1">
						</div>

						<div class="input-group mb-3">
							<div class="input-group-prepend">
								<span class="input-group-text text-center" id="basic-addon1"><i
										class="fa fa-unlock"></i></span>
							</div>
							<input type="password" class="form-control" placeholder="请再次输入密码" name="newpwd2"
								aria-label="Username" aria-describedby="basic-addon1">
						</div>

						<div class="input-group mb-3">
							<div class="input-group-prepend">
								<span class="input-group-text text-center" id="basic-addon1"><i
										class="fa fa-mobile"></i></span>
							</div>
							<input type="text" class="form-control" placeholder="请输入手机号" name="phone"
								aria-label="Username" aria-describedby="basic-addon1">
						</div>

						<div class="input-group mb-3">
							<div class="input-group-prepend">
								<span class="input-group-text text-center" id="basic-addon1"><i
										class="fa fa-code"></i></span>
							</div>
							<input type="text" class="form-control" name="checkcode" placeholder="请输入验证码"
								aria-label="Username" aria-describedby="basic-addon1">
							<a href="javascript:reloadCheckImg();"><img src="img.jsp" /></a>
						</div>


					</div>
					<div class="modal-footer">
						<button type="button" class="btn btn-secondary" data-dismiss="modal">Close</button>
						<input type="submit" class="btn btn-primary" value="立即注册" />
					</div>
				</div>
			</div>
		</div>
	</form>
	<div class="container" style="">
		<div class="row">
			<div class="col pic">
				<div class="text">
					<h2 class="kusjz">快速就诊</h2>
					<h2 class="zuykk">专业可靠</h2>
				</div>

				<img src="img/doctor.png" />
			</div>
			<div class="login-container col">
				<div class="login-title">
					登录
				</div>
				<div class="login-content">
					<form name="login" action="LoginController" method="get">
						<div class="content">

							<div class="user">
								<svg class="user-img" xmlns="http://www.w3.org/2000/svg"
									xmlns:xlink="http://www.w3.org/1999/xlink" width="40" height="30"
									viewBox="0 0 36 40" fill="none">
									<defs>
										<pattern id="pattern0" patternContentUnits="objectBoundingBox" width="1"
											height="1">
											<use transform="translate(-0.05555555555555555 0) scale(0.004273504273504274 0.0038461538461538464) rotate(0)"
												xlink:href="#image0" />
										</pattern>
										<image id="image0" width="260" height="260"
											xlink:href="data:image/png;base64,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" />
									</defs>
									<path id="ed0ce46d1f5c4c40b0adc932f05d7c95 (1).png" fill-rule="evenodd"
										style="fill:url(#pattern0)" transform="translate(0 0)  rotate(0 18 20)"
										opacity="1" d="M0,40L36,40L36,0L0,0L0,40Z " />
								</svg>
								<input type="text" name="uname" placeholder="请输入用户名">
							</div>

							<div class="pwd">
								<img src="./img/pwd.png" width="40" height="30">
								<input type="password" name="upwd" placeholder="请输入密码">

							</div>

							<div class="else">
								<div class="remember">
									<input type="checkbox" name="remenber" />记住我
								</div>
								<div class="register">
									没有账号？<a href="javascript:void(0);" data-toggle="modal"
										data-target="#exampleModal">注册一个</a>
								</div>
							</div>
						</div>

						<div class="login-btn">
							<input class="btn btn-success" onclick="return validate_login();" type="submit" value="登录">
						</div>

						<br>
					</form>
				</div>

			</div>
		</div>
	</div>


</body>


</html>