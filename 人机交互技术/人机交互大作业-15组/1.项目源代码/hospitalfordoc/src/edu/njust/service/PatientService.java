package edu.njust.service;

import java.util.ArrayList;

import edu.njust.dao.*;
import edu.njust.entity.*;

public class PatientService {
	public ArrayList findAll()
	{
		PatientDao pd=new PatientDao();
		return pd.findAllPatient();
	}
	public Patient findByUname(String username)
	{
		PatientDao pd=new PatientDao();
		return pd.findPatientByUname(username);
	}
}
