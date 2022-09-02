package edu.njust.dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;


import java.util.ArrayList;

import edu.njust.entity.User;

public class UserDao {
	Connection ct;
	PreparedStatement pstmt;
	public UserDao()
	{
		try
		{
			Class.forName("com.mysql.jdbc.Driver").newInstance();
			ct=DriverManager.getConnection("jdbc:mysql://localhost:3306/hospital?useUnicode=true&characterEncoding=utf8","root","root");
			System.out.print(1);
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
			pstmt=ct.prepareStatement("select * from patient where username=?");
			pstmt.setString(1,username);
			ResultSet rs=pstmt.executeQuery();
			User user=new User();
			while(rs.next())
			{
				user.setId(rs.getInt(1));
				user.setName(rs.getString(2));
				user.setPwd(rs.getString(3));
				user.setIsLocked(rs.getInt(10));
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
	
	public ArrayList findAlluser()
	{
		try
		{
			ArrayList al=new ArrayList();
			pstmt=ct.prepareStatement("select * from patient");
			ResultSet rs=pstmt.executeQuery();
			while(rs.next())
			{
				User user=new User();
				user.setId(rs.getInt(1));
				user.setUname(rs.getString(2));
				user.setPwd(rs.getString(3));
				user.setName(rs.getString(4));
				user.setSex(rs.getString(5));
				user.setAge(rs.getString(6));
				user.setPicture(rs.getString(7));
				user.setPhone(rs.getString(8));
				user.setDetail(rs.getString(9));
				al.add(user);
			}
			return al;
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return null;
		}
	}
	
	public boolean addnewUser(User newuser)
	{
		try
		{
			pstmt=ct.prepareStatement("insert into patient(username,password,phone,picture,islocked) values(?,?,?,'moren.jpg',0)");
			pstmt.setString(1,newuser.getUname());
			pstmt.setString(2,newuser.getPwd());
			pstmt.setString(3,newuser.getPhone());
			pstmt.executeUpdate();
			return true;
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return false;
		}
	}
	
	public User findUserByUname(String username)
	{
		try
		{
			pstmt=ct.prepareStatement("select * from patient where username=?");
			pstmt.setString(1,username);
			ResultSet rs=pstmt.executeQuery();
			User user=new User();
			while(rs.next())
			{
				user.setId(rs.getInt(1));
				user.setUname(rs.getString(2));
				user.setPwd(rs.getString(3));
				user.setName(rs.getString(4));
				user.setSex(rs.getString(5));
				user.setAge(rs.getString(6));
				user.setPicture(rs.getString(7));
				user.setPhone(rs.getString(8));
				user.setDetail(rs.getString(9));
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
	
	public int alterinfo(User user)
	{
		try
		{
			pstmt=ct.prepareStatement("UPDATE patient SET name=?,sex=?,age=?,picture=?,detail=? WHERE username = ?");
			pstmt.setString(1,user.getName());
			pstmt.setString(2,user.getSex());
			pstmt.setString(3,user.getAge());
			pstmt.setString(4,user.getPicture());
			pstmt.setString(5,user.getDetail());
			pstmt.setString(6,user.getUname());
			int rs=pstmt.executeUpdate();
			return rs;
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return 0;
		}
	}
	
	public String getpicture(String username)
	{
		try
		{
			pstmt=ct.prepareStatement("select * from patient where username=?");
			pstmt.setString(1,username);
			ResultSet rs=pstmt.executeQuery();
			User user=new User();
			while(rs.next())
			{
				user.setId(rs.getInt(1));
				user.setUname(rs.getString(2));
				user.setPwd(rs.getString(3));
				user.setName(rs.getString(4));
				user.setSex(rs.getString(5));
				user.setAge(rs.getString(6));
				user.setPicture(rs.getString(7));
				user.setPhone(rs.getString(8));
				user.setDetail(rs.getString(9));
				return user.getPicture();
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
