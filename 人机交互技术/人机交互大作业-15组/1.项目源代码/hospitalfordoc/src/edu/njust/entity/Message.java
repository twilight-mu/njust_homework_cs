package edu.njust.entity;

public class Message {
	private int id;
	private String content;
	private String publisher;
	private String receiver;
	
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
	
	public String getPublisher()
	{
		return this.publisher;
	}
	public void setPublisher(String publisher)
	{
		this.publisher=publisher;
	}
	
	public String getReceiver()
	{
		return this.receiver;
	}
	public void setReceiver(String receiver)
	{
		this.receiver=receiver;
	}
}
