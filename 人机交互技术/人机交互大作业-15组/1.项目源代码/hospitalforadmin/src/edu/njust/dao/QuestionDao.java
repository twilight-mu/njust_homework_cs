package edu.njust.dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;

import edu.njust.entity.Question;

public class QuestionDao {
	Connection ct;
	PreparedStatement pstmt;
	public QuestionDao()
	{
		try
		{
			Class.forName("com.mysql.jdbc.Driver").newInstance();
			ct=DriverManager.getConnection("jdbc:mysql://localhost:3306/hospital","root","root");
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
			pstmt=ct.prepareStatement("select * from question order by id");
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
	
	public boolean DelQuestion(int qtid)
	{
		try
		{
			pstmt=ct.prepareStatement("delete from question where id="+qtid);
			pstmt.executeUpdate();
			return true;
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return false;
		}
	}
}
