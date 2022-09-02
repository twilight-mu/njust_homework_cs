package edu.njust.service;

import java.util.ArrayList;

import edu.njust.dao.DoctorDao;
import edu.njust.dao.PatientDao;
import edu.njust.entity.Doctor;
import edu.njust.entity.Patient;

public class PatientService {
	public ArrayList findAllPatient()
	{
		PatientDao pd=new PatientDao();
		ArrayList al=pd.findAllPatient();
		return al;
	}
	
	public Patient findByUname(String username)
	{
		PatientDao pd=new PatientDao();
		return pd.findPatientByUname(username);
	}
	
	public int setLocked(int islocked,String username)
	{
		PatientDao pd=new PatientDao();
		int rs=pd.updateLocked(islocked,username);
		return rs;
	}
}
