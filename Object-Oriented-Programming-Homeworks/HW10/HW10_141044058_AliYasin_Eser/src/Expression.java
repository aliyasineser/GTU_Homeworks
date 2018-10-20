
/**
 * This is an expression class that can take inputs as element by element and
 * calculates the expression. The developer must be careful about exceptions.
 * All checks in taking input method and calculate method implemented carefully.
 * If there is a problem, please inform the developer of this code. This code
 * written by Ali Yasin Eser (141044058) for Homework 10
 *
 * @author aliyasineser
 */
import java.util.ArrayList;
import java.util.Scanner;

public class Expression {

    /**
     * Object array as ArrayList, for keeping the expression.
     */
    private ArrayList<Object> exp_arr;

    /**
     * Constructor of the array. Takes nothing, initializes the Array.
     */
    public Expression() {
        exp_arr = new ArrayList<>();
    }

    /**
     * Takes the expression as element by element from the user. In the end,
     * there are some algorithm that checks if input entered wrong. These checks
     * can throw exceptions. Must be careful about that.
     *
     * @throws OperatorException
     * @throws OperandException
     * @throws ParanthesisException
     */
    public void takeTheExp() throws OperatorException, OperandException, ParanthesisException {

        String elem;

        Scanner input = new Scanner(System.in);
        System.out.println("Enter your expression. Please enter all the expression elements one by one.");
        // Taking a string and checks what the user entered. If check is correct, algorithm does assignment
        do {
            System.out.println("Enter the expression element:");
            elem = input.nextLine();
            // Operator check
            if (elem.equals("*") || elem.equals("/") || elem.equals("+") || elem.equals("-")) {
                getArr().add(new Operator(elem.charAt(0)));
                //Paranthesis check
            } else if (elem.equals("(") || elem.equals(")")) {
                getArr().add(new Paranthesis(elem.charAt(0)));
                // Operation end check
            } else if (elem.equals("=")) {
            } else {
                // Integer operand check
                try {
                    getArr().add(new Operand(Integer.parseInt(elem)));

                } catch (java.lang.NumberFormatException e) {
                    // If  all checks gives the false, need re-enter the expression element
                    System.out.println("You entered invalid expression element.");
                }
            }

        } while (!elem.equals("="));

        //Control of first or last element is operator 
        if ((getArr().get(0) instanceof Operator)
                || (getArr().get(getArr().size() - 1) instanceof Operator)) {
            throw new OperatorException();
        }

        //Control of  are two operators next to each other
        for (int i = 0; i < getArr().size(); ++i) {
            if (getArr().get(i) instanceof Operator) {
                if (i != 0 || i != getArr().size()) {
                    if ((getArr().get(i - 1) instanceof Operator)
                            || (getArr().get(i + 1) instanceof Operator)) {
                        throw new OperatorException();
                    }
                }
            }
        }

        //Control of paranthesises that opens and closes in that order and no operand or expression in it
        for (int i = 0; i < getArr().size() - 1; ++i) {
            if (getArr().get(i) instanceof Paranthesis && getArr().get(i + 1) instanceof Paranthesis) {
                if (((Paranthesis) getArr().get(i)).getParanthesis() == '('
                        && ((Paranthesis) getArr().get(i + 1)).getParanthesis() == ')') {
                    throw new ParanthesisException();
                }
            }

        }
        //Control of  are two operands are next to each other
        for (int i = 0; i < getArr().size(); ++i) {
            if (getArr().get(i) instanceof Operand) {
                if (i > 1 && i < getArr().size() - 1) {
                    if ((getArr().get(i - 1) instanceof Operand)
                            || (getArr().get(i + 1) instanceof Operand)) {
                        throw new OperandException();
                    }
                }

            }
        }

        //Control of  are paranthesises opened and closed correctly
        int para_count = 0;
        for (int i = 0; i < getArr().size(); ++i) {
            if (getArr().get(i) instanceof Paranthesis) {
                if (((Paranthesis) getArr().get(i)).getParanthesis() == '(') {
                    ++para_count;
                } else if (((Paranthesis) getArr().get(i)).getParanthesis() == ')') {
                    --para_count;
                }
            }
            if (para_count < 0) {
                throw new ParanthesisException();
            }
        }

        if (para_count > 0) {
            throw new ParanthesisException();
        }

        //Control of  are operand and paranthesis'es positions correct
        for (int i = 0; i < getArr().size(); ++i) {
            if (getArr().get(i) instanceof Operand) {
                if (i > 1 && i < getArr().size() - 1) {
                    if ((getArr().get(i - 1) instanceof Paranthesis)) {
                        if (((Paranthesis) (getArr().get(i - 1))).getParanthesis() == ')') {
                            throw new OperandException();
                        }
                    } else if ((getArr().get(i + 1) instanceof Paranthesis)) {
                        if (((Paranthesis) (getArr().get(i + 1))).getParanthesis() == '(') {
                            throw new OperandException();
                        }

                    }
                }

            }
        }

    }

