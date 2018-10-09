package it.denv.supsi.i3b.ingsw2.exercises.es2;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class FractionTest {

	@Test
	void simplification() {
		Fraction f = new Fraction(2,4);
		f.simplify();
		assertEquals(1, f.num());
		assertEquals(2, f.den());

		f = new Fraction(8, 12);
		assertEquals(8, f.num());
		assertEquals(12, f.den());

		f.simplify();
		assertEquals(2, f.num());
		assertEquals(3, f.den());
	}

	@Test
	void equality(){
		Fraction f = new Fraction(3, 9);
		Fraction f2 = new Fraction(4, 8);
		assertNotEquals(f, f2);
		assertNotEquals(f2, f);

		f = new Fraction(1,2);
		f2 = new Fraction(1,2);

		assertEquals(f, f2);
		assertEquals(f2, f);
	}

	@Test
	void gcdTest(){
		assertEquals(1, Fraction.gcd(1, 2));
		assertEquals(4, Fraction.gcd(8, 12));
		assertEquals(4, Fraction.gcd(12, 8));
	}

	@Test
	void divisionByZero(){
		assertThrows(RuntimeException.class, ()->{
			new Fraction(1,0);
		});
	}
}