package edu.njust.dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;

import edu.njust.entity.Question;
import edu.njust.entity.Reply;

public class ReplyDao {
	Connection ct;
	PreparedStatement pstmt;
	public ReplyDao()
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
	
	public ArrayList findAllReply()
	{
		try
		{
			ArrayList al=new ArrayList();
			pstmt=ct.prepareStatement("select * from reply");
			ResultSet rs=pstmt.executeQuery();
			while(rs.next())
			{
				Reply rp=new Reply();
				rp.setId(rs.getInt(1));
				rp.setContent(rs.getString(2));
				rp.setReplier(rs.getString(3));
				rp.setQid(rs.getInt(4));
				al.add(rp);
			}
			return al;
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return null;
		}
	}
	
	public boolean DelReply(int replyid)
	{
		try
		{
			pstmt=ct.prepareStatement("delete from reply where id="+replyid);
			pstmt.executeUpdate();
			return true;
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return false;
		}
	}
	
	public boolean DelReplyByQid(int qid)
	{
		try
		{
			pstmt=ct.prepareStatement("delete from reply where qid="+qid);
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
