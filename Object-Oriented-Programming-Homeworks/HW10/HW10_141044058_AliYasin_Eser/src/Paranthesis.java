
/**
 * This is an paranthesis class for keeping expressions paranthesis parts. Keeps
 * a character and have methods for manipulating it;
 *
 * @author aliyasineser
 */
public class Paranthesis {

    // Variable
    private char par_ch;

    /**
     * Constructor of the class.
     *
     * @param _paranthesis
     */
    public Paranthesis(char _paranthesis) {
        setParanthesis(_paranthesis);
    }

    /**
     * Setter of the paranthesis. Has check for is that really a paranthesis
     * symbol.
     *
     * @param _par
     */
    public void setParanthesis(char _par) {
        if (_par == '(' || _par == ')') {
            par_ch = _par;
        }
    }

    /**
     * Getter of the Paranthesis.Returns the paranthesis.
     *
     * @return Paranthesis symbol
     */
    public char getParanthesis() {
        return par_ch;
    }

    /**
     * Override toString method.
     *
     * @return String paranthesis
     */
    @Override
    public String toString() {
        String str = "";
        str += getParanthesis();
        return str;
    }

}
