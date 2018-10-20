package com.mycompany.hw01_141044058_aliyasin_eser;

import java.util.ArrayList;

/**
 * Assignable homework class. User can create assignable homework objects for
 * doing assignment to a quiz.
 *
 * @author Ali Yasin Eser
 */
public class AssignableHomework extends AbstractAssignable {

    /**
     * Constructor
     *
     * @param assignedDocuments, documents those assigned for course as
     * AbstractDocument ArrayList
     * @param assignmentThatWeAddedDocuments, assignment that we added documents
     */
    public AssignableHomework(ArrayList<AbstractDocument> assignedDocuments, AbstractAssignment assignmentThatWeAddedDocuments) {
        super(assignedDocuments, assignmentThatWeAddedDocuments);
    }

    /**
     * Constructor that takes super reference of itself
     *
     * @param _abstractAssignable, assignable referene, has same instance fields
     * with the new object
     */
    public AssignableHomework(AbstractAssignable _abstractAssignable) {
        super(_abstractAssignable.getAssignedDocuments(), _abstractAssignable.getAssignmentThatWeAddedDocuments());
    }

}
