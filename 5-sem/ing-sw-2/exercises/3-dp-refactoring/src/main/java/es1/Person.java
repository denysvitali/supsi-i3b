package es1;

public class Person implements IComposite {
	private String name;
	private String surname;

	public Person(String name, String surname){
		this.name = name;
		this.surname = surname;
	}

	@Override
	public void print() {
		System.out.println(String.format(
				"\t\t\tes1.Person: %s %s", name, surname
		));
	}
}
