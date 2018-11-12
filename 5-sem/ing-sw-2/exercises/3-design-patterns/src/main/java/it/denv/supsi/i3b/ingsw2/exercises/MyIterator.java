package it.denv.supsi.i3b.ingsw2.exercises;

public class MyIterator<T> {
	private int currentEl = 0;
	private MyList<T> l;
	private MyIteratorDirection direction = MyIteratorDirection.FORWARD;

	public MyIterator(MyList<T> l){
		this.l = l;
	}
	public MyIterator(MyList<T> l, MyIteratorDirection dir){
		this.l = l;
		this.direction = dir;

		if(dir == MyIteratorDirection.BACKWARD){
			currentEl = l.length() - 1;
		}
	}

	public void setDirection(MyIteratorDirection direction) {
		this.direction = direction;
	}

	public T nextElement(){
		if(hasMoreElements()){
			T el = l.getElement(currentEl);
			switch(direction){
				case FORWARD:
					currentEl++;
					break;
				case BACKWARD:
					currentEl--;
					break;
			}
			return el;
		}
		return null;
	}

	public boolean hasMoreElements(){
		switch(direction){
			case FORWARD:
				return l.length() != currentEl;
			case BACKWARD:
				return currentEl >= 0;
		}
		return false;
	}

	public void rewind(){
		switch (direction){
			case FORWARD:
				currentEl = 0;
				break;
			case BACKWARD:
				if(l.length() == 0){
					currentEl = 0;
				} else {
					currentEl = l.length() - 1;
				}
				break;
		}
	}
}
