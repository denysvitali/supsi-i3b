package es1;

public class Section extends Component {
	private String name;

	public Section(String name){
		this.name = name;
	}

	@Override
	public void print() {
		System.out.println(
				String.format("\t\tes1.Section %s:", name)
		);
		getChildren().forEach(IComposite::print);
	}
}
