package request;

import http.Method;

import java.net.URI;
import java.net.URISyntaxException;

public class RequestBuilder {

	private Request r = new Request();
	public RequestBuilder(){

	}

	public void setMethod(Method method) {
		r.method = method;
	}

	public Request build(){
		return r;
	}

	public void setUri(String uri) throws URISyntaxException {
		r.uri = new URI(uri);
	}
}
