package it.denv.supsi.i3b.ingsw2.exercises.es1;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

public class WorkerTest {

	@Test
	public void conversion() {
		assertEquals(1, Worker.conversion(2));
		assertEquals(3, Worker.conversion(1));
	}

	@Test
	public void sequence(){
		assertThrows(RuntimeException.class,
				()->new Worker(1).sequence()
		);
		assertEquals(6, new Worker(10).sequence());
	}
}
