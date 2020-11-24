import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out);
        
        long one = Integer.MAX_VALUE / Integer.MAX_VALUE;
        long zero = one - one;
        long two = one + one;
        long three = one + two;
        
        long n, k;
        n = in.nextLong();
        k = in.nextLong();
        long m = (n - three*k + one) / two;
        
        m = Math.max(zero, m);
        
        out.println(m);
        
        out.close();
    }
}