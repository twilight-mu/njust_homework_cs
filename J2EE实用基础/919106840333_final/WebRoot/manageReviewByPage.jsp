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
    
    <title>My JSP 'MyJsp.jsp' starting page</title>
    
	<meta name="content-type" content="text/html; charset=UTF-8">
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
	<script type="text/javascript" >
	  function inValidateSession(){
	    session.invalidate();
	  }
	  
	  function delConfirm(){
	    if(confirm("确定删除吗？")){
	      return true;
	    }
	    else{
	      return false;
	    }
	  
	  }
	  
	</script>

  </head>
  
  <body>
  <form name="search"  action="addPayInfo.jsp">
     <table border="1" width="150">
        <tr>
          <td align = "center"><input  type = "submit" value = "提取费用"></td>
          
        </tr>
   </table>
   <table border="1" width="800" id = "courseT">       
      <tr>
      	  <td align = "center">序号</td>
          <td align = "center">送审机构</td>
          <td align = "center">类型</td>
          <td align = "center">费用</td>
          <td align = "center">是否支付</td>
          <td align = "center">日期</td>
        </tr>
        <% 
          Vector<Review> curVec = (Vector<Review>)request.getAttribute("allCourse");
          Review review = null;
          if(!curVec.isEmpty()){
             int size = curVec.size();
             int index =1; //starting from 1
	      	 while (size> 0){	      	    
			    review =(Review) curVec.get(size-1);
		     	if(review!=null&&review.getIsPayed()==false)
		     	{
		     	%>
		     	<tr>
		     	  <td align = "center"><input type="checkbox" name="chk" id="chk" value=<%=review.getFee()%>> <%=index%></td>
		     	  <td align = "center"><%=review.getOrganization()%></td>
		     	  <td align = "center"><%=review.getPaperTitle()%></td>
		     	  <td align = "center"><%=review.getFee()%></td>
		     	  <td align = "center">未完成支付</td>
		     	  <% Date date = review.getCreateDate();
		     	     if(date!=null)
		     	     {
		     	  %>
		     	    <td align = "center"><%=date.toLocaleString() %></td>
		     	  <% 
		     	  }
		     	  else 
		     	  { %>
		     	     <td align = "center">未填写日期</td>
		     	  <% } %>
		     	     
		     
		     	</tr>
		     	<% 
			//	   System.out.println(course.getName()+"   "+course.getCreator()+"   "+course.getCreateDate());
				index = index +1;
		
			    }
			    
			    size = size -1;
		     }
          }   
        		
       %>
      </table>
			<%
				CoursePage cp=(CoursePage)session.getAttribute("page");
				int nowpage=cp.getNowpage();
				int maxpage=cp.getMaxpage();
				int minpage=cp.getMinpage(); 
				System.out.println(nowpage);
				System.out.println(maxpage);
				System.out.println(minpage);
			%>
			
					<a
	    				href="<%=request.getContextPath()%>/courseReview?operation=query&pg=first">[首页]
	    			</a>&nbsp;
			
			<%  if(nowpage!=1){%>
					<a
	    				href="<%=request.getContextPath()%>/courseReview?operation=query&pg=prev">[上一页]
	    			</a>&nbsp;		
	    		<%} %>
	    			第<%=nowpage%>页\共<%=maxpage%>页
	    		<%
	    		if(nowpage!=maxpage)
	    		{ %>
	    			<a
	    				href="<%=request.getContextPath()%>/courseReview?operation=query&pg=next">[下一页]
	    			</a>&nbsp;
	    		<%} %>
	    		
	    			<a
	    				href="<%=request.getContextPath()%>/courseReview?operation=query&pg=last">[尾页]
	    			</a>&nbsp;
	    		
	    		<%session.setAttribute("page",cp); %>
     </form>
  </body>
</html>

