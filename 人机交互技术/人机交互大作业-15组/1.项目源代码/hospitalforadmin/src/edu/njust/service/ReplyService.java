package edu.njust.service;

import java.util.ArrayList;

import edu.njust.dao.QuestionDao;
import edu.njust.dao.ReplyDao;

public class ReplyService {
	public ArrayList findAll()
	{
		ReplyDao rd=new ReplyDao();
		return rd.findAllReply();
	}
	
	public boolean delReply(int replyid)
	{
		ReplyDao rd=new ReplyDao();
		boolean rs=rd.DelReply(replyid);
		return rs;
	}
	
	public boolean delReplyByQid(int qid)
	{
		ReplyDao rd=new ReplyDao();
		boolean rs=rd.DelReplyByQid(qid);
		return rs;
	}
}
