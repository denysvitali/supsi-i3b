package it.denv.supsi.i3b.ingsw2.exercises.es1;

public class Division extends Component implements IAcceptor {
	private String name;

	public Division(String name){
		this.name = name;
	}

	public String getName() {
		return name;
	}

	@Override
	public void accept(IVisitor visitor) {
		visitor.visit(this);
	}
}
