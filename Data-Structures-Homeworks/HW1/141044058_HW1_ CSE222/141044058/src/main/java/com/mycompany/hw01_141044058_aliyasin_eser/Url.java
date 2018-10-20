package com.mycompany.hw01_141044058_aliyasin_eser;

/**
 * Url class. Just for representing.
 *
 * @author Ali Yasin Eser
 */
public class Url extends AbstractDocument {

    /**
     * Constructor
     *
     * @param documentName, name of the document
     */
    public Url(String documentName) {
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

        System.out.println("Url: " + getDocumentName());

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
