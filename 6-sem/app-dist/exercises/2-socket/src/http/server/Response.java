package http.server;

import java.io.UnsupportedEncodingException;
import java.nio.charset.StandardCharsets;

public class Response {

	private String contentType = "text/plain";
	private StatusCode statusCode = StatusCode.OK;
	private String body;

	public Response(String s) {
		this.body = s;
	}

	public Response(String s, String contentType){
		this.body = s;
		this.contentType = contentType;
	}

	public String getResponse(){
		StringBuilder sb = new StringBuilder();
		sb.append("HTTP/1.1 ");
		sb.append(statusCode.getCode());
		sb.append(" ");
		sb.append(statusCode.getName());
		sb.append("\r\n");
		sb.append("Server: ");
		sb.append(Server.IDENTIFIER);
		sb.append("\r\n");

		if(body != null){
			sb.append("Content-Length: ");
			sb.append(body.getBytes(StandardCharsets.UTF_8).length);
			sb.append("\r\n");
			sb.append("\r\n");
			sb.append(body);
		}

		sb.append("\r\n");
		sb.append("\r\n");

		return sb.toString();
	}
}
