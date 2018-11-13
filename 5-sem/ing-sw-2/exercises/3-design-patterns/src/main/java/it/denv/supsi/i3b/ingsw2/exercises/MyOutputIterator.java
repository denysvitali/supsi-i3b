package it.denv.supsi.i3b.ingsw2.exercises;

import java.io.IOException;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.HashMap;

public class MyOutputIterator {
	private MyIterator<String> iterator;
	private MyList<String> list;
	private ListFromFile lff;
	private ArrayList<OutputStream> os = new ArrayList<>();
	private HashMap<Character, Integer> statHM = new HashMap<>();
	private MyOutputDecorator decorator = null;
	private boolean alreadyIterated = false;

	public MyOutputIterator(String inputFilename, MyIteratorDirection dir) throws IOException {
		lff = new ListFromFile(inputFilename);
		list = lff.getList();

		switch(dir){
			case BACKWARD:
				iterator = list.getBackwardIterator();
				break;
			case FORWARD:
				iterator = list.getForwardIterator();
				break;
			default:
				iterator = list.getForwardIterator();
		}
	}

	public void setOutputStream(OutputStream os){
		this.os.clear();
		this.os.add(os);
	}

	public void addOutputStream(OutputStream os){
		this.os.add(os);
	}

	public void addStatCounter(char c){
		if(!statHM.containsKey(c)){
			statHM.put(c, 0);
		}
	}

	public void setDecorator(MyOutputDecorator decorator){
		this.decorator = decorator;
	}

	public void iterate() throws IOException {
		while(iterator.hasMoreElements()){
			String output = iterator.nextElement();
			if(decorator != null){
				output = decorator.decorate(output);
			}
			if(statHM.keySet().size() > 0){
				for(byte c : output.getBytes()){
					if(statHM.containsKey((char) c)){
						statHM.put((char) c, statHM.get((char) c) + 1);
					}
				}
			}
			for(OutputStream o : os){
				o.write(output.getBytes());
				o.write('\n');
			}
		}
		alreadyIterated = true;
	}

	public HashMap<Character, Integer> getStatHM() throws IOException {
		if(alreadyIterated){
			iterate();
		}
		return (HashMap<Character, Integer>) statHM.clone();
	}
}
