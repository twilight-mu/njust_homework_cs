package edu.njust.entity;

public class Reply {
	private int id;
	private String content;
	private String replier;
	private int qid;
	
	public int getId()
	{
		return this.id;
	}
	public void setId(int id)
	{
		this.id=id;
	}
	
	public String getContent()
	{
		return this.content;
	}
	public void setContent(String content)
	{
		this.content=content;
	}
	
	public String getReplier()
	{
		return this.replier;
	}
	public void setReplier(String replier)
	{
		this.replier=replier;
	}
	
	public int getQid()
	{
		return this.qid;
	}
	public void setQid(int qid)
	{
		this.qid=qid;
	}
}
