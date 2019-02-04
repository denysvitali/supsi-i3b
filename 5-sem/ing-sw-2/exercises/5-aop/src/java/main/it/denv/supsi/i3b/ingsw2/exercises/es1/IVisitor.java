package it.denv.supsi.i3b.ingsw2.exercises.es1;

public interface IVisitor {
	void visit(Department d);
	void visit(Section s);
	void visit(Division d);
	void visit(Person p);
}
