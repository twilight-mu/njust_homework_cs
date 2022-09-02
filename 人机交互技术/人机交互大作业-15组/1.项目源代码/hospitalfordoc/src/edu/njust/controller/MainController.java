package edu.njust.controller;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import edu.njust.entity.Question;
import edu.njust.entity.Reply;
import edu.njust.service.PatientService;
import edu.njust.service.QuestionService;
import edu.njust.service.ReplyService;

public class MainController extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public MainController() {
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
		if(op.equals("main"))
		{
			PatientService ps=new PatientService();
			ArrayList al1=ps.findAll();
			session.setAttribute("al1",al1);
			QuestionService qs=new QuestionService();
			ArrayList al2=qs.findAll();
			session.setAttribute("al2",al2);
			response.sendRedirect("main.jsp");
		}
		else if(op.equals("add"))
		{

			Question qt=(Question)session.getAttribute("qt");
			String content=request.getParameter("content");
			String username=(String)session.getAttribute("user_name"); 
			Reply reply=new Reply();
			reply.setReplier(username);
			reply.setContent(content);
			reply.setQid(qt.getId());
			ReplyService rs=new ReplyService();
			boolean result=rs.addreply(reply);
			response.sendRedirect("addreply.jsp");
		}
		else if(op.equals("qb"))
		{
			String major=request.getParameter("major");
			if(major.equals("all"))
			{
				QuestionService qs=new QuestionService();
				ArrayList al=qs.findAll();
				session.setAttribute("al",al);
				session.setAttribute("major","全部");
				response.sendRedirect("questionbar.jsp");
			}
			else
			{
				QuestionService qs=new QuestionService();
				ArrayList al=qs.findByMajor(major);
				session.setAttribute("al",al);
				session.setAttribute("major",major);
				response.sendRedirect("questionbar.jsp");
			}
		}
		else if(op.equals("myreply"))
		{
			ReplyService rs=new ReplyService();
			String replier=(String)session.getAttribute("user_name");
			ArrayList al=rs.findbyreplier(replier);
			session.setAttribute("al",al);
			response.sendRedirect("myreply.jsp");
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
