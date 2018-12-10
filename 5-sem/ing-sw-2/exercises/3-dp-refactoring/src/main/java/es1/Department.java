package es1;

public class Department extends Component {

	private String name;

	public Department(String name){
		this.name = name;
	}

	@Override
	public void print() {
		System.out.println(
				String.format("es1.Department %s:", name)
		);
		getChildren().forEach(IComposite::print);
	}
}
