
package com.mycompany.hw01_141044058_aliyasin_eser;

import java.util.GregorianCalendar;

/**
 * Group Project class. Just for representing.
 * @author Ali Yasin Eser
 */
public class GroupProject extends AbstractAssignment {

    /**
     * Constructor
     *
     * @param assignmentName, name of the group project as String
     * @param whichCoursesAssignment, assignmet's course as Course
     * @param deadlineDate, deadline date as Calendar
     * @param lastDeadlineDate, last deadline date as Calendar
     */
    public GroupProject(String assignmentName, Course whichCoursesAssignment, GregorianCalendar deadlineDate, GregorianCalendar lastDeadlineDate) {
        super(assignmentName, whichCoursesAssignment, deadlineDate, lastDeadlineDate);
    }

}
