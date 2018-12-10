package es2;

public class Visitor implements IVisitor {
	public void visit(Person p) {
		System.out.println(String.format("\t\t\tPerson: %s %s",
				p.getName(),
				p.getSurname()));
		p.getChildren().forEach(e->e.accept(this));
	}

	public void visit(Department d) {
		System.out.println(String.format("Department: %s",
				d.getName()));
		d.getChildren().forEach(e->e.accept(this));
	}

	public void visit(Section s) {
		System.out.println(String.format("\t\tSection: %s",
				s.getName()));
		s.getChildren().forEach(e->e.accept(this));
	}

	public void visit(Division d) {
		System.out.println(String.format("\tDivision: %s",
				d.getName()));
		d.getChildren().forEach(e->e.accept(this));
	}
}
