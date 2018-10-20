package com.mycompany.hw01_141044058_aliyasin_eser;

import java.util.ArrayList;

/**
 * Admin class. Has inherited methods for managing the system.
 *
 * @author Ali Yasin Eser
 */
public class Admin extends AbstractAuthorizedUser {

    /**
     * Constructor of the Admin class
     *
     * @param userID, user id
     * @param userPassword, users pass
     * @param userFullName, users full name
     * @param ownerSystemOfUser, system that owns this admin
     * @param userEmail, user mail
     */
    public Admin(String userID, String userPassword, String userFullName, courseManagementSystem ownerSystemOfUser, String userEmail) {
        super(userID, userPassword, userFullName, ownerSystemOfUser, userEmail);
    }

    /**
     * Abstract class that user prints something about himself/herself Added for
     * proof that i already know polymorphism
     */
    @Override
    public void identifyYourself() {
        System.out.println(getUserFullName() + ", " + getClass().getSimpleName() + ", e-mail:" + getUserEmail());
    }

    @Override
    public String toString() {
        return "Admin";
    }

    /**
     * Removes a course from the system course list
     *
     * @param courseThatShouldBeRemoved course that we will remove from the
     * system
     * @return true if removes, false otherwise
     */
    @Override
    public boolean removeCourseFromSystem(Course courseThatShouldBeRemoved) {
        for (AbstractUser user : getOwnerSystemOfUser().getUsersOfTheSystem()) {

            if (user instanceof Tutor) {
                if (((Tutor) user).getTutorOfWhichCourse().equals(courseThatShouldBeRemoved)) {
                    
                    getOwnerSystemOfUser().addUser(new Student(((Tutor) user).getCoursesThatStudentTakes(), ((Tutor) user).getAssignmentsOfStudent(),
                            user.getUserID(), user.getUserPassword(), user.getUserFullName(), user.getOwnerSystemOfUser(), user.getUserEmail()));

                    getOwnerSystemOfUser().removeUser((Tutor) user);

                }

            } else if (user instanceof Student) {

                ArrayList<AbstractAssignable> assignables = ((Student) user).getAssignmentsOfStudent();
                for (int i = 0; i < assignables.size(); ++i) {

                    if (assignables.get(i).getAssignmentThatWeAddedDocuments().getWhichCoursesAssignment().equals(courseThatShouldBeRemoved)) {
                        ((Student) user).getAssignmentsOfStudent().remove(assignables.get(i));
                    }

                }
                ((Student) user).getCoursesThatStudentTakes().remove(courseThatShouldBeRemoved);

            }
        }
        return getOwnerSystemOfUser().getCoursesOfTheSystem().remove(courseThatShouldBeRemoved);

    }

    /**
     * Adds a user to system user list
     *
     * @param userWhoShouldBeAdded user who we will add to system
     * @return true if added, false otherwise
     */
    @Override
    public boolean addUserToSystem(AbstractUser userWhoShouldBeAdded) {

        getOwnerSystemOfUser().addUser(userWhoShouldBeAdded);
        return true;

    }

    /**
     * Adds a course to system course list
     *
     * @param courseThatShouldBeAdded course that we will add to system
     * @return true if added, false otherwise
     */
    @Override
    public boolean addCourseToSystem(Course courseThatShouldBeAdded) {
        ArrayList<Course> courses = (getOwnerSystemOfUser().getCoursesOfTheSystem());
        for (int i = 0; i < courses.size(); ++i) {
            if (courses.get(i).equals(courseThatShouldBeAdded)) {
                return false;
            }
        }
        return getOwnerSystemOfUser().addCourse(courseThatShouldBeAdded);

    }

    /**
     * Removes user from the system, includes their assignment documents
     *
     * @param userWhoShouldBeRemoved user who we will remove from the system
     * @return true if removed, false otherwise
     */
    @Override
    public boolean removeUserFromSystem(AbstractUser userWhoShouldBeRemoved) {

        if (userWhoShouldBeRemoved instanceof Student) {
            ((Student) userWhoShouldBeRemoved).getAssignmentsOfStudent().clear();
            ((Student) userWhoShouldBeRemoved).getCoursesThatStudentTakes().clear();
            this.getOwnerSystemOfUser().removeUser(userWhoShouldBeRemoved);
            return true;
        } else if (userWhoShouldBeRemoved instanceof Tutor) {
            ((Tutor) userWhoShouldBeRemoved).getAssignmentsOfStudent().clear();
            ((Tutor) userWhoShouldBeRemoved).getCoursesThatStudentTakes().clear();
            this.getOwnerSystemOfUser().removeUser(userWhoShouldBeRemoved);
            return true;
        } else if (userWhoShouldBeRemoved instanceof Teacher) {

            ArrayList<Course> courses = ((Teacher) userWhoShouldBeRemoved).getCoursesThatTeacherGives();
            for (int i = 0; i < courses.size(); ++i) {
                getOwnerSystemOfUser().removeCourse(courses.get(i));
            }

            ((Teacher) userWhoShouldBeRemoved).getCoursesThatTeacherGives().clear();

            getOwnerSystemOfUser().getUsersOfTheSystem().remove(userWhoShouldBeRemoved);

        } else if (userWhoShouldBeRemoved instanceof Admin) {
            getOwnerSystemOfUser().getUsersOfTheSystem().remove(userWhoShouldBeRemoved);

        } else {
            return false;
        }

        return true;
    }

}
