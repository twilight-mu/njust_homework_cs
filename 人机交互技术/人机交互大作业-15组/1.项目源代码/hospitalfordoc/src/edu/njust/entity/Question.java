package edu.njust.entity;

public class Question {
	private int id;
	private String title;
	private String content;
	private String publisher;
	private int replynum;
	private String major;
	
	public int getId()
	{
		return this.id;
	}
	public void setId(int id)
	{
		this.id=id;
	}
	
	public String getTitle()
	{
		return this.title;
	}
	public void setTitle(String title)
	{
		this.title=title;
	}
	
	public String getContent()
	{
		return this.content;
	}
	public void setContent(String content)
	{
		this.content=content;
	}
	
	public String getPublisher()
	{
		return this.publisher;
	}
	public void setPublisher(String publisher)
	{
		this.publisher=publisher;
	}
	
	public int getReplynum()
	{
		return this.replynum;
	}
	public void setRelpynum(int replynum)
	{
		this.replynum=replynum;
	}
	
	public String getMajor()
	{
		return this.major;
	}
	public void setMajor(String major)
	{
		this.major=major;
	}
}
