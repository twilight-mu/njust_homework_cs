package edu.njust.controller;

import edu.njust.entity.Doctor;
import edu.njust.entity.Patient;
import edu.njust.service.*;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

public class UserController extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public UserController() {
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
		if(op.equals("all"))
		{
			PatientService ps=new PatientService();
			DoctorService ds=new DoctorService();
			ArrayList al1=ps.findAllPatient();
			session.setAttribute("al1",al1);
			
			ArrayList al2=ds.findAllDoctor();
			session.setAttribute("al2",al2);
			response.sendRedirect("userlist.jsp");
		}
		else if(op.equals("lockdt"))
		{
			String uname=request.getParameter("user");
			DoctorService ds=new DoctorService();
			PatientService ps=new PatientService();
			int rs=ds.setLocked(1, uname);
			ArrayList al1=ps.findAllPatient();
			session.setAttribute("al1",al1);
			ArrayList al2=ds.findAllDoctor();
			session.setAttribute("al2",al2);
			response.sendRedirect("userlist.jsp");
		}
		else if(op.equals("releasedt"))
		{
			String uname=request.getParameter("user");
			DoctorService ds=new DoctorService();
			PatientService ps=new PatientService();
			int rs=ds.setLocked(0, uname);
			ArrayList al1=ps.findAllPatient();
			session.setAttribute("al1",al1);
			ArrayList al2=ds.findAllDoctor();
			session.setAttribute("al2",al2);
			response.sendRedirect("userlist.jsp");
		}
		else if(op.equals("detaildt"))
		{
			String uname=request.getParameter("user");
			DoctorService ds=new DoctorService();
			Doctor dt=ds.findByUname(uname);
			session.setAttribute("type","dt");
			session.setAttribute("udetail",dt);
			response.sendRedirect("userdetail.jsp");
		}
		else if(op.equals("lockpt"))
		{
			String uname=request.getParameter("user");
			DoctorService ds=new DoctorService();
			PatientService ps=new PatientService();
			int rs=ps.setLocked(1, uname);
			ArrayList al1=ps.findAllPatient();
			session.setAttribute("al1",al1);
			ArrayList al2=ds.findAllDoctor();
			session.setAttribute("al2",al2);
			response.sendRedirect("userlist.jsp");
		}
		else if(op.equals("releasept"))
		{
			String uname=request.getParameter("user");
			DoctorService ds=new DoctorService();
			PatientService ps=new PatientService();
			int rs=ps.setLocked(0, uname);
			ArrayList al1=ps.findAllPatient();
			session.setAttribute("al1",al1);
			ArrayList al2=ds.findAllDoctor();
			session.setAttribute("al2",al2);
			response.sendRedirect("userlist.jsp");
		}
		else if(op.equals("detailpt"))
		{
			String uname=request.getParameter("user");
			PatientService ps=new PatientService();
			Patient pt=ps.findByUname(uname);
			session.setAttribute("type","pt");
			session.setAttribute("udetail",pt);
			response.sendRedirect("userdetail.jsp");
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
