package ch.supsi.webapp.server;

public class Content
{
	int length = 0;
	byte[] content;
	
	public Content(byte[] content){
		this.content = content;
		this.length = content.length;
	}
}