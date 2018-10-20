package com.mycompany.hw01_141044058_aliyasin_eser;

/**
 * Abstract document class. All the document types will inherit this class. Has
 * a document name, and it's methods. This class has no information about what
 * is book, url etc. because it is written for just representation.
 *
 * @author Ali Yasin Eser
 */
public abstract class AbstractDocument {

    /**
     * Name of the document as String
     */
    protected String documentName;

    /**
     * Constructor
     *
     * @param documentName, name of the document as String
     */
    public AbstractDocument(String documentName) {
        this.documentName = documentName;
    }

    /**
     * prints document name, implemented for proof of polymorphism
     */
    public abstract void printDocumentName();

    /**
     * Override toString
     *
     * @return String representation
     */
    @Override
    public String toString() {
        return documentName;
    }

}
