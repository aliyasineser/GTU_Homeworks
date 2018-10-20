
/**
 * This is a test file for testing Polynomial class. Test creates a few objects
 * and uses theese objects for testing member methods of Polynomial class. Test
 * file created and implemented by Ali Yasin Eser, for:
 * HW9_141044058_AliYasin_Eser
 *
 * @author aliyasineser
 */
public class PolynomialTest {

    /**
     * Main file for testing the Polynomial class.
     * @param args 
     */
    public static void main(String args[]) {
        // Creating a double array for using on constructor
        double[] arr = new double[5];
        // Filling the double array, taking index's double adding 2
        for (int i = 0; i < arr.length; ++i) {
            arr[i] = (double) 3 * i + 5;
        }
        double[] arr2 = new double[5];

        for (int i = 0; i < arr2.length; ++i) {
            arr2[i] = arr[i] * 3;
        }

        double[] arr3 = new double[5];

        for (int i = 0; i < arr3.length; ++i) {
            arr3[i] = arr[i] * 7;
        }

        // test 1 and 2, Polynomials
        Polynomial test = new Polynomial(arr);
        Polynomial test2 = new Polynomial(arr2);
        Polynomial test3 = new Polynomial(arr3);

        // Printing the test polynomials
        System.out.printf("Test Polynomial: %s\n", test.toString());
        System.out.printf("Test2 Polynomial: %s\n", test2.toString());
        System.out.printf("Test3 Polynomial: %s\n", test3.toString());

        // Both objects created with using same array, they must be equal
        if (test.equals(test2)) {
            System.out.println("Test = Test2");
        } else {
            System.out.println("Test != Test2");

        }

        // Printing the calculations
        System.out.printf("Test * Test2: %s\n", test.multiplyArr(test2));
        System.out.printf("Test + Test2: %s\n", test.sumArr(test2));
        System.out.printf("Test3 - Test2: %s\n", test3.subArr(test2));

        // Printing that what if we consider x as 3, what will be the result of test2 
        System.out.printf("Test2(3) : %s\n", test2.result(3));

    }
}
