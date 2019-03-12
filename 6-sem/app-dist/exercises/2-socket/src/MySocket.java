import java.io.*;
import java.net.Socket;

public class MySocket {
	public static void main(String[] args) throws IOException {
		MyHTTPServer server = new MyHTTPServer();
		server.start();
	}

	public static void client() throws IOException {
		Socket s = new Socket("supsi.ch", 80);
		BufferedReader br = new BufferedReader(
				new InputStreamReader(s.getInputStream())
		);

		String line;

		PrintWriter pw = new PrintWriter(new OutputStreamWriter(s.getOutputStream()));
		pw.print("GET / HTTP/1.1\r\nHost: www.supsi.ch\r\n\r\n");
		pw.flush();

		while((line = br.readLine()) != null){
			System.out.println(line);
		}
		s.close();
	}
}
