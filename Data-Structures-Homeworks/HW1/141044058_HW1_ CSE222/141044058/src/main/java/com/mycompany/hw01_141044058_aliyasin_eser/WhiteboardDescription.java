
package com.mycompany.hw01_141044058_aliyasin_eser;

/**
 * WhiteBoard Description class. Just for representing.
 * @author Ali Yasin Eser
 */
public class WhiteboardDescription extends AbstractDocument {

    /**
     * Constructor
     *
     * @param documentName, name of the document as String
     */
    public WhiteboardDescription(String documentName) {
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

        System.out.println("Document name: " + getDocumentName());
        System.out.println("Document type: WhiteBoard Description");

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
