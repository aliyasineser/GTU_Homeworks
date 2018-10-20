package com.mycompany.hw01_141044058_aliyasin_eser;

import java.text.SimpleDateFormat;
import java.util.GregorianCalendar;
import java.util.Objects;

/**
 * Abstract assignment class. All assignment classese will inherit this class.
 * Has it's own variables and methods for assignments who will inherit this
 * class.
 *
 * @author Ali Yasin Eser
 */
public abstract class AbstractAssignment {

    /**
     * Assignment of the name as String
     */
    private String assignmentName;
    /**
     * Assignment's course as Course
     */
    private Course whichCoursesAssignment;
    /**
     * Deadline of the assignment as GregorianCalendar
     */
    private GregorianCalendar deadlineDate;
    /**
     * Late deadline of the assignment as GregorianCalendar
     */
    private GregorianCalendar lastDeadlineDate;

    /**
     * Simple date format for the assignment deadlines. Need for good looking
     * representation.
     */
    private static final SimpleDateFormat DATE_FORMAT = new SimpleDateFormat("dd/M/yyyy");

    /**
     * Constructor
     *
     * @param assignmentName, Name of the assignment
     * @param whichCoursesAssignment, Course of the assignment
     * @param deadlineDate, Deadline of the assignment
     * @param lastDeadlineDate, Last deadline of the assignment
     */
    public AbstractAssignment(String assignmentName, Course whichCoursesAssignment, GregorianCalendar deadlineDate, GregorianCalendar lastDeadlineDate) {
        this.assignmentName = assignmentName;
        this.whichCoursesAssignment = whichCoursesAssignment;
        this.deadlineDate = deadlineDate;
        this.lastDeadlineDate = lastDeadlineDate;
    }

    /**
     * Getter of the assignment name
     *
     * @return assignment as String
     */
    public String getAssignmentName() {
        return assignmentName;
    }

    /**
     * setter of the assignment name
     *
     * @param assignmentName, name of the assignment as String
     */
    public void setAssignmentName(String assignmentName) {
        this.assignmentName = assignmentName;
    }

    /**
     * getter of the Course that assignment is in it
     *
     * @return Course as Course
     */
    public Course getWhichCoursesAssignment() {
        return whichCoursesAssignment;
    }

    /**
     * Getter of the deadline date
     *
     * @return deadline as a Calendar
     */
    public GregorianCalendar getDeadlineDate() {
        return deadlineDate;
    }

    /**
     * setter of the Deadline date, added on purpose. Date can be change
     *
     * @param deadlineDate, date
     */
    public void setDeadlineDate(GregorianCalendar deadlineDate) {
        this.deadlineDate = deadlineDate;
    }

    /**
     * Getter of the last deadline date
     *
     * @return Late deadline as a Calendar
     */
    public GregorianCalendar getLastDeadlineDate() {
        return lastDeadlineDate;
    }

    /**
     * setter of the last deadline date
     *
     * @param lastDeadlineDate, date
     */
    public void setLastDeadlineDate(GregorianCalendar lastDeadlineDate) {
        this.lastDeadlineDate = lastDeadlineDate;
    }

    /**
     * Hashcode override
     *
     * @return uniquelike integer
     */
    @Override
    public int hashCode() {
        int hash = 3;
        hash = 53 * hash + Objects.hashCode(this.assignmentName);
        hash = 53 * hash + Objects.hashCode(this.whichCoursesAssignment);
        hash = 53 * hash + Objects.hashCode(this.deadlineDate);
        hash = 53 * hash + Objects.hashCode(this.lastDeadlineDate);
        return hash;
    }

    /**
     * toString override
     *
     * @return String representation
     */
    @Override
    public String toString() {

        return "{" + "assignmentName=" + assignmentName + ", Course=" + whichCoursesAssignment.getNameOfTheCourse() + "}";
    }

    /**
     * equals method override
     *
     * @param obj, object for compare
     * @return true or false as equal or not
     */
    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final AbstractAssignment other = (AbstractAssignment) obj;
        if (!Objects.equals(this.whichCoursesAssignment, other.whichCoursesAssignment)) {
            return false;
        }
        if (!Objects.equals(this.deadlineDate, other.deadlineDate)) {
            return false;
        }
        if (!Objects.equals(this.lastDeadlineDate, other.lastDeadlineDate)) {
            return false;
        }
        return true;
    }

}
