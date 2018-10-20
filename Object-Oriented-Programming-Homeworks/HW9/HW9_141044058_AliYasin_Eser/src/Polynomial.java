
import com.sun.org.apache.xpath.internal.operations.Equals;

/**
 * The class Polynomial is a class that describes polynomials. Contains a double
 * array of coefficients. Member methods can calculate sum, sub and multiply of
 * two polynomials. The class has the necessary setters and getters. The class
 * has redefined toString and equals methods.
 *
 * The class written by Ali Yasin Eser, for :
 *
 * HW9_141044058_AliYasin_Eser
 *
 * @author aliyasineser
 */
public class Polynomial {

    /**
     * Double coefficient array of the class. It is private but it doesn't
     * matters because our getter member function allows to manipulate the
     * array. Still, i used private.
     */
    private double[] doubleCoefficientArray;

    /**
     * Constructor of the class. Takes an double coefficient array and does
     * assignment.
     *
     * @param _arr
     */
    public Polynomial(double[] _arr) {

        doubleCoefficientArray = _arr;
    }

    /**
     * Setter of the double coefficient array. User can change the array with
     * his/her double array.
     *
     * @param _arr
     */
    public void setArr(double[] _arr) {
        doubleCoefficientArray = _arr;
    }

    /**
     * Getter of the double coefficient array. Must be remembered that array can
     * be manipulate when this function called. User can change the coefficient
     * that he/she wants. This function designed on purpose.
     *
     * @return
     */
    public double[] getArr() {
        return doubleCoefficientArray;
    }

    /**
     *
     * @param index
     * @param coefficient
     */
    public void setIndex(int index, double coefficient) {
        doubleCoefficientArray[index] = coefficient;
    }

    /**
     * Calculates the sum of two polynomials . Returns the result.
     *
     * @param second_polynomial
     * @return Result of the calculation as polynomial
     */
    public Polynomial sumArr(Polynomial second_polynomial) {
        Polynomial a;

        Polynomial b, result;

        double[] temp = new double[this.getArr().length];

        for (double u : temp) {
            u = 0.0;
        }

        for (int i = 0; i < second_polynomial.getArr().length; ++i) {
            temp[i] += (second_polynomial.getArr())[i];
        }

        for (int i = 0; i < this.getArr().length; ++i) {
            temp[i] += (this.getArr())[i];
        }

        result = new Polynomial(temp);

        return result;
    }

    /**
     * Calculates the subtraction of two polynomials . Returns the result.
     *
     * @param second_polynomial
     * @return Result of the calculation as polynomial
     */
    public Polynomial subArr(Polynomial second_polynomial) {
        Polynomial a, b, result;

        double[] temp = new double[this.getArr().length];

        for (int i = 0; i < second_polynomial.getArr().length; ++i) {
            temp[i] -= (second_polynomial.getArr())[i];
        }

        for (int i = 0; i < this.getArr().length; ++i) {
            temp[i] += (this.getArr())[i];
        }

        result = new Polynomial(temp);

        return result;
    }

    /**
     * Calculates the multiply of two polynomials . Returns the result.
     *
     * @param second_polynomial
     * @return Result of the calculation as polynomial
     */
    public Polynomial multiplyArr(Polynomial second_polynomial) {

        Polynomial result;

        double[] temp = new double[getArr().length + second_polynomial.getArr().length];

        result = new Polynomial(temp);

        for (int i = 0; i < getArr().length; ++i) {
            for (int j = 0; j < second_polynomial.getArr().length; ++j) {
                result.getArr()[i + j] += getArr()[i] * second_polynomial.getArr()[j];
            }
        }
        return result;

    }

    /**
     * Redefined Method toString.
     *
     * @return String polynomial, ordered as high order x to low order
     */
    @Override
    public String toString() {

        String result = "";

        if (getArr()[getArr().length - 1] != 0.0) {
            result += "(" + getArr()[getArr().length - 1] + ")*x^(" + String.valueOf(getArr().length - 1) + ") + ";
        }

        for (int i = 1; i < getArr().length; ++i) {
            if (getArr()[getArr().length - 1 - i] != 0.0) {
                result += "(" + getArr()[getArr().length - 1 - i] + ")*x^(" + String.valueOf(getArr().length - 1 - i) + ")";

                if (getArr()[getArr().length - 1 - i] != 0.0 && (getArr().length - 1 - i) != 0) {
                    result += " + ";
                }

            }

        }

        return result;

    }

    /**
     * Redefined equals method.
     *
     * @param obj
     * @return boolean return or false.
     */
    @Override
    public boolean equals(Object obj) {

        Polynomial other;

        if (obj instanceof Polynomial) {
            other = (Polynomial) obj;
            if (getArr().length != other.getArr().length) {
                return false;
            } else {
                for (int i = 0; i < getArr().length; ++i) {
                    if (getArr()[i] != other.getArr()[i]) {
                        return false;

                    }
                }
            }

        } else {
            return false;
        }
        return true;

    }

    /**
     * Calculates the result of what if x is equals the given value.
     *
     * @param x
     * @return Result of the calculation
     */
    public double result(double x) {
        double result = 0.0;

        for (int i = 0; i < getArr().length; ++i) {
            result += getArr()[i] * Math.pow(x, i);
        }

        return result;
    }
}
