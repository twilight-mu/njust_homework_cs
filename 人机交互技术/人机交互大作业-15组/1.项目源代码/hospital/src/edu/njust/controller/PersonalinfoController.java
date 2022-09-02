package edu.njust.controller;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import edu.njust.entity.User;
import edu.njust.service.UserService;

public class PersonalinfoController extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public PersonalinfoController() {
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
		String op=request.getParameter("op");
		HttpSession session = request.getSession();
		String username=(String)session.getAttribute("user_name");
		if(op.equals("check"))
		{
			UserService us=new UserService();
			User user=us.checkinfo(username);
			session.setAttribute("userinfo",user);
			session.setAttribute("user_name",user.getUname());
			session.setAttribute("picture",user.getPicture());
			response.sendRedirect("personal.jsp");
		}
		else if(op.equals("alter"))
		{
			System.out.println("I am in alter");
			String picture=request.getParameter("picture");
			String uname=(String)session.getAttribute("user_name");
			String name=request.getParameter("name");
			String sex=request.getParameter("sex");
			String age=request.getParameter("age");
			String phone=request.getParameter("phone");
			String detail=request.getParameter("detail");
			
			User user=new User();
			if(picture==null)
			{
				user.setPicture("moren.jpg");
			}
			else
			{
				user.setPicture(picture);
			}
			user.setUname(uname);
			user.setName(name);
			user.setSex(sex);
			user.setAge(age);
			user.setPhone(phone);
			user.setDetail(detail);
			UserService us=new UserService();
			int rs=us.alterinfo(user);
			user=us.checkinfo(username);
			session.setAttribute("userinfo",user);
			session.setAttribute("user_name",user.getUname());
			session.setAttribute("picture",user.getPicture());
			response.sendRedirect("personal.jsp");
			
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
