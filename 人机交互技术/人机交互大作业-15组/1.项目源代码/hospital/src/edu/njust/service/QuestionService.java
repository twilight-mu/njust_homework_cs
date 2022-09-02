package edu.njust.service;

import java.util.ArrayList;

import edu.njust.dao.*;
import edu.njust.entity.Question;

public class QuestionService {
	public ArrayList findAll()
	{
		QuestionDao qd=new QuestionDao();
		return qd.findAllQuestion();
	}
	
	public boolean addnewQuestion(Question question)
	{
		QuestionDao qd=new QuestionDao();
		return qd.addnewQuestion(question);
	}
	
	public ArrayList findByMajor(String major)
	{
		QuestionDao qd=new QuestionDao();
		return qd.findQuestionByMajor(major);
	}
	
	public Question findById(int qid)
	{
		QuestionDao qd=new QuestionDao();
		return qd.findQuestionById(qid);
	}
	
	public ArrayList findByPublisher(String publisher)
	{
		QuestionDao qd=new QuestionDao();
		return qd.findQuestionByPublisher(publisher);
	}
}
