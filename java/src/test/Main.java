package test;

import test.our.objects.StdInputReader;

public class Main {

    public static void main(String[] args) {

        StdInputReader r = new StdInputReader();

        int index = r.readInt();

        Fibonacci fibonacci = new Fibonacci();

        int result = fibonacci.run(index);

        System.out.print(result);
    }
}
