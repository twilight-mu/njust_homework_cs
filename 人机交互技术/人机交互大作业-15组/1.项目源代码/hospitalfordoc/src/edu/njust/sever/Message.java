package edu.njust.sever;

public class Message {
	
	private String from;
	private String to;
	private String msg;
	
	public String getFrom() {
		return from;
	}
	public void setFrom(String from) {
		this.from = from;
	}
	public String getTo() {
		return to;
	}
	public void setTo(String to) {
		this.to = to;
	}
	public String getMsg() {
		return msg;
	}
	public void setMsg(String msg) {
		this.msg = msg;
	}
	
	public Message(){}
	
	public Message(String from,String to,String msg){
		this.from=from;
		this.to=to;
		this.msg=msg;
	}
}
