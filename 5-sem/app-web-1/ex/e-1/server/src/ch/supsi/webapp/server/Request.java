package ch.supsi.webapp.server;

public class Request
{
	String allRequest;
	String body;
	String resource;
	boolean isPost;
	
	public Request(String allRequest, String resource, String body, boolean isPost){
		this.allRequest = allRequest;
		this.resource = resource;
		this.body = body;
		this.isPost = isPost;
	}
}