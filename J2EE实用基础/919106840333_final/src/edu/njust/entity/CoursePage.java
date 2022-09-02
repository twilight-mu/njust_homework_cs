package edu.njust.entity;

public class CoursePage 
{
	private int nowpage;//当前页面数
	private int minpage;//最小页面数
	private int maxpage;//最大页面数
	public int getNowpage()
	{
		return nowpage;
	}
	public void setNowpage(int nowpage)
	{
		this.nowpage=nowpage;
	}
	public int getMinpage()
	{
		return minpage;
	}
	public void setMinpage(int minpage)
	{
		this.minpage=minpage;
	}
	public int getMaxpage()
	{
		return maxpage;
	}
	public void setMaxpage(int maxpage)
	{
		this.maxpage=maxpage;
	}
}
