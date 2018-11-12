package it.denv.supsi.i3b.ingsw2.exercises;

import org.junit.jupiter.api.Test;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.net.URL;

import static org.junit.jupiter.api.Assertions.*;

class ListFromFileTest {
	@Test
	public void testFile() throws IOException {
		ListFromFile lff = new ListFromFile("test.txt");
		MyList<String> mL = lff.getList();
		assertEquals("lorem", mL.getElement(0));
		assertEquals("ipsum", mL.getElement(1));
		assertEquals("dolor", mL.getElement(2));
		assertEquals("sit", mL.getElement(3));
		assertEquals("amet", mL.getElement(4));
		assertEquals(5, mL.length());
	}
}