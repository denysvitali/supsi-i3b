package it.denv.supsi.i3b.ingsw2.exercises.es1;

import org.aopalliance.intercept.MethodInterceptor;
import org.aopalliance.intercept.MethodInvocation;

import java.util.Arrays;

public class TracingInterceptor implements MethodInterceptor {
	public Object invoke(MethodInvocation methodInvocation) throws Throwable {
		double start = System.nanoTime();
		Object output = methodInvocation.proceed();
		double end = System.nanoTime();

		System.out.println(String.format("%s(%s) executed in %f ns",
				methodInvocation.getMethod().getName(),
				Arrays.stream(methodInvocation.getArguments()[0].getClass().getName().split("\\."))
				.reduce((a,b)->b).orElse(""),
				end-start));

		return output;
	}
}
