
/**
 * This is an operand class for keeping expressions operand parts. Keeps a
 * private integer and have methods to manipulate it.
 *
 * @author aliyasineser
 */
public class Operand {

    //Variable
    private int operand;

    /**
     * Constructor of the class
     *
     * @param _operand
     */
    public Operand(int _operand) {
        setOperand(_operand);
    }

    /**
     * Setter of the operand. Sets the operand integer.
     *
     * @param _operand
     */
    public void setOperand(int _operand) {
        operand = _operand;
    }

    /**
     * Getter of the operand. Returns the integer operand
     *
     * @return operand
     */
    public int getOperand() {
        return operand;
    }

    /**
     * toString method override.
     *
     * @return String operand
     */
    @Override
    public String toString() {
        String str = "";
        str += getOperand();
        return str;
    }

}
