package it.denv.supsi.i3b.ingsw2.exercises.encapsulation;

import org.junit.Test;

import java.util.Calendar;
import java.util.GregorianCalendar;

import static org.junit.Assert.*;

public class DayTest {
	@Test
	public void dayIn10(){
		Day d = new Day(2018, 10, 9);
		Day d2 = d.dayAfter(10);

		assertEquals(19, d2.getDayOfMonth());
		assertEquals(10, d2.getMonth());
		assertEquals(2018, d2.getYear());
	}

	@Test
	public void dayIn50(){
		Day d = new Day(2018, 10, 9);
		Day d2 = d.dayAfter(50);

		assertEquals(29, d2.getDayOfMonth());
		assertEquals(11, d2.getMonth());
		assertEquals(2018, d2.getYear());
	}

	@Test
	public void daysTo(){
		Calendar c = new Calendar.Builder().build();
		Day d = new Day(c.get(Calendar.YEAR),
				c.get(Calendar.MONTH),
				c.get(Calendar.DAY_OF_MONTH));

		int daysTo = 10;
		Day d2 = d.dayAfter(daysTo);

		assertEquals(daysTo, d.daysTo(d2));
	}

	@Test
	public void daysTillEndOfYear(){
		Calendar c = new GregorianCalendar();
		Calendar c2 = new Calendar.Builder().setDate(
				c.get(Calendar.YEAR),
				11,
				31
		).build();

		int daysEoy = (int) Math.round(
				(c2.getTimeInMillis() - c.getTimeInMillis()) /
						(1000.0 * 60 * 60 * 24)
		);

		System.out.println("Days till the end of year: " + daysEoy);
		assertEquals(daysEoy, Day.daysTillEndOfYear());
	}
}