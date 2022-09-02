package edu.njust.controller;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Calendar;
import java.util.Date;
import java.util.Vector;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import edu.njust.dao.*;
import edu.njust.entity.*;
import edu.njust.service.*;

public class CourseReviewServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public CourseReviewServlet() {
		super();
	}

	/**
	 * Destruction of the servlet. <br>
	 */
	public void destroy() {
		super.destroy(); // Just puts "destroy" string in log
		// Put your code here
	}

	/**
	 * The doGet method of the servlet. <br>
	 *
	 * This method is called when a form has its tag value method equals to get.
	 * 
	 * @param request the request send by the client to the server
	 * @param response the response send by the server to the client
	 * @throws ServletException if an error occurred
	 * @throws IOException if an error occurred
	 */
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		request.setCharacterEncoding("utf-8");	
		HttpSession session = request.getSession(false);
		//session.invalidate();
		//System.out.println(session);
		
		String operation = request.getParameter("operation");
		//String curName = request.getParameter("cName");
		
		//Course course = null;
		//CourseService cs = new CourseService();
		Review review=null;
		ReviewService rs=new ReviewService();
		int result = 0 ;
		/*
		if(operation.equals("add"))
		{
			String curCreator = request.getParameter("cCreator");
			String curDate = request.getParameter("cDate");
			Date date = null;
			if(curDate!=null){
				//2020-04-07 12:43
				int year = Integer.parseInt(curDate.substring(0, 4));
				int month = Integer.parseInt(curDate.substring(5, 7));
				int day = Integer.parseInt(curDate.substring(8, 10));
				int hours = Integer.parseInt(curDate.substring(11, 13));
				int minutes = Integer.parseInt(curDate.substring(14, 16));
				
				Calendar rightNow = Calendar.getInstance();
				rightNow.set(year, month-1, day, hours, minutes);
				date = rightNow.getTime();
			    course = new Course(curName,curCreator,date);
			}else 
			{
			  course = new Course(curName,curCreator);
			}
			if(course!=null && cs.addNewCourse(course)){
				result = 1; 
			}else {
				result = -1; 
			}
		}else if(operation.equals("del"))
		{
			course = new Course(curName,null,null);
			if(cs.delCourse(course))
			{
				result = 2; 
			}else
			{
				result = -2; 
			}	
		}
		else if(operation.equals("del1"))
		{
			Vector<Course> curVec=cs.findAllCourses();
			request.setAttribute("allCourse", curVec);
			request.getRequestDispatcher("delCourse.jsp").forward(request,response);
		}
		else if(operation.equals("del2"))
		{
			
			String s[]=request.getParameterValues("chk");
			for(int i=0;i<s.length;i++)
			{
				course = new Course(s[i],null,null);
				if(cs.delCourse(course))
				{
					result = 2; 
				}
				else
				{
					result = -2; 
					break;
				}
			}
		}
		else if(operation.equals("mod"))
		{
			String curCreator = request.getParameter("cCreator");
			String curDate = request.getParameter("cDate");
			if(curDate!=null)
			{
				//2020-04-07 12:43
				
				int year = Integer.parseInt(curDate.substring(0, 4));
				int month = Integer.parseInt(curDate.substring(5, 7));
				int day = Integer.parseInt(curDate.substring(8, 10));
				int hours=0;
				int minutes=0;
				if(curDate.length()>10)
				{
				   hours = Integer.parseInt(curDate.substring(11, 13));
				   minutes = Integer.parseInt(curDate.substring(14, 16));
				}
				
				//System.out.println("year:=  "+year);
				Calendar rightNow = Calendar.getInstance();
				rightNow.set(year, month-1, day, hours, minutes);
				Date date = rightNow.getTime();
				
			    course = new Course(curName,curCreator,date);
			}
			if(cs.modifyCourse(course))
			{
				result = 5; 
			}else 
			{
				result = -5; 
			}
			
		}else if(operation.equals("modReq")){			
			course = cs.findCourseByName(curName);
			if(course != null){
				
				result = 3;				
			}				
		}else */
		if(operation.equals("query"))
		{
			result = 4;
		}
		
		switch(result)
		{
			case 1:			
			case 4:
			case 2:
			case 5:
				//Vector<Course> curVec = cs.findAllCourses();
				CoursePage cp=(CoursePage)session.getAttribute("page");
				String pg=request.getParameter("pg");
				if(rs.getCountofReviews()%5==0)
				{
					cp.setMaxpage(rs.getCountofReviews()/5);
				}
				else
				{
					cp.setMaxpage(rs.getCountofReviews()/5+1);
				}
				int nowpage=cp.getNowpage();
				int maxpage=cp.getMaxpage();
				if(pg.equals("prev"))
				{
					cp.setNowpage(nowpage-1);
				}
				else if(pg.equals("next"))
				{
					cp.setNowpage(nowpage+1);
				}
				else if(pg.equals("first"))
				{
					cp.setNowpage(1);
				}
				else if(pg.equals("last"))
				{
					cp.setNowpage(maxpage);
				}
				nowpage=cp.getNowpage();
				Vector<Review> curVec=rs.findByReviewpage((nowpage-1)*5,5);
				request.setAttribute("allCourse", curVec);
				session.setAttribute("page",cp);
				request.getRequestDispatcher("manageReviewByPage.jsp").forward(request,response);
				break;
			/*case 3:
				request.setAttribute("curCourse", course);
				request.getRequestDispatcher("modifyCourse.jsp").forward(request,response);
				break;
			case -1:
			case -2:
			case -5:*/
			default:
				request.setAttribute("error_code", result);
				request.getRequestDispatcher("failure.jsp").forward(request,response);
				break;
		}
		
	}

	/**
	 * The doPost method of the servlet. <br>
	 *
	 * This method is called when a form has its tag value method equals to post.
	 * 
	 * @param request the request send by the client to the server
	 * @param response the response send by the server to the client
	 * @throws ServletException if an error occurred
	 * @throws IOException if an error occurred
	 */
	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

	
	}

	/**
	 * Initialization of the servlet. <br>
	 *
	 * @throws ServletException if an error occurs
	 */
	public void init() throws ServletException {
		// Put your code here
	}

}
