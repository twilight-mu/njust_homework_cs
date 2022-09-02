package edu.njust.entity;

public class User 
{
	private int userId;
	private String userName;
	private String password;
	private String name;
	private String sex;
	private String age;
	private String picture;
	private String phone;
	private String detail;
	private int isLocked;
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
	
	public String getName()
	{
		return this.name;
	}
	public void setName(String name)
	{
		this.name=name;
	}
	
	public String getSex()
	{
		return this.sex;
	}
	public void setSex(String sex)
	{
		this.sex=sex;
	}
	
	public String getAge()
	{
		return this.age;
	}
	public void setAge(String age)
	{
		this.age=age;
	}
	
	public String getPicture()
	{
		return this.picture;
	}
	public void setPicture(String picture)
	{
		this.picture=picture;
	}
	
	public String getPhone()
	{
		return this.phone;
	}
	public void setPhone(String phone)
	{
		this.phone=phone;
	}
	
	public String getDetail()
	{
		return this.detail;
	}
	public void setDetail(String detail)
	{
		this.detail=detail;
	}
	
	public int getIsLocked()
	{
		return this.isLocked;
	}
	public void setIsLocked(int isLocked)
	{
		this.isLocked=isLocked;
	}

}
