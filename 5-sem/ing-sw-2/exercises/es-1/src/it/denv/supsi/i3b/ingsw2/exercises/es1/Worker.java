package it.denv.supsi.i3b.ingsw2.exercises.es1;

public class Worker {

	private int startingValue;

	public Worker(int startingValue){
		this.startingValue = startingValue;
	}

	public static int conversion(int number){
		if (number % 2 == 0) {
			return number/2;
		}
		return number * 3 + 1;
	}

	public int sequence() {
		if(startingValue <= 2){
			throw new RuntimeException("Invalid Value");
		}

		int value = startingValue;
		int calls = 0;
		while(value != 1){
			value = conversion(value);
			calls++;
		}

		return calls;
	}
}
