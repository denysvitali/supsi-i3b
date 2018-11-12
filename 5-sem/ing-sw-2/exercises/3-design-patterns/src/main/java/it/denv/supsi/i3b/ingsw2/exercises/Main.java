package it.denv.supsi.i3b.ingsw2.exercises;

import java.io.IOException;

public class Main {

    public static void main(String[] args) throws IOException {
        ListFromFile lff = new ListFromFile("test.txt");
        MyList<String> list = lff.getList();

        MyIterator<String> myIterator = list.getBackwardIterator();
        while(myIterator.hasMoreElements()){
            System.out.println(myIterator.nextElement());
        }

    }
}
