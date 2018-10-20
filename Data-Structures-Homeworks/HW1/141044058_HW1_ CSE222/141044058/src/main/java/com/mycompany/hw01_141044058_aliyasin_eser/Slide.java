
package com.mycompany.hw01_141044058_aliyasin_eser;

/**
 * Slide class. Just for representing.
 * @author Ali Yasin Eser
 */
public class Slide extends AbstractDocument {

    /**
     * Constructor
     *
     * @param documentName, name of the document as String
     */
    public Slide(String documentName) {
        super(documentName);
    }

    /**
     * Getter of the document name
     *
     * @return document name as a String
     */
    public String getDocumentName() {
        return documentName;
    }

    /**
     * prints document name, implemented for proof of polymorphism
     */
    @Override
    public void printDocumentName() {

        System.out.println("Slide name: " + getDocumentName());

    }

    /**
     * Override toString
     *
     * @return String representation
     */
    @Override
    public String toString() {
        return super.toString();
    }

}
