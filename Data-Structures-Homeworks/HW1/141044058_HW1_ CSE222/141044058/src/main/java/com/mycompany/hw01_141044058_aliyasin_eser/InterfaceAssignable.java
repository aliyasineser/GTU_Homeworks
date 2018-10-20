package com.mycompany.hw01_141044058_aliyasin_eser;

import java.util.ArrayList;

/**
 * Interface Assignable. Has fundamental methods.
 *
 * @author Ali Yasin Eser
 */
public interface InterfaceAssignable {

    /**
     * Getter of the assignment that we added documents
     *
     * @return assignment
     */
    public abstract AbstractAssignment getAssignmentThatWeAddedDocuments();

    /**
     * Getter documents that we assigned to assignment
     *
     * @return
     */
    public abstract ArrayList<AbstractDocument> getAssignedDocuments();
}
