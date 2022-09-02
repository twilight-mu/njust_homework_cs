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

public class SignupController extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public SignupController() {
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
		String checkcode=(String)session.getAttribute("CKECKCODE");
		String code=request.getParameter("checkcode");
		
		if(checkcode!= null && code.equals(checkcode))
		{

			String newuser=request.getParameter("newuser");
			String newpwd1=request.getParameter("newpwd1");
			String newpwd2=request.getParameter("newpwd2");
			String phone=request.getParameter("phone");
			System.out.println(newuser);
			System.out.println(newpwd1);
			System.out.println(newpwd2);
			if(!newpwd1.equals(newpwd2))
			{
				request.setAttribute("error_code", new Integer(3));//密码不匹配
	        	request.getRequestDispatcher("login.jsp").forward(request,response);
			}
			else
			{
				UserService us=new UserService();
				int result=us.checksignup(newuser);
				if(result==1)
				{
					request.setAttribute("error_code", new Integer(4));//用户名重复
		        	request.getRequestDispatcher("login.jsp").forward(request,response);
				}
				else
				{
					User user=new User();
					user.setUname(newuser);
					user.setPwd(newpwd1);
					user.setPhone(phone);
					boolean rs=us.addnewUser(user);
					if(rs==true)
					{
						request.setAttribute("suc_code", new Integer(1));
						request.getRequestDispatcher("login.jsp").forward(request,response);
					}
					else
					{
						request.setAttribute("error_code", new Integer(5));//未知错误
			        	request.getRequestDispatcher("login.jsp").forward(request,response);
					}
				}
			}
		}
		else
		{
			request.setAttribute("error_code", new Integer(6));
        	request.getRequestDispatcher("login.jsp").forward(request,response);
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
