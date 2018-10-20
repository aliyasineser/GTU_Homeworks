package com.mycompany.hw01_141044058_aliyasin_eser;

import java.util.ArrayList;

/**
 * Abstract assignable class. Assignable is the class that student class uses
 * for linking their hw, project and quizes with course's assignments.
 *
 * @author Ali Yasin Eser
 */
public class AbstractAssignable implements InterfaceAssignable {

    /**
     * Documents those assigned for assignment
     */
    private ArrayList<AbstractDocument> assignedDocuments;
    /**
     * Which assignment we added documents
     */
    private AbstractAssignment assignmentThatWeAddedDocuments;

    /**
     * Constructor
     *
     * @param assignedDocuments, Documents those assigned for assignment as
     * AbstractDocument ArrayList
     * @param assignmentThatWeAddedDocuments, Which assignment we added
     * documents as AbstractAssignment
     */
    public AbstractAssignable(ArrayList<AbstractDocument> assignedDocuments, AbstractAssignment assignmentThatWeAddedDocuments) {
        this.assignedDocuments = assignedDocuments;
        this.assignmentThatWeAddedDocuments = assignmentThatWeAddedDocuments;
    }

    /**
     * Constructor which takes a reference of same-type object
     *
     * @param mirror, same type object
     */
    public AbstractAssignable(AbstractAssignable mirror) {
        assignedDocuments = mirror.getAssignedDocuments();
        assignmentThatWeAddedDocuments = mirror.getAssignmentThatWeAddedDocuments();
    }

    /**
     * Getter of the document
     *
     * @return Documents ArrayList
     */
    @Override
    public ArrayList<AbstractDocument> getAssignedDocuments() {
        return assignedDocuments;
    }

    /**
     * Getter of the assignment
     *
     * @return Assignment that we assigned as AbstractAssignment
     */
    @Override
    public AbstractAssignment getAssignmentThatWeAddedDocuments() {
        return assignmentThatWeAddedDocuments;
    }

    /**
     * Override toString
     *
     * @return String representation
     */
    @Override
    public String toString() {

        String str = "";
        str += "{ assignedDocuments=";

        for (AbstractDocument doc : getAssignedDocuments()) {
            str += doc.documentName + ", ";
        }

        str += "Assignment name=" + assignmentThatWeAddedDocuments;

        str += " }";;

        return str;

    }

}
