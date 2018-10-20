package com.mycompany.hw01_141044058_aliyasin_eser;

/**
 * Tutor class. Inherited from Student and has it's own variable. That variable
 * comes from the course that he/she is tutor on that.
 *
 * @author Ali Yasin Eser
 */
public class Tutor extends Student {

    /**
     * Course that tutor doing his/her job
     */
    Course tutorOfWhichCourse;

    /**
     * Construtor of tutor
     *
     * @param tutorOfWhichCourse, course that he/she doing his/her job
     * @param userID, id as String
     * @param userPassword, pass as String
     * @param userFullName, name as String
     * @param ownerSystemOfUser, system reference as courseManagementSystem
     * @param userEmail , mail address as String
     */
    public Tutor(Course tutorOfWhichCourse, String userID, String userPassword, String userFullName, courseManagementSystem ownerSystemOfUser, String userEmail) {
        super(userID, userPassword, userFullName, ownerSystemOfUser, userEmail);
        this.tutorOfWhichCourse = tutorOfWhichCourse;
    }

    /**
     * Getter of the tutor's course
     *
     * @return
     */
    public Course getTutorOfWhichCourse() {
        return tutorOfWhichCourse;
    }

    /**
     * Setter of the tutor's course
     *
     * @param tutorOfWhichCourse, course that tutor will take as Course
     */
    public void setTutorOfWhichCourse(Course tutorOfWhichCourse) {
        this.tutorOfWhichCourse = tutorOfWhichCourse;
    }

}
