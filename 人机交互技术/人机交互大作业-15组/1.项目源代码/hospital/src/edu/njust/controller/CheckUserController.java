package edu.njust.controller;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import edu.njust.service.*;
import edu.njust.entity.*;

public class CheckUserController extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public CheckUserController() {
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

		request.setCharacterEncoding("gb2312");
		response.setContentType("text/html;charset=UTF-8");
		response.setCharacterEncoding("UTF-8");
		HttpSession session = request.getSession();
		String op=request.getParameter("op");
		String uname=request.getParameter("uname");
		if(op.equals("user"))
		{
			UserService us=new UserService();
			User user=us.checkinfo(uname);
			session.setAttribute("info",user);
			session.setAttribute("op", "user");
			response.sendRedirect("checkuser.jsp");
		}
		else if(op.equals("doctor"))
		{
			DoctorService ds=new DoctorService();
			Doctor doctor=ds.findByUname(uname);
			session.setAttribute("info",doctor);
			session.setAttribute("op", "doctor");
			response.sendRedirect("checkuser.jsp");
		}
		else
		{
			UserService us=new UserService();
			int result=us.checksignup(uname);
			if(result==1)
			{
				User user=us.checkinfo(uname);
				session.setAttribute("info",user);
				session.setAttribute("op", "user");
				response.sendRedirect("checkuser.jsp");
			}
			else
			{
				DoctorService ds=new DoctorService();
				Doctor doctor=ds.findByUname(uname);
				session.setAttribute("info",doctor);
				session.setAttribute("op", "doctor");
				response.sendRedirect("checkuser.jsp");
			}
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

		response.setContentType("text/html");
		PrintWriter out = response.getWriter();
		out.println("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">");
		out.println("<HTML>");
		out.println("  <HEAD><TITLE>A Servlet</TITLE></HEAD>");
		out.println("  <BODY>");
		out.print("    This is ");
		out.print(this.getClass());
		out.println(", using the POST method");
		out.println("  </BODY>");
		out.println("</HTML>");
		out.flush();
		out.close();
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
