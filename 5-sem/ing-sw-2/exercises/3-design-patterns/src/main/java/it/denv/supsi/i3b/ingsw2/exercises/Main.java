package it.denv.supsi.i3b.ingsw2.exercises;

import java.io.FileOutputStream;
import java.io.IOException;

public class Main {

    public static void main(String[] args) throws IOException {
        ListFromFile lff = new ListFromFile("test.txt");
        MyList<String> list = lff.getList();

        MyOutputIterator myOutputIterator =
                new MyOutputIterator("test.txt",
                        MyIteratorDirection.BACKWARD);
        myOutputIterator.setDecorator(String::toUpperCase);

        FileOutputStream fos = new FileOutputStream("/tmp/test2.txt");
        myOutputIterator.addOutputStream(fos);
        myOutputIterator.addOutputStream(System.out);
        myOutputIterator.addStatCounter('A');
        myOutputIterator.addStatCounter('B');
        myOutputIterator.iterate();

        System.out.println("As: " + myOutputIterator.getStatHM().get('A'));

    }
}
