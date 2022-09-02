package edu.njust.service;

import java.util.Vector;

import edu.njust.dao.*;
import edu.njust.entity.*;

public class ReviewService {
	
	
	public Vector<Review> findByReviewpage(int n,int m)
	{
		ReviewDao  rdao = new ReviewDao();
		Vector<Review> vecCur = rdao.findByReviewpage(n,m);
		return vecCur;
	}
	public int getCountofReviews()
	{
		ReviewDao  rdao = new ReviewDao();
		int sum;
		sum=rdao.getCountofReviews();
		return sum;
	}
}
