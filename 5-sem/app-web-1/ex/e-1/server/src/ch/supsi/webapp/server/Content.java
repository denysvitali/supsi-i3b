package ch.supsi.webapp.server;

public class Content
{
	int length = 0;
	byte[] content;
	int code = 200;
	
	public Content(byte[] content){
		this.content = content;
		this.length = content.length;
	}

	public Content(byte[] content, int code){
		this.content = content;
		this.length = content.length;
		this.code = code;
	}
}