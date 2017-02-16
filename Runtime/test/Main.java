package test;

import test.our.objects.StdInputReader;

public class Main {

    public static void main(String[] args) {

        StdInputReader r = new StdInputReader();

        int index = r.readInt();

        int pom1 = r.readInt();

        int pom2 = r.readInt();

        Fibonacci fibonacci = new Fibonacci();

        int result = fibonacci.run(index, pom1, pom2);

        System.out.print(result);
    }
}
