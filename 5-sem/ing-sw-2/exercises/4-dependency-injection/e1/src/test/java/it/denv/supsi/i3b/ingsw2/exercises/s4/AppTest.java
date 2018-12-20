package it.denv.supsi.i3b.ingsw2.exercises.s4;

import com.google.inject.Guice;
import com.google.inject.Injector;
import junit.framework.Test;
import junit.framework.TestCase;
import junit.framework.TestSuite;

/**
 * Unit test for simple App.
 */
public class AppTest
		extends TestCase {
	/**
	 * Create the test case
	 *
	 * @param testName name of the test case
	 */
	public AppTest(String testName) {
		super(testName);
	}

	/**
	 * @return the suite of tests being tested
	 */
	public static Test suite() {
		return new TestSuite(AppTest.class);
	}

	public void testApp() {
		Injector injector = Guice.createInjector(new CarTestModule());
		Car myCar = injector.getInstance(Car.class);

		assertNotNull(myCar);
		assertEquals(8.0, myCar.getWeight());
	}
}
