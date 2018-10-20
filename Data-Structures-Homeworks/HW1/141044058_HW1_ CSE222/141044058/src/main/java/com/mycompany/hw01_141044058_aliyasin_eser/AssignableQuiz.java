package com.mycompany.hw01_141044058_aliyasin_eser;

import java.util.ArrayList;

/**
 * Assignable quiz class. User can create assignable quiz objects for doing
 * assignment to a quiz.
 *
 * @author Ali Yasin Eser
 */
public class AssignableQuiz extends AbstractAssignable {

    /**
     * Constructor
     *
     * @param assignedDocuments, documents those assigned for course as Abstract
     * Document ArrayList
     * @param assignmentThatWeAddedDocuments, assignment that we added as
     * Abstract Assignment documentws
     */
    public AssignableQuiz(ArrayList<AbstractDocument> assignedDocuments, AbstractAssignment assignmentThatWeAddedDocuments) {
        super(assignedDocuments, assignmentThatWeAddedDocuments);
    }

    /**
     * Constructor that takes super reference of itself
     *
     * @param _abstractAssignable, assignable referene, has same instance fields
     * with the new object
     */
    public AssignableQuiz(AbstractAssignable _abstractAssignable) {
        super(_abstractAssignable.getAssignedDocuments(), _abstractAssignable.getAssignmentThatWeAddedDocuments());
    }

}