    /**
     * Calculates the given expression. Prints the operations and results step
     * by step. Results array of result.
     *
     * @return ArrayList answer. Just an operand
     * @throws DivideByZeroException
     */
    public ArrayList Calculate() throws DivideByZeroException {
        int start_index, end_index;

        System.out.println(this);
        // For caring all the operations in the one paranthesis
        getArr().add(0, new Paranthesis('('));
        getArr().add(new Paranthesis(')'));

        // Finding how many paranthesis that method will handle
        int count = 0;
        for (int i = 0; i < getArr().size(); ++i) {
            if (getArr().get(i) instanceof Paranthesis) {
                if (((Paranthesis) getArr().get(i)).getParanthesis() == '(') {
                    ++count;
                }
            }
        }
        // Finding higher priority paranthesis'es start index
        for (int par_count = 0; par_count < count; ++par_count) {

            start_index = -1;
            for (int i = 0; i < getArr().size(); ++i) {
                String temp = getArr().get(i).toString();
                if (temp.equals("(")) {
                    start_index = i;
                }
            }

            // Finding higher priority paranthesis'es end index
            boolean flag = false;
            end_index = -1;
            for (int i = start_index; i < getArr().size() && flag != true; ++i) {
                String temp = getArr().get(i).toString();
                if (temp.equals(")")) {
                    end_index = i;
                    flag = true;
                }
            }

            // if check for is there any operation in the paranthesis or just and operand
            if (end_index - start_index != 2) {
                // Calculates all the multiply operatations in the paranthesis
                for (int i = start_index; i < end_index; ++i) {
                    if (getArr().get(i) instanceof Operator) {
                        Operator temp = (Operator) getArr().get(i);
                        String temps = temp.toString();
                        if (temps.equals("*")) {
                            int operand1 = ((Operand) getArr().get(i - 1)).getOperand();
                            int operand2 = ((Operand) getArr().get(i + 1)).getOperand();
                            Operand answer = new Operand(operand1 * operand2);
                            getArr().set(i - 1, answer);
                            getArr().remove(i);
                            getArr().remove(i);
                            end_index -= 2;
                            i = start_index;
                            if (end_index - start_index == 2) {
                                getArr().remove(end_index);
                                getArr().remove(start_index);
                                end_index -= 2;
                            }
                            System.out.println(this);
                        }
                    }
                }
                // Calculates all the division operatations in the paranthesis
                for (int i = start_index; i < end_index; ++i) {
                    if (getArr().get(i) instanceof Operator) {
                        Operator temp = (Operator) getArr().get(i);
                        String temps = temp.toString();
                        if (temps.equals("/")) {
                            int operand1 = ((Operand) getArr().get(i - 1)).getOperand();
                            int operand2 = ((Operand) getArr().get(i + 1)).getOperand();
                            if (operand2 == 0) {
                                throw new DivideByZeroException();
                            }
                            Operand answer = new Operand(operand1 / operand2);
                            getArr().set(i - 1, answer);
                            getArr().remove(i);
                            getArr().remove(i);
                            end_index -= 2;
                            i = start_index;
                            if (end_index - start_index == 2) {
                                getArr().remove(end_index);
                                getArr().remove(start_index);
                                end_index -= 2;
                            }
                            System.out.println(this);
                        }
                    }
                }
                // Calculates all the sum operatations in the paranthesis
                for (int i = start_index; i < end_index; ++i) {
                    if (getArr().get(i) instanceof Operator) {
                        Operator temp = (Operator) getArr().get(i);
                        String temps = temp.toString();
                        if (temps.equals("+")) {
                            int operand1 = ((Operand) getArr().get(i - 1)).getOperand();
                            int operand2 = ((Operand) getArr().get(i + 1)).getOperand();
                            Operand answer = new Operand(operand1 + operand2);
                            getArr().set(i - 1, answer);
                            getArr().remove(i);
                            getArr().remove(i);
                            end_index -= 2;
                            i = start_index;
                            if (end_index - start_index == 2) {
                                getArr().remove(end_index);
                                getArr().remove(start_index);
                                end_index -= 2;
                            }
                            System.out.println(this);
                        }
                    }
                }
                // Calculates all the substraction operatations in the paranthesis
                for (int i = start_index; i < end_index; ++i) {
                    if (getArr().get(i) instanceof Operator) {
                        Operator temp = (Operator) getArr().get(i);
                        String temps = temp.toString();
                        if (temps.equals("-")) {
                            int operand1 = ((Operand) getArr().get(i - 1)).getOperand();
                            int operand2 = ((Operand) getArr().get(i + 1)).getOperand();
                            Operand answer = new Operand(operand1 - operand2);
                            getArr().set(i - 1, answer);
                            getArr().remove(i);
                            getArr().remove(i);
                            end_index -= 2;
                            i = start_index;
                            if (end_index - start_index == 2) {
                                getArr().remove(end_index);
                                getArr().remove(start_index);
                                end_index -= 2;
                            }
                            System.out.println(this);
                        }
                    }
                }

            } else { // if there is just an operand in the paranthesis
                getArr().remove(end_index);
                getArr().remove(start_index);
                end_index -= 2;
            }

        }
        return getArr(); // returning the result
    }

    /**
     * Getter of the expression.
     *
     * @return expression as Array
     */
    public ArrayList getArr() {
        return exp_arr;
    }

    /**
     * Setter of the expression.
     *
     * @param arrayExpression
     */
    public void setArr(ArrayList arrayExpression) {
        exp_arr = arrayExpression;
    }

    /**
     * Class toString method, returns expression as String.
     *
     * @return Expression as String
     */
    @Override
    public String toString() {
        String str = "";

        for (int i = 0; i < getArr().size(); ++i) {
            str += getArr().get(i).toString();
        }
        return str;
    }

}
