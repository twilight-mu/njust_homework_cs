package edu.njust.dao;

import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Vector;

import edu.njust.entity.*;
import edu.njust.utils.*;

import java.sql.*;

import javax.sql.*;

import edu.njust.utils.DBUtil;

public class ReviewDao {
	
	public ReviewDao(){
		
	}	
	
	public ReviewDao(Review review) {
		// TODO Auto-generated constructor stub
	}	

	
	public Vector<Review> findByReviewpage(int n,int m)
	{
		Vector<Review> vecCur = new Vector<Review>();
		Map<String, Object> map = null;
		Review review = null;
		try 
			{
				   String limit=n+","+m;
				   List<Map<String, Object>> list = DBUtil.query("review_log",false,null,null,null,null,null,null,limit);
				   int size = list.size();
				   for(int i=0;i<size;i++)
				   {
					   map = list.get(i);
					   review=new Review();
					   review.setReviewId((int)map.get("reviewId"));
					   review.setOrganization((String)map.get("organization"));
					   review.setPaperTitle((String)map.get("paperTitle"));
					   review.setFee((int)map.get("fee"));
					   review.setCreateDate((Date)map.get("date"));
					   review.setIsPayed((boolean)map.get("isPayed"));
					   vecCur.add(review);
				   	}
		        } catch (SQLException e) {
		            e.printStackTrace();
		        } catch (Exception e){
		            e.printStackTrace();
		        }
			   
		return vecCur;
	}
	
	
	public int getCountofReviews() 
	{
		try 
		{
		   List<Map<String, Object>> list = DBUtil.query("review_log",null);
		   return list.size();
	    } 
		catch (SQLException e) 
	    {
	       e.printStackTrace();
	    } 
		catch (Exception e)
	    {
	       e.printStackTrace();
	    }
		return 0;
	}


	

}
