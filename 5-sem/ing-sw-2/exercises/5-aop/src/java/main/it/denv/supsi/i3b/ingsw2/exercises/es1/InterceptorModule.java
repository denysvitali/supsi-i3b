package it.denv.supsi.i3b.ingsw2.exercises.es1;

import com.google.inject.AbstractModule;
import com.google.inject.matcher.Matchers;

public class InterceptorModule extends AbstractModule {
	@Override
	protected void configure() {
		bindInterceptor(Matchers.only(Visitor.class),
				Matchers.any(),
				new TracingInterceptor()
		);
	}
}
