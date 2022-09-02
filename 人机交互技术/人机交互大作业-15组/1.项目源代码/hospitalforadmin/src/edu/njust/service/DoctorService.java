package edu.njust.service;

import java.util.ArrayList;

import edu.njust.dao.DoctorDao;
import edu.njust.dao.PatientDao;
import edu.njust.dao.UserDao;
import edu.njust.entity.Doctor;

public class DoctorService {
	public ArrayList findAllDoctor()
	{
		DoctorDao pd=new DoctorDao();
		ArrayList al=pd.findAllDoctor();
		System.out.println("DoctorService is Ok");
		return al;
	}
	
	public Doctor findByUname(String username)
	{
		DoctorDao pd=new DoctorDao();
		return pd.findDoctorByUname(username);
	}
	
	public int setLocked(int islocked,String username)
	{
		DoctorDao pd=new DoctorDao();
		int rs=pd.updateLocked(islocked,username);
		return rs;
	}
}
