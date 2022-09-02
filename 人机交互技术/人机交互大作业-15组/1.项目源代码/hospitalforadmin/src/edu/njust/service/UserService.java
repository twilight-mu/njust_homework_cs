package edu.njust.service;

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
		return 0;//登录成功
	}
	
}
