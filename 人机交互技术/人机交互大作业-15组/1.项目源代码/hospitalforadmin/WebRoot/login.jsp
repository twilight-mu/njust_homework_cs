<%@ page language="java" import="java.util.*" contentType="text/html; charset=UTF-8"  pageEncoding="UTF-8"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'login.jsp' starting page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->

  </head>
  
     <script type="text/javascript" >
    
      function validateForm(){
		  var uname = document.forms["login"]["uname"].value;
		  var upwd = document.forms["login"]["upwd"].value;
		  if (uname ==null || uname =="")
		  {
		    alert("用户名必须填写！");
		    return false;
		  }
		  else if (upwd ==null || upwd =="")
		  {
		    alert("密码不能为空！");
		    return false;
		  }
      }
    </script>
  
  <style>
    *{
    font-family:"微软雅黑";
    
    }
    
	body{
		max-width:100%;
		height:60%;
		background-image:url("img/login.jpg");
		background-repeat:no-repeat;
		background-size:100% 100%;
		
		}
	input[type=text]{
		width: 250px;
		height:30px;
  		box-sizing: border-box;
  		border: 2px solid #ccc;
  		border-radius: 4px;
  		font-size: 20px;
  		background-color: white;
		background-position: 0px 0px; 
  		background-repeat: no-repeat;
  		transition: width 0.4s ease-in-out;
	}
	input[type=password]{
	width: 250px;
	height:30px;
  		box-sizing: border-box;
  		border: 2px solid #ccc;
  		border-radius: 4px;
  		font-size: 16px;
  		background-color: white;
		background-position: 0px 0px; 
  		background-repeat: no-repeat;
  		transition: width 0.4s ease-in-out;
	
	}
	input[type=text]:focus {
  		width: 80%;
  		background-color:#EEE8AA;
	}
	input[type=password]:focus {
  		width: 80%;
  		background-color:#EEE8AA;
	}

	input[type="submit"],input[type="reset"]{
    width: 60px;
    height:40px;
    text-align: center;
    text-decoration: none;
    font: 16px/100% Arial, Helvetica, sans-serif;
    padding: 5px 2px 4px;
    border-radius: 5px;
    box-shadow: 0 1px 2px rgba(0, 0, 0, .2);
    color: #d9eef7;
    border: solid 1px #0076a3;
    background: #0095cd;
    background: -webkit-gradient(linear, left top, left bottom, from(#0095cc), to(#00678e));
    background: -moz-linear-gradient(top, #00adee, #00678e);
  
}
			input[type="submit"]:hover ,input[type="reset"]:hover{
    background: #007ead;
    background: -webkit-gradient(linear, left top, left bottom, from(#00678e), to(#0095cc));
    background: -moz-linear-gradient(top, #00678e, #0095cc);
    filter: progid:DXImageTransform.Microsoft.gradient(startColorstr='#00678e', endColorstr='#0095cc');
}
	#login{
		wide:40%;
 		border-collapse: collapse;
 		empty-cells:hide;
	}

	#login td, #login th {
  		border: 1px solid #ddd;
  		padding: 5px;
	}

#login td {
  padding-top: 12px;
  padding-bottom: 12px;
  text-align: center;
  background-color: #4CAF50;
  color: white;
}



h {
  font-size: 20px;
  margin:40px 2px;
}
table{
	width:30%;
	height:40%;
	text-align:center;
	font-size:19px;
	font-weight:600;
}

a:link {
  text-decoration: none;
  color: red;
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
  
<body style="background:url(img/蓝色1.jpg)
   	;background-size:100%;background-attachment:fixed">
<center style="margin-top:40px;"><h1 >云医生平台</h1></center>
 <center><h3 >信息管理</h3></center>
 <center>
  <form name="login" action="LoginController" onsubmit="return validateForm()" method = "get">
  
    <table>
      <tr>  <td style="width:100px;"> 用户名：</td><td style="width:250px;"><input  type = "text" name ="uname" placeholder="请输入用户名"> </td> </tr>
      <tr>  <td> 密码：</td><td><input  type = "password" name ="upwd" placeholder="请输入密码"></td> </tr>
    </table>
	<br>
      <input  type = "submit" value = "登录">
	<br>
  </form>
  </center>
 </body>
</html>
