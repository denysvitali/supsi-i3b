package it.denv.supsi.i3b.ingsw2.exercises.s4;

import com.google.inject.Inject;

public class Car {
	private IEngine engine;
	private IBody body;
	private Frame frame;
	private Interior interior;
	private Wheel[] wheels;

	@Inject
	public Car(IEngine engine,
			   IBody body,
			   Frame frame,
			   Interior interior,
			   Wheel[] wheels) {
		this.engine = engine;
		this.body = body;
		this.frame = frame;
		this.interior = interior;
		this.wheels = wheels;
	}

	public double getWeight(){
		double sum = 0.0;
		sum += this.engine.getWeight();
		sum += this.body.getWeight();
		sum += this.frame.getWeight();
		sum += this.interior.getWeight();
		for(Wheel w : wheels){
			sum += w.getWeight();
		}

		return sum;
	}
}
