package edu.njust.controller;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import edu.njust.entity.Message;
import edu.njust.service.MessageService;

public class MessageController extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public MessageController() {
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
		if(op.equals("add"))
		{
			String writeto=(String)session.getAttribute("writeto");
			String publisher=(String)session.getAttribute("user_name");
			String content=request.getParameter("content");
			MessageService ms=new MessageService();
			Message ma=new Message();
			ma.setContent(content);
			ma.setPublisher(publisher);
			ma.setReceiver(writeto);
			boolean result=ms.addmessage(ma);
			response.sendRedirect("checkuser.jsp");
		}
		else if(op.equals("check"))
		{
			String username=(String)session.getAttribute("user_name");
			MessageService ms=new MessageService();
			ArrayList al1=ms.findByReceiver(username);
			ArrayList al2=ms.findByPublisher(username);
			session.setAttribute("al1", al1);
			session.setAttribute("al2", al2);
			response.sendRedirect("mymessage.jsp");
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
