import http.Method;
import http.server.InvalidRequestException;
import http.server.Response;
import request.Request;
import request.RequestBuilder;

import java.io.*;
import java.net.Socket;
import java.net.URISyntaxException;

public class SocketAcceptor implements Runnable {
	private Socket s;
	public SocketAcceptor(Socket s) {
		this.s = s;
	}

	@Override
	public void run() {
		try {
			BufferedReader br = new BufferedReader(new InputStreamReader(
					s.getInputStream()));

			RequestBuilder r = new RequestBuilder();


			br.mark(5);
			for(Method m : Method.values()){
				br.reset();
				byte[] v = m.toString().getBytes("ASCII");

				for(int i=0; i<v.length; i++){
					if(v[i] != br.read()){
						continue;
					}
				}

				r.setMethod(m);
				break;
			}

			if(br.read() != ' '){
				throw new InvalidRequestException();
			}

			StringBuilder requestUriSB = new StringBuilder();
			int c;
			while((c = br.read()) != ' '){
				if(c == '\n' || c == '\r'){
					throw new InvalidRequestException();
				}
				requestUriSB.append((char) c);
			}

			r.setUri(requestUriSB.toString());

			handleRequest(r.build());
		} catch (IOException | InvalidRequestException | URISyntaxException e) {
			e.printStackTrace();
		}
	}

	private void handleRequest(Request r) {
		switch(r.getMethod()){
			case GET:
				doGet(r);
				return;
			case PUT:
				doPut(r);
				return;
			case HEAD:
				doHead(r);
				return;
			case POST:
				doPost(r);
				return;
		}
	}

	private void doPut(Request r) {
	}

	private void doHead(Request r) {
	}

	private void doPost(Request r) {
	}

	private void doGet(Request r){
		switch(r.getUri().getPath()){
			case "/":
				Response resp = new Response("<!DOCTYPE html><html>" +
						"<head>" +
						"<title>My WS</title>" +
						"</head>" +
						"<body>" +
						"<h1>:)</h1>" +
						"</body>" +
						"</html>", "text/html");
				sendResponse(resp);
				break;
		}
	}

	private void sendResponse(Response r){
		try {
			BufferedOutputStream bos = new BufferedOutputStream(
					s.getOutputStream());
			bos.write(r.getResponse().getBytes());
			bos.flush();
			bos.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
