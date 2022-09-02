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
}
