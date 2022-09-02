package edu.njust.dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;


import edu.njust.entity.Question;
import edu.njust.entity.User;

public class QuestionDao {
	Connection ct;
	PreparedStatement pstmt;
	public QuestionDao()
	{
		try
		{
			Class.forName("com.mysql.jdbc.Driver").newInstance();
			ct=DriverManager.getConnection("jdbc:mysql://localhost:3306/hospital?useUnicode=true&characterEncoding=utf8","root","root");
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
	
	public ArrayList findAllQuestion()
	{
		try
		{
			ArrayList al=new ArrayList();
			pstmt=ct.prepareStatement("select * from question order by replynum");
			ResultSet rs=pstmt.executeQuery();
			while(rs.next())
			{
				Question qs=new Question();
				qs.setId(rs.getInt(1));
				qs.setTitle(rs.getString(2));
				qs.setContent(rs.getString(3));
				qs.setPublisher(rs.getString(4));
				qs.setRelpynum(rs.getInt(5));
				qs.setMajor(rs.getString(6));
				al.add(qs);
			}
			return al;
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return null;
		}
	}
	
	public boolean addnewQuestion(Question question)
	{
		try
		{
			pstmt=ct.prepareStatement("insert into question(title,content,publisher,replynum,major) values(?,?,?,0,?)");
			pstmt.setString(1,question.getTitle());
			pstmt.setString(2,question.getContent());
			pstmt.setString(3,question.getPublisher());
			pstmt.setString(4,question.getMajor());
			pstmt.executeUpdate();
			return true;
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return false;
		}
	}
	
	public ArrayList findQuestionByMajor(String major)
	{
		try
		{
			ArrayList al=new ArrayList();
			pstmt=ct.prepareStatement("select * from question where major=?");
			pstmt.setString(1,major);
			ResultSet rs=pstmt.executeQuery();
			while(rs.next())
			{
				Question qs=new Question();
				qs.setId(rs.getInt(1));
				qs.setTitle(rs.getString(2));
				qs.setContent(rs.getString(3));
				qs.setPublisher(rs.getString(4));
				qs.setRelpynum(rs.getInt(5));
				qs.setMajor(rs.getString(6));
				al.add(qs);
			}
			return al;
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return null;
		}
	}
	
	public Question findQuestionById(int id)
	{
		try
		{
			Question qs=new Question();
			pstmt=ct.prepareStatement("select * from question where id=?");
			pstmt.setInt(1,id);
			ResultSet rs=pstmt.executeQuery();
			while(rs.next())
			{
				qs.setId(rs.getInt(1));
				qs.setTitle(rs.getString(2));
				qs.setContent(rs.getString(3));
				qs.setPublisher(rs.getString(4));
				qs.setRelpynum(rs.getInt(5));
				qs.setMajor(rs.getString(6));
				return qs;
			}
			return null;
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return null;
		}
	}
	
	public ArrayList findQuestionByPublisher(String publisher)
	{
		try
		{
			ArrayList al=new ArrayList();
			pstmt=ct.prepareStatement("select * from question where publisher=?");
			pstmt.setString(1,publisher);
			ResultSet rs=pstmt.executeQuery();
			while(rs.next())
			{
				Question qs=new Question();
				qs.setId(rs.getInt(1));
				qs.setTitle(rs.getString(2));
				qs.setContent(rs.getString(3));
				qs.setPublisher(rs.getString(4));
				qs.setRelpynum(rs.getInt(5));
				qs.setMajor(rs.getString(6));
				al.add(qs);
			}
			return al;
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return null;
		}
	}
}
