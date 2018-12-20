package it.denv.supsi.i3b.ingsw2.exercises.s4;

import com.google.inject.AbstractModule;
import com.google.inject.Provides;

public class CarTestModule extends AbstractModule {
	protected void configure() {
		bind(IEngine.class).to(FakeEngine.class);
		bind(IBody.class).to(FakeBody.class);
		bind(IFrame.class).to(Frame.class);
		bind(IInterior.class).to(Interior.class);
		bind(IWheel.class).to(Wheel.class);
	}

	@Provides
	Wheel[] wheelProvider() {
		return new Wheel[]{
				new Wheel(),
				new Wheel(),
				new Wheel(),
				new Wheel()
		};
	}
}
