package test;

/**
 * Created by daniel on 4.2.17.
 */
public class Fibonacci {


    public int run(int n){
        if(n == 0) {
            return 0;
        }

        if(n == 1) {
            return 1;
        }
        
        return run(n - 1) + run(n - 2);
    }
}
