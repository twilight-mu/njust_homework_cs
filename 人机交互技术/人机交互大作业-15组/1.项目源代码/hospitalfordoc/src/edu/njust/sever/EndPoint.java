package edu.njust.sever;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentMap;

import net.sf.json.*; 

import javax.websocket.*;
import javax.websocket.server.*;


@ServerEndpoint(value = "/chat")
public class EndPoint
{
	//远程endPoint，使用userName作为Key进行绑定
	private static ConcurrentMap<String,EndPoint>clientSet = new ConcurrentHashMap<>(); 
	
	//连接时，获得用户名
	private String user;
	//_websocket会话
	private Session session;


	@OnOpen
	public void start(Session session)
	{
		this.session = session;
		user=this.session.getRequestParameterMap().get("user").get(0);
		
		clientSet.put(user, this);
		
		List<String>list =new ArrayList<>( clientSet.keySet());
	    broadcast(list);
	    
	    Message msg=new Message("server","All",String.format("【%s %s】",user, "加入了聊天室！"));
		sendMessage(msg);
	}
	// 当端断开连接时自动激发该方法
	@OnClose
	public void end()
	{
		clientSet.remove(user);
		Message msg=new Message("server","All",String.format("【%s %s】",user, "离开了聊天室！"));
		sendMessage(msg);
		
		List<String>list =new ArrayList<>( clientSet.keySet());
	    broadcast(list);
		
	}
	// 每当收到客户端消息时自动激发该方法
	@OnMessage
	public void onMessage(String message)
	{
		JSONObject json = JSONObject.fromObject(message);
	    Message msg = (Message)JSONObject.toBean(json,Message.class);

		sendMessage(msg);
	}
	// 当客户端通信出现错误时，激发该方法
	@OnError
	public void onError(Throwable t) throws Throwable
	{
		System.out.println("WebSocket服务端错误 " + t);
	}
	// 发送消息
	private static void sendMessage(Message msg)
	{
		//如果为all，遍历历用户列表，逐个发送，否则只发送给一个
		if(msg.getTo().equals("All")){
			Set<String>clientKey = clientSet.keySet();
		    for(String k: clientKey){
		    	EndPoint client=clientSet.get(k);
		    	try
				{
					synchronized (client)
					{
						// 发送消息
						client.session.getBasicRemote().sendText(JSONObject.fromObject(msg).toString());
					}
				}
				catch (IOException e)
				{
					clientSet.remove(k);
					try
					{
						client.session.close();
					}
					catch (IOException e1){}
					
					Message msgError=new Message("server","All",String.format("【%s %s】",k, "已经被断开了连接。"));
					sendMessage(msgError);
					
					List<String>list =new ArrayList<>( clientSet.keySet());
				    broadcast(list);
				}
		    }
    	}else{
    		EndPoint client=clientSet.get(msg.getTo());
	    	try
			{
				synchronized (client)
				{
					// 发送消息
					client.session.getBasicRemote().sendText(JSONObject.fromObject(msg).toString());
				}
			}
			catch (IOException e)
			{
				clientSet.remove(msg.getTo());
				try
				{
					client.session.close();
				}
				catch (IOException e1){}
				
				Message msgError=new Message("server","All",String.format("【%s %s】",msg.getTo(), "已经被断开了连接。"));
				sendMessage(msgError);
				
				List<String>list =new ArrayList<>( clientSet.keySet());
			    broadcast(list);
			}
	    	
	    	EndPoint clientSend=clientSet.get(msg.getFrom());
	    	try
			{
				synchronized (clientSend)
				{
					// 发送消息
					clientSend.session.getBasicRemote().sendText(JSONObject.fromObject(msg).toString());
				}
			}
			catch (IOException e){}
    	}
	}
	
	// 广播用户列表消息，客户端更新
	private static void broadcast(List<String> list)
	{
	    for(String k: list){
	    	try
			{
				synchronized (k)
				{
					// 发送消息
					clientSet.get(k).session.getBasicRemote().sendText(JSONArray.fromObject(list).toString());
				}
			}
	    	catch (IOException e)
			{
				System.out.println("聊天错误，向客户端 "
					+ k + " 发送消息出现错误。");
				clientSet.remove(k);
				try
				{
					clientSet.get(k).session.close();
				}
				catch (IOException e1){}
				Message msgError=new Message("server","All",String.format("【%s %s】",k, "已经被断开了连接。"));
				sendMessage(msgError);
			}
    	}
	}
}