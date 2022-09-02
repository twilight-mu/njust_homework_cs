package edu.njust.dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;

import edu.njust.entity.Message;
import edu.njust.entity.Reply;

public class MessageDao {
	Connection ct;
	PreparedStatement pstmt;
	public MessageDao()
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
	
	public ArrayList findAllMessage()
	{
		try
		{
			ArrayList al=new ArrayList();
			pstmt=ct.prepareStatement("select * from message");
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
	
	public boolean DelMessage(int maid)
	{
		try
		{
			pstmt=ct.prepareStatement("delete from message where id="+maid);
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
