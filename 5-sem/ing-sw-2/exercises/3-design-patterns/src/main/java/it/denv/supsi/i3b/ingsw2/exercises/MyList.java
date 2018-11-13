package it.denv.supsi.i3b.ingsw2.exercises;

import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;

public class MyList<T> {
	List<T> myList = new ArrayList<>();

	public MyList(){

	}

	public void addElement(T element){
		myList.add(element);
	}
	public int length() {
		return myList.size();
	}

	public T getElement(int index){
		return myList.get(index);
	}

	public MyIterator<T> getForwardIterator(){
		return new MyIterator<>(this);
	}
	public MyIterator<T> getBackwardIterator(){
		return new MyIterator<>(this, MyIteratorDirection.BACKWARD);
	};
}
