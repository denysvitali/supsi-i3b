package es2;

public interface IVisitor {
	void visit(Department d);
	void visit(Section s);
	void visit(Division d);
	void visit(Person p);
}
