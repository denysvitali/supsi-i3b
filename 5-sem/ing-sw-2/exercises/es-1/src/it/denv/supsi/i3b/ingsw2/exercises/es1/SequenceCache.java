package it.denv.supsi.i3b.ingsw2.exercises.es1;

import java.util.HashMap;
import java.util.Map;

public class SequenceCache {
	private Map<Integer, Worker> sequences;

	public SequenceCache(){
		this.sequences = new HashMap<>();
	}

	public int length(int value){
		if(sequences.containsKey(value)){
			return sequences.get(value).sequence();
		}

		Worker w = new Worker(value);
		sequences.put(value, w);
		return w.sequence();
	}

}
