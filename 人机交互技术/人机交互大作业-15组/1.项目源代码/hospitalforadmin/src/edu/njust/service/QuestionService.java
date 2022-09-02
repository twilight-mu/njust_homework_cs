package edu.njust.service;

import java.util.ArrayList;

import edu.njust.dao.QuestionDao;

public class QuestionService {
	public ArrayList findAll()
	{
		QuestionDao qd=new QuestionDao();
		return qd.findAllQuestion();
	}
	
	public boolean delQuestion(int qid)
	{
		QuestionDao qd=new QuestionDao();
		boolean rs=qd.DelQuestion(qid);
		return rs;
	}
}
