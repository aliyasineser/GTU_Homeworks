
/**
 * This is an operator class for keeping expressions operator parts. Keeps a
 * character and have methods for manipulating it.
 *
 * @author aliyasineser
 */
public class Operator {

    // Variable
    private char op_ch;

    /**
     * Constuctor of the class.
     *
     * @param _operator
     */
    public Operator(char _operator) {
        setOperator(_operator);
    }

    /**
     * Setter of the operator. Has check for is that a really operator symbol.
     *
     * @param _operator
     */
    public void setOperator(char _operator) {
        if (_operator == '*' || _operator == '/' || _operator == '+' || _operator == '-') {
            op_ch = _operator;
        }
    }

    /**
     * Getter of the operator. Returns the operator.
     *
     * @return operator as character
     */
    public char getOperator() {
        return op_ch;
    }

    /**
     * Override toStirng method.
     *
     * @return String operator
     */
    @Override
    public String toString() {
        String str = "";
        str += getOperator();
        return str;
    }

}
