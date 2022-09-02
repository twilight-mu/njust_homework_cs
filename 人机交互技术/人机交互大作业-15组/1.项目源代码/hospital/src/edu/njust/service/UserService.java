package edu.njust.service;

import java.util.ArrayList;
import java.util.Iterator;

import edu.njust.dao.UserDao;
import edu.njust.entity.User;

public class UserService {
	public int checklogin(User user1)
	{
		UserDao ud=new UserDao();
		User user2=ud.checkUser(user1.getUname());
		if(user2==null)
		{
			return 1;//用户不存在
		}
		else
		{
			if(!user1.getPwd().equals(user2.getPwd()))
				return 2;//密码错误
		}
		if(user2.getIsLocked()==1)
		{
			return 7;//账号被封
		}
		return 0;//登录成功
	}
	
	public int checksignup(String newname)
	{
		UserDao ud=new UserDao();
		ArrayList al=ud.findAlluser();
		Iterator iter=al.iterator();
		while(iter.hasNext())
		{
			User ur=(User)iter.next();
			String uname=ur.getUname();
			if(uname.equals(newname))
			{
				return 1;//用户名重复
			}
		} 
		return 0;//注册信息无误
	}
	
	public boolean addnewUser(User newuser)
	{
		UserDao ud=new UserDao();
		return ud.addnewUser(newuser);
	}
	
	public User checkinfo(String username)
	{
		UserDao ud=new UserDao();
		return ud.findUserByUname(username);
	}
	
	public int alterinfo(User user)
	{
		UserDao ud=new UserDao();
		return ud.alterinfo(user);
	}
	
	public String getpicture(String username)
	{
		UserDao ud=new UserDao();
		return ud.getpicture(username);
	}
}
