package edu.njust.dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;

import edu.njust.entity.*;

public class MessageDao {
	Connection ct;
	PreparedStatement pstmt;
	public MessageDao()
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
	
	public boolean addMessage(Message ms)
	{
		try
		{
			pstmt=ct.prepareStatement("insert into message(content,publisher,receiver) values(?,?,?)");
			pstmt.setString(1,ms.getContent());
			pstmt.setString(2,ms.getPublisher());
			pstmt.setString(3,ms.getReceiver());
			pstmt.executeUpdate();
			return true;
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return false;
		}
	}
	
	public ArrayList findMessageByPublisher(String publisher)
	{
		try
		{
			ArrayList al=new ArrayList();
			pstmt=ct.prepareStatement("select * from message where publisher=?");
			pstmt.setString(1,publisher);
			ResultSet rs=pstmt.executeQuery();
			while(rs.next())
			{
				Message ma=new Message();
				ma.setId(rs.getInt(1));
				ma.setContent(rs.getString(2));
				ma.setPublisher(rs.getString(3));
				ma.setReceiver(rs.getString(4));
				al.add(ma);
			}
			return al;
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return null;
		}
	}
	
	public ArrayList findMessageByReceiver(String receiver)
	{
		try
		{
			ArrayList al=new ArrayList();
			pstmt=ct.prepareStatement("select * from message where receiver=?");
			pstmt.setString(1,receiver);
			ResultSet rs=pstmt.executeQuery();
			while(rs.next())
			{
				Message ma=new Message();
				ma.setId(rs.getInt(1));
				ma.setContent(rs.getString(2));
				ma.setPublisher(rs.getString(3));
				ma.setReceiver(rs.getString(4));
				al.add(ma);
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
