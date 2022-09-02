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

  <title>My JSP 'myquestion.jsp' starting page</title>

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
          <a class="nav-link dropdown-toggle" href="#" id="navbarDropdown" role="button" data-toggle="dropdown"
            aria-haspopup="true" aria-expanded="false">
            问题栏
          </a>
          <div class="dropdown-menu" aria-labelledby="navbarDropdown">
            <a class="dropdown-item" href="<%=request.getContextPath()%>/MainController?op=qb&major=all">查看问题</a>
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
            <a class="nav-link dropdown-toggle" href="#" id="navbarDropdown" role="button" data-toggle="dropdown"
              aria-haspopup="true" aria-expanded="false"
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
  <div class="container">
    <div class="row justify-content-md-center">
      <div class="col col-md-auto question" style="width: calc(100% - 50px);padding: 50px;">
        <h2>我发布的问题</h2>
        <table class="table" style="border-bottom: #dee2e6 solid 1px;">
          <tr>
            <td>标题</td>
            <td>科室</td>
            <td>回复数</td>
          </tr>
          <%
   		ArrayList al=(ArrayList)session.getAttribute("al");
		Iterator iter=al.iterator(); 
		while(iter.hasNext())
		{
			Question qt=(Question)iter.next();
	%>
          <tr>
            <td><a href="<%=request.getContextPath()%>/ReplyController?qid=<%=qt.getId()%>"> <%=qt.getTitle() %></a>
            </td>
            <td><%=qt.getMajor() %> </td>
            <td><%=qt.getReplynum() %></td>
          </tr>
          <%
		}
	%>
        </table>
      </div>
    </div>
  </div>
</body>

</html>