package edu.njust.dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;

import edu.njust.entity.Reply;
import edu.njust.entity.User;

public class ReplyDao {
	Connection ct;
	PreparedStatement pstmt;
	public ReplyDao()
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
	
	public ArrayList findReplyByQid(int qid)
	{
		try
		{
			ArrayList al=new ArrayList();
			pstmt=ct.prepareStatement("select * from reply where qid=?");
			pstmt.setInt(1,qid);
			ResultSet rs=pstmt.executeQuery();
			while(rs.next())
			{
				Reply reply=new Reply();
				reply.setId(rs.getInt(1));
				reply.setContent(rs.getString(2));
				reply.setReplier(rs.getString(3));
				reply.setQid(rs.getInt(4));
				al.add(reply);
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
