package test;

/**
 * Created by daniel on 4.2.17.
 */
public class Fibonacci {


    public int run(int n, int pom1, int pom2){
        if(n == 0) {
            return pom1;
        }

        if(n == 1) {
            return pom2;
        }
        
        return run(n - 1, pom1, pom2) + run(n - 2, pom1, pom2);
    }
}
