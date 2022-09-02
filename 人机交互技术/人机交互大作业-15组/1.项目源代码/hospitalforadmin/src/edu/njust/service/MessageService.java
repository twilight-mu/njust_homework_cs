package edu.njust.service;

import java.util.ArrayList;

import edu.njust.dao.MessageDao;
import edu.njust.dao.ReplyDao;

public class MessageService {
	public ArrayList findAll()
	{
		MessageDao md=new MessageDao();
		return md.findAllMessage();
	}
	
	public boolean delMessage(int maid)
	{
		MessageDao md=new MessageDao();
		boolean rs=md.DelMessage(maid);
		return rs;
	}
}
