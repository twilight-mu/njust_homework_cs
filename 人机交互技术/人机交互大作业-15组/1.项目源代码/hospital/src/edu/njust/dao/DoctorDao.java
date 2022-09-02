package edu.njust.dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;

import edu.njust.entity.*;

public class DoctorDao {
	Connection ct;
	PreparedStatement pstmt;
	public DoctorDao()
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
	
	public ArrayList findAllDoctor()
	{
		try
		{
			ArrayList al=new ArrayList();
			pstmt=ct.prepareStatement("select * from doctor");
			ResultSet rs=pstmt.executeQuery();
			while(rs.next())
			{
				Doctor user=new Doctor();
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
	
	public Doctor findDoctorByUname(String username)
	{
		try
		{
			
			pstmt=ct.prepareStatement("select * from doctor where username=?");
			pstmt.setString(1,username);
			ResultSet rs=pstmt.executeQuery();
			while(rs.next())
			{
				Doctor user=new Doctor();
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
}
