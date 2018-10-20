
/**
 * This is a test class for testing the expression class. There is a driver code
 * in it, that takes the expression and does the calculation.
 *
 * @author aliyasineser
 */
public class ExpressionTest {

    /**
     * Main test method.
     *
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        Expression exp = new Expression();

        try {
            //Taking input
            exp.takeTheExp();
            try {
                //Does calculation
                exp.Calculate();

            } catch (DivideByZeroException e) {
                System.out.println("There is a divide by zero error. ");
                System.out.println("Computer can't handle with that. Program exits.");
                System.exit(1);
            }
        } catch (ParanthesisException e) {
            System.out.println("Check your paranthesis and try again.");
            System.out.println("In an expression, you can't write \"()\"");
            System.out.println("In an expression, you can't start with \")\" and end with \"(\"");
        } catch (OperatorException e) {
            System.out.println("Check your operators and try again.");
            System.out.println("An expression cannot start or end with an operator.");
            System.out.println("In an expression, two operators cannot be next each other.");
        } catch (OperandException e) {
            System.out.println("Check your operand and try again.");
            System.out.println("In an expression, two operand cannot be next each other.");
            System.out.println("In an expression, you can't do \" x( \" or \" )x \"");

        }

    }
}
