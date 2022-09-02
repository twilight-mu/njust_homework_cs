package edu.njust.entity;

import java.util.Date;

import edu.njust.utils.CalendarUtil;

public class Review 
{
	private int reviewId;
	private String organization;
	private String paperTitle;
	private int fee;
	private boolean isPayed;
	private Date createDate;
	public Review(){
		
	}
	public void setReviewId(int reviewId)
	{
		this.reviewId=reviewId;
	}
	public int getReviewId()
	{
		return reviewId;
	}
	public void setOrganization(String organzation)
	{
		this.organization=organzation;
	}
	public String getOrganization()
	{
		return organization;
	}
	public void setPaperTitle(String paperTitle)
	{
		this.paperTitle=paperTitle;
	}
	public String getPaperTitle()
	{
		return paperTitle;
	}
	public void setFee(int fee)
	{
		this.fee=fee;
	}
	public int getFee()
	{
		return fee;
	}
	public void setIsPayed(boolean isPayed)
	{
		this.isPayed=isPayed;
	}
	public boolean getIsPayed()
	{
		return isPayed;
	}
	public Date getCreateDate(){
		return this.createDate;
	}
	public String getFormattedDate(){
		String dateStr = CalendarUtil.dateFormat(this.createDate);
		//System.out.println(dateStr);
		return dateStr;
	}
	public void setCreateDate(Date date){
		this.createDate = date;
	}
}
