import es2.Department;
import es2.Division;
import es2.Person;
import es2.Section;
import es2.Visitor;
import org.junit.jupiter.api.Test;

class VisitorTest {

	@Test
	void visitorTest1(){
		Department dep = new Department("DTI");
		Division div1 = new Division("ISIN");
		Division div2 = new Division("MEMTI");
		Division div3 = new Division("IDSIA");
		Division div4 = new Division("ISTePS");
		Section s1 = new Section("Sec1");
		Section s2 = new Section("Sec2");
		Section s3 = new Section("Sec3");
		Section s4 = new Section("Sec4");
		Person p1 = new Person("Emanuele", "Carpanzano");
		Person p2 = new Person("Marco", "Colla");
		Person p3 = new Person("Luca", "Gambardella");
		Person p4 = new Person("Tiziano", "Leidi");
		Person p5 = new Person("Adriano", "Nasciuti");

		div3.addChild(p3);
		div4.addChild(p2);
		div1.addChild(p4);

		dep.addChild(div1);
		dep.addChild(div2);
		dep.addChild(div3);
		dep.addChild(div4);

		s2.addChild(p5);

		div1.addChild(s1);
		div2.addChild(s2);
		div3.addChild(s3);
		div4.addChild(s4);

		Visitor v = new Visitor();
		v.visit(dep);
	}

}
