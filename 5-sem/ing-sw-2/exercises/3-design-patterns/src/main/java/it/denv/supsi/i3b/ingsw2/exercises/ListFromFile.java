package it.denv.supsi.i3b.ingsw2.exercises;

import java.io.*;

public class ListFromFile {
	private MyList<String> myList = new MyList<>();
	public ListFromFile(String path) throws IOException {
		FileReader fr = new FileReader(
				getClass().getResource("/" + path).getPath());
		BufferedReader br = new BufferedReader(fr);
		String line;
		while((line = br.readLine()) != null){
			myList.addElement(line);
		}
	}

	public MyList<String> getList() {
		return myList;
	}
}
