package it.denv.supsi.i3b.ingsw2.exercises;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class MyListTest {
	@Test
	public void TestList(){
		MyList<Integer> list = new MyList<>();
		assertEquals(0, list.length());
		list.addElement(10);
		assertEquals(1, list.length());
		assertEquals(Integer.valueOf(10), list.getElement(0));
	}

	private MyList<Integer> createTestList() {
		MyList<Integer> list = new MyList<>();
		list.addElement(10);
		list.addElement(20);
		list.addElement(30);

		return list;
	}

	@Test
	public void TestListCreation(){
		MyList<Integer> l = createTestList();
		assertEquals(Integer.valueOf(10), l.getElement(0));
		assertEquals(Integer.valueOf(20), l.getElement(1));
		assertEquals(Integer.valueOf(30), l.getElement(2));
	}

	@Test
	public void TestForwardIterator(){
		MyList<Integer> list = createTestList();

		Integer[] expectedResults = {10, 20, 30};
		int index = 0;

		MyIterator<Integer> fwdIterator = list.getForwardIterator();
		while(fwdIterator.hasMoreElements()){
			assertEquals(expectedResults[index], fwdIterator.nextElement());
			index++;
		}
		fwdIterator.rewind();
		index = 0;
		while(fwdIterator.hasMoreElements()){
			assertEquals(expectedResults[index], fwdIterator.nextElement());
			index++;
		}
	}

	@Test
	public void TestBackwardIterator(){
		MyList<Integer> list = createTestList();

		Integer[] expectedResults = {10, 20, 30};
		int index = expectedResults.length - 1;

		MyIterator<Integer> bwdIterator = list.getBackwardIterator();
		while(bwdIterator.hasMoreElements()){
			assertEquals(expectedResults[index], bwdIterator.nextElement());
			index--;
		}
		bwdIterator.rewind();
		index = expectedResults.length - 1;
		while(bwdIterator.hasMoreElements()){
			assertEquals(expectedResults[index], bwdIterator.nextElement());
			index--;
		}
	}

}