package it.denv.supsi.i3b.ingsw2.exercises.encapsulation;

import java.util.Calendar;
import java.util.GregorianCalendar;

public class Day {

	private Calendar c;

	public Day(int year, int month, int day){
		Calendar.Builder cb = new Calendar.Builder();
		cb.setFields(Calendar.YEAR, year);
		cb.setFields(Calendar.MONTH, month);
		cb.setFields(Calendar.DAY_OF_MONTH, day);
		c = cb.build();
	}

	private Day(Calendar c){
		this.c = c;
	}

	public int daysTillEndOfYear(){
		Day now = this;
		Day endOfYear = new Day(now.getYear(), 11, 31);
		return now.daysTo(endOfYear);
	}

	public int getYear(){
		return c.get(Calendar.YEAR);
	}

	public int getMonth(){
		return c.get(Calendar.MONTH);
	}

	public int getDayOfMonth() {
		return c.get(Calendar.DAY_OF_MONTH);
	}

	private long getMillis(){
		return c.getTimeInMillis();
	}

	public int daysTo(Day d){
		long millis = d.getMillis() - this.getMillis();
		return (int) Math.round(millis / (1000.0 * 60.0 * 60 * 24));
	}

	public Day dayAfter(int days){
		Calendar c2 = (Calendar) c.clone();
		c2.add(Calendar.DAY_OF_MONTH, days);

		return new Day(c2);
	}
}
