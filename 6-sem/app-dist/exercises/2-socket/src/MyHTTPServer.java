import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class MyHTTPServer {
	private int port = 8080;
	private ServerSocket s;

	/*
		Running 20s test @ http://127.0.0.1:8080/
		2 threads and 40 connections
		Thread Stats   Avg      Stdev     Max   +/- Stdev
		Latency     8.77ms   14.75ms 135.22ms   91.77%
		Req/Sec     3.89k     1.49k    5.64k    83.25%
		154786 requests in 20.01s, 22.88MB read
		Socket errors: connect 0, read 154785, write 0, timeout 0
		Requests/sec:   7736.10
		Transfer/sec:      1.14MB

	 */

	public MyHTTPServer(){

	}

	public MyHTTPServer(int port){
		this.port = port;
	}

	public void start() throws IOException {
		s = new ServerSocket(port);

		while(true){
			Socket socket = s.accept();
			Thread t = new Thread(new SocketAcceptor(socket));
			t.start();
		}
	}
}
