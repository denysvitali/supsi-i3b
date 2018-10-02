package it.denv.supsi.i3b.ingsw2.exercises.es2;

public class Fraction {

	private int numerator, denominator;

	public Fraction(int num, int den){

		if(den == 0){
			throw new RuntimeException("Division by zero!");
		}

		this.numerator = num;
		this.denominator = den;
	}

	public int num(){
		return this.numerator;
	}

	public int den(){
		return this.denominator;
	}

	public void simplify(){
		int gcd_r = gcd(numerator, denominator);
		int new_n = numerator / gcd_r;

		this.numerator = new_n;
		this.denominator = denominator / gcd_r;
	}

	static int gcd(int a, int b){
		if(b == 0){
			return a;
		}

		return gcd(b, a%b);
	}

	@Override
	public boolean equals(Object o) {
		if(o.getClass() != this.getClass()){
			return false;
		}

		Fraction other = (Fraction) o;

		if(this.numerator != other.numerator){
			return false;
		}

		return this.denominator == other.denominator;
	}
}