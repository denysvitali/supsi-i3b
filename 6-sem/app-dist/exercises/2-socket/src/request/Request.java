package request;

import http.Method;

import java.net.URI;

public class Request {

	protected Method method;
	protected URI uri;
	protected Request(){

	}

	public Method getMethod() {
		return method;
	}

	public URI getUri() {
		return uri;
	}
}
