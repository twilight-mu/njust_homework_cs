package edu.njust.service;


import java.util.ArrayList;

import edu.njust.dao.*;
import edu.njust.entity.Message;

public class MessageService {
	public boolean addmessage(Message ms)
	{
		MessageDao md=new MessageDao();
		return md.addMessage(ms);
	}
	
	public ArrayList findByPublisher(String publisher)
	{
		MessageDao md=new MessageDao();
		return md.findMessageByPublisher(publisher);
	}
	
	public ArrayList findByReceiver(String receiver)
	{
		MessageDao md=new MessageDao();
		return md.findMessageByReceiver(receiver);
	}
}
