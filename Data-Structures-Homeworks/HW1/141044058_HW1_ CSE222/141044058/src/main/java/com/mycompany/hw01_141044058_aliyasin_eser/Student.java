
package com.mycompany.hw01_141044058_aliyasin_eser;

import java.util.ArrayList;

/**
 *
 * @author Ali Yasin Eser
 */
public class Student extends AbstractUser {

    /**
     * Course list that includes courses that student takes
     */
    private ArrayList<Course> coursesThatStudentTakes;
    /**
     * Assignment list that includes assignments that student takes
     */
    private ArrayList<AbstractAssignable> assignmentsOfStudent;

    /**
     * Getter of the course list those student takes
     *
     * @return course list
     */
    public ArrayList<Course> getCoursesThatStudentTakes() {
        return coursesThatStudentTakes;

    }

    /**
     * Override, implemented for polymorphism
     */
    @Override
    public void identifyYourself() {
        System.out.println(getUserFullName() + ", " + getClass().getSimpleName() + ", e-mail:" + getUserEmail());
    }

    /**
     * Adds course to student
     *
     * @param courseThatShouldBeAdded, course
     * @return
     */
    public boolean addCourseToStudent(Course courseThatShouldBeAdded) {

        for (Course courseOfStudent : getCoursesThatStudentTakes()) {
            if (courseOfStudent.equals(courseThatShouldBeAdded)) {
                return true;
            }
        }

        for (Course courseOfSystem : getOwnerSystemOfUser().getCoursesOfTheSystem()) {
            if (courseOfSystem.equals(courseThatShouldBeAdded)) {
                getCoursesThatStudentTakes().add(courseThatShouldBeAdded);
                return true;
            }
        }
        return false;
    }

    /**
     * Removes course from student
     *
     * @param courseThatShouldBeRemoved, Course
     * @return
     */
    public boolean removeCourseFromStudent(Course courseThatShouldBeRemoved) {
        for (Course courseOfStudent : getCoursesThatStudentTakes()) {
            if (courseOfStudent.equals(courseThatShouldBeRemoved)) {
                getCoursesThatStudentTakes().remove(courseThatShouldBeRemoved);
                return true;
            }
        }
        return false;
    }

    /**
     * Getter of the assignment list of the student
     *
     * @return list of assignments
     */
    public ArrayList<AbstractAssignable> getAssignmentsOfStudent() {
        return assignmentsOfStudent;

    }

    /**
     * Construcotr of the Student class
     *
     * @param coursesThatStudentTakes, course list of the student
     * @param assignmentsOfStudent, assignment list of the student
     * @param userID
     * @param userPassword
     * @param userFullName
     * @param ownerSystemOfUser
     * @param userEmail
     */
    public Student(ArrayList<Course> coursesThatStudentTakes, ArrayList<AbstractAssignable> assignmentsOfStudent, String userID, String userPassword, String userFullName, courseManagementSystem ownerSystemOfUser, String userEmail) {
        super(userID, userPassword, userFullName, ownerSystemOfUser, userEmail);
        this.coursesThatStudentTakes = coursesThatStudentTakes;
        this.assignmentsOfStudent = assignmentsOfStudent;
    }

    /**
     * Does enrollment to a course
     *
     * @param courseThatShouldBeAdded
     * @return true if enroll operation done correctly, false otherwise
     */
    public boolean enrollCourse(Course courseThatShouldBeAdded) {
        for (Course course : getOwnerSystemOfUser().getCoursesOfTheSystem()) {

            if (course.equals(courseThatShouldBeAdded)) {

                course.addStudentToEnrollList(this);
                return true;
            }
        }
        return false;
    }

    /**
     * toString override
     *
     * @return String representation
     */
    @Override
    public String toString() {
        String str = "";
        str += "{ coursesThatStudentTakes=";

        for (Course course : coursesThatStudentTakes) {
            str += course.getNameOfTheCourse() + ", ";
        }

        str += "assignmentsOfStudent=";

        for (AbstractAssignable assignment : assignmentsOfStudent) {
            str += assignment.getAssignmentThatWeAddedDocuments().getAssignmentName() + ", ";
        }

        str = str.substring(0, str.length() - 2);

        str += " }";;

        return str;
    }

    /**
     * Does unenrollment to course
     *
     * @param courseThatShouldBeRemoved, course that we will unrollment from
     * @return true if unenrollment operation done correctly, false otherwise
     */
    public boolean unEnrollCourse(Course courseThatShouldBeRemoved) {

        for (AbstractAssignable assignment : getAssignmentsOfStudent()) {

            for (AbstractAssignment courseAssignment : courseThatShouldBeRemoved.getAssignmentsOfTheCourse()) {

                if (assignment.getAssignmentThatWeAddedDocuments() == courseAssignment) {

                    getAssignmentsOfStudent().remove(assignment);
                    break;
                }
            }
        }

        getCoursesThatStudentTakes().remove(courseThatShouldBeRemoved);
        return true;
    }

    /**
     *
     * Constructor of the student, without courses or assignments
     *
     * @param userID
     * @param userPassword
     * @param userFullName
     * @param ownerSystemOfUser
     * @param userEmail
     */
    public Student(String userID, String userPassword, String userFullName, courseManagementSystem ownerSystemOfUser, String userEmail) {
        super(userID, userPassword, userFullName, ownerSystemOfUser, userEmail);
        this.coursesThatStudentTakes = new ArrayList<>();
        this.assignmentsOfStudent = new ArrayList<>();
    }

    /**
     * Does upload operation, takes an assignable and link with assignment
     *
     * @param assignmentOfStudent, assignable object
     * @return true if operation done corretly, false otherwise
     */
    public boolean uploadAssignment(AbstractAssignable assignmentOfStudent) {

        if (assignmentOfStudent instanceof AssignableQuiz) {
            getAssignmentsOfStudent().add(new AssignableQuiz(assignmentOfStudent));
            return true;
        } else if (assignmentOfStudent instanceof AssignableHomework) {
            getAssignmentsOfStudent().add(new AssignableHomework(assignmentOfStudent));
            return true;
        } else if (assignmentOfStudent instanceof AssignableGroupProject) {
            getAssignmentsOfStudent().add(new AssignableGroupProject(assignmentOfStudent));
            return true;
        }
        return false;
    }

}
