package edu.njust.entity;

public class User 
{
	private int userId;
	private String userName;
	private String password;
	public User(){
		
	}	
	public int getId()
	{
		return this.userId;
	}
	public void setId(int userId)
	{
		this.userId=userId;
	}
	
	public String getUname()
	{
		return this.userName;
	}
	public void setUname(String userName)
	{
		this.userName=userName;
	}
	
	public String getPwd()
	{
		return this.password;
	}
	public void setPwd(String password)
	{
		this.password=password;
	}
	
}
