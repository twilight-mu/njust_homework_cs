package edu.njust.service;

import java.util.ArrayList;

import edu.njust.dao.DoctorDao;
import edu.njust.entity.Doctor;

public class DoctorService {
	public ArrayList findAll()
	{
		DoctorDao dd=new DoctorDao();
		return dd.findAllDoctor();
	}
	public Doctor findByUname(String username)
	{
		DoctorDao dd=new DoctorDao();
		return dd.findDoctorByUname(username);
	}
}
