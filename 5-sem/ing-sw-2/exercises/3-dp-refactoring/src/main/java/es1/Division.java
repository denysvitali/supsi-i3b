package es1;

public class Division extends Component {
	private String name;

	public Division(String name){
		this.name = name;
	}

	@Override
	public void print() {
		System.out.println(
				String.format("\tes1.Division %s:", name)
		);
		getChildren().forEach(IComposite::print);
	}
}
