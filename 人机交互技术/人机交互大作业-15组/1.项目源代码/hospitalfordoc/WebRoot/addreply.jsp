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

  <title>My JSP 'addreply.jsp' starting page</title>

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

  <% 
   		ArrayList al=(ArrayList)session.getAttribute("al");
		Iterator iter=al.iterator();
		Question qt=(Question)session.getAttribute("qt");
		PatientService ps=new PatientService();
		Patient patient=ps.findByUname(qt.getPublisher());
   		%>
  <div>
    <div class="QuestionHeader">
      <div class="QuestionHeader-content">
        <div class="QuestionHeader-main">
          <div>
            <p><img style="border-radius: 50%;height: 20px;width:20px;" src="img/<%=patient.getPicture()%>">
              <a
                href="<%=request.getContextPath()%>/CheckUserController?op=patient&uname=<%=qt.getPublisher()%>"><%=qt.getPublisher() %></a>
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
              <a href="checkquestion.jsp">
                <button type="button" class="Button Button--blue">
                  <span style="display: inline-flex; align-items: center;">&ZeroWidthSpace;
                    <svg class="Zi Zi--Edit QuestionButton-icon" fill="currentColor" viewBox="0 0 24 24" width="16"
                      height="16">
                      <path
                        d="M4.076 16.966a4.19 4.19 0 0 1 1.05-1.76l8.568-8.569a.524.524 0 0 1 .741 0l2.928 2.927a.524.524 0 0 1 0 .74l-8.568 8.57c-.49.49-1.096.852-1.761 1.051l-3.528 1.058a.394.394 0 0 1-.49-.488l1.06-3.53zM20.558 4.83c.59.59.59 1.546 0 2.136l-1.693 1.692a.503.503 0 0 1-.712 0l-2.812-2.812a.504.504 0 0 1 0-.712l1.693-1.693a1.51 1.51 0 0 1 2.135 0l1.389 1.389z">
                      </path>
                    </svg>
                  </span>
                  返回
                </button>
              </a>
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
                    <svg class="Zi Zi--Comment Button-zi" fill="currentColor" viewBox="0 0 24 24" width="1.2em"
                      height="1.2em">
                      <path
                        d="M10.241 19.313a.97.97 0 0 0-.77.2 7.908 7.908 0 0 1-3.772 1.482.409.409 0 0 1-.38-.637 5.825 5.825 0 0 0 1.11-2.237.605.605 0 0 0-.227-.59A7.935 7.935 0 0 1 3 11.25C3 6.7 7.03 3 12 3s9 3.7 9 8.25-4.373 9.108-10.759 8.063z"
                        fill-rule="evenodd"></path>
                    </svg></span><%=qt.getReplynum() %> 条评论</button></div>

              <div class="QuestionHeader-actions"></div>
            </div>
          </div>
        </div>
      </div>
    </div>
    <div class="container">
      <div class="row justify-content-md-center">
        <div class="col col-md-auto question" style="width: calc(100% - 50px);padding: 50px;">
          <form name="add" action="MainController" method="get">
            <input type="hidden" name="op" value="add">
            <div class="input-group">
              <textarea class="form-control" name="content" style="width:300px;height:300px"
                placeholder="发表一下你对这个病人的问题的看法吧~"></textarea>
            </div>
            <input style="position: absolute;right: 50px;bottom: 10px;" class="btn btn-primary" type="submit"
              value="确认回复">
          </form>
        </div>
      </div>
    </div>
  </div>
</body>

</html>