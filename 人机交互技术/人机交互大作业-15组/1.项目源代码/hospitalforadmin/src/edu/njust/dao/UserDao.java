package edu.njust.dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import edu.njust.entity.User;

public class UserDao {
	Connection ct;
	PreparedStatement pstmt;
	public UserDao()
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
	
	public User checkUser(String username)
	{
		try
		{
			pstmt=ct.prepareStatement("select * from admin where username=?");
			pstmt.setString(1,username);
			ResultSet rs=pstmt.executeQuery();
			User user=new User();
			while(rs.next())
			{
				user.setId(rs.getInt(1));
				user.setUname(rs.getString(2));
				user.setPwd(rs.getString(3));
				return user;
			}
			return null;
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return null;
		}
	}
}
