package edu.njust.service;

import java.util.ArrayList;

import edu.njust.dao.*;
import edu.njust.entity.*;

public class ReplyService {
	public ArrayList getreply(int qid)
	{
		ReplyDao rd=new ReplyDao();
		ArrayList al=rd.findReplyByQid(qid);
		return al;
	}
	
	public boolean addreply(Reply reply)
	{
		ReplyDao rd=new ReplyDao();
		return rd.addnewReply(reply);
	}
	
	public ArrayList findbyreplier(String replier)
	{
		ReplyDao rd=new ReplyDao();
		ArrayList al=rd.findReplyByReplier(replier);
		return al;
	}
}
