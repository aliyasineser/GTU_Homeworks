package com.mycompany.hw01_141044058_aliyasin_eser;

import java.util.ArrayList;

/**
 *
 * @author Ali Yasin Eser
 */
public class Teacher extends AbstractAuthorizedUser {

    private ArrayList<Course> coursesThatTeacherGives;

    /**
     * Constructor of the Teacher class
     *
     * @param userID, user id as String
     * @param userPassword, users pass as String
     * @param userFullName, users full name as String
     * @param ownerSystemOfUser, system that owns this teacher as reference of
     * courseManagementSystem
     * @param userEmail, user mail as String
     */
    public Teacher(String userID, String userPassword, String userFullName, courseManagementSystem ownerSystemOfUser, String userEmail) {
        super(userID, userPassword, userFullName, ownerSystemOfUser, userEmail);
        coursesThatTeacherGives = new ArrayList<>();
    }

    @Override
    public String toString() {
        String str = "{ Teacher name: " + getUserFullName() + ", ";
        str += " Courses that teacher gives=";

        for (Course course : coursesThatTeacherGives) {
            str += course.getNameOfTheCourse() + ", ";
        }

        str = str.substring(0, str.length() - 2);

        str += " }";

        return str;
    }

    /**
     * Printing a line of string includes users fullname, type and e-mail
     * address
     */
    @Override
    public void identifyYourself() {
        System.out.println(getUserFullName() + ", " + getClass().getSimpleName() + ", e-mail:" + getUserEmail());
    }

    /**
     * Removes a course from the system course list
     *
     * @param courseThatShouldBeRemoved course that we will remove from the
     * system as Course as Course
     * @return true if removes, false otherwise
     */
    @Override
    public boolean removeCourseFromSystem(Course courseThatShouldBeRemoved) {
        for (Course course : this.getCoursesThatTeacherGives()) {

            if (course.equals(courseThatShouldBeRemoved)) {
                for (AbstractUser user : getOwnerSystemOfUser().getUsersOfTheSystem()) {

                    if (user instanceof Student) {

                        ArrayList<AbstractAssignable> assignables = ((Student) user).getAssignmentsOfStudent();
                        for (int i = 0; i < assignables.size(); ++i) {

                            if (assignables.get(i).getAssignmentThatWeAddedDocuments().getWhichCoursesAssignment().equals(courseThatShouldBeRemoved)) {
                                ((Student) user).getAssignmentsOfStudent().remove(assignables.get(i));
                            }

                        }

                        ((Student) user).getCoursesThatStudentTakes().remove(courseThatShouldBeRemoved);

                        return true;

                    } else if (user instanceof Tutor) {
                        if (((Tutor) user).getTutorOfWhichCourse().equals(courseThatShouldBeRemoved)) {
                            getOwnerSystemOfUser().addUser(new Student(((Tutor) user).getCoursesThatStudentTakes(), ((Tutor) user).getAssignmentsOfStudent(),
                                    user.getUserID(), user.getUserPassword(), user.getUserFullName(), user.getOwnerSystemOfUser(), user.getUserEmail()));

                            getOwnerSystemOfUser().removeUser((Tutor) user);

                            return true;
                        }

                    } else {
                        return false;
                    }
                }
                this.getCoursesThatTeacherGives().remove(courseThatShouldBeRemoved);
            }
        }
        return true;
    }

    /**
     * Adds a user to system user list
     *
     * @param userWhoShouldBeAdded user who we will add to system as
     * AbstractUser as AbstractUser
     * @return true if added, false otherwise
     */
    @Override
    public boolean addUserToSystem(AbstractUser userWhoShouldBeAdded) {

        if (userWhoShouldBeAdded instanceof Student || userWhoShouldBeAdded instanceof Tutor) {

            getOwnerSystemOfUser().addUser(userWhoShouldBeAdded);
            return true;

        } else {
            return false;
        }

    }

    /**
     * Adds a course to system course list
     *
     * @param courseThatShouldBeAdded course that we will add to system as
     * Course as Course
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

        getOwnerSystemOfUser().addCourse(courseThatShouldBeAdded);
        return this.addCourseToTeacher(courseThatShouldBeAdded);
    }

    /**
     * Removes user from the system, includes their assignment documents
     *
     * @param userWhoShouldBeRemoved user who we will remove from the system as
     * AbstractUser
     * @return true if removed, false otherwise
     */
    @Override
    public boolean removeUserFromSystem(AbstractUser userWhoShouldBeRemoved) {

        if (userWhoShouldBeRemoved instanceof Student) {
            ((Student) userWhoShouldBeRemoved).getAssignmentsOfStudent().clear();
            ((Student) userWhoShouldBeRemoved).getCoursesThatStudentTakes().clear();

        } else if (userWhoShouldBeRemoved instanceof Tutor) {
            ((Tutor) userWhoShouldBeRemoved).getAssignmentsOfStudent().clear();
            ((Tutor) userWhoShouldBeRemoved).getCoursesThatStudentTakes().clear();

        }
        this.getOwnerSystemOfUser().removeUser(userWhoShouldBeRemoved);
        return true;
    }

    /**
     * Getter of the course list those theacer gives
     *
     * @return array list of course as Course list
     */
    public ArrayList<Course> getCoursesThatTeacherGives() {
        return coursesThatTeacherGives;
    }

    /**
     *
     * @param courseThatShouldBeAdded the course that we will add as Course
     * @return true if course added, false otherwise as boolean
     */
    public boolean addCourseToTeacher(Course courseThatShouldBeAdded) {
        return (coursesThatTeacherGives.add(courseThatShouldBeAdded));

    }

    /**
     * Removes an assignment from course
     *
     * @param courseOfTheAssignment, Course of the assignment as Course
     * @param assignmentThatShouldBeRemoved, assignment that we will remove as
     * Abstract assignment
     * @return true if operation done correctly , false otherwise
     */
    public boolean removeAssignmentFromCourse(Course courseOfTheAssignment, AbstractAssignment assignmentThatShouldBeRemoved) {
        if (getCoursesThatTeacherGives().contains(courseOfTheAssignment)) {

            for (int i = 0; i < getOwnerSystemOfUser().getUsersOfTheSystem().size(); ++i) {
                if (getOwnerSystemOfUser().getUsersOfTheSystem().get(i) instanceof Student) {
                    Student student = (Student) getOwnerSystemOfUser().getUsersOfTheSystem().get(i);
                    for (int j = 0; j < student.getAssignmentsOfStudent().size(); ++j) {
                        if (student.getAssignmentsOfStudent().get(j).getAssignmentThatWeAddedDocuments() == assignmentThatShouldBeRemoved) {
                            student.getAssignmentsOfStudent().remove(j);
                        }
                    }
                } else if (getOwnerSystemOfUser().getUsersOfTheSystem().get(i) instanceof Tutor) {
                    Tutor tutor = (Tutor) getOwnerSystemOfUser().getUsersOfTheSystem().get(i);
                    for (int j = 0; j < tutor.getAssignmentsOfStudent().size(); ++j) {
                        if (tutor.getAssignmentsOfStudent().get(j).getAssignmentThatWeAddedDocuments() == assignmentThatShouldBeRemoved) {
                            tutor.getAssignmentsOfStudent().remove(j);
                        }
                    }
                }
            }
            getCoursesThatTeacherGives().get(getCoursesThatTeacherGives().indexOf(courseOfTheAssignment)).addAssignment(assignmentThatShouldBeRemoved);
            return true;
        }
        return false;
    }

    /**
     * Adds assignment to course
     *
     * @param courseOfTheAssignment, course of the assignment as Course
     * @param assignmentThatShouldBeAdded, assignment that we will add as
     * AbstractAssignment
     * @return true if operation done correctly , false otherwise
     */
    public boolean addAssignentToCourse(Course courseOfTheAssignment, AbstractAssignment assignmentThatShouldBeAdded) {

        if (getCoursesThatTeacherGives().contains(courseOfTheAssignment)) {
            getCoursesThatTeacherGives().get(getCoursesThatTeacherGives().indexOf(courseOfTheAssignment)).addAssignment(assignmentThatShouldBeAdded);
            return true;
        }
        return false;
    }

    /**
     * Teacher accpets students to Course. And deletes the student from
     * enrollment list.
     *
     * @return always true, even if there is no enrollment. This is just an
     * accept code
     */
    public boolean acceptEnrollment() {

        for (int i = 0; i < getCoursesThatTeacherGives().size(); ++i) {
            ArrayList<Student> studentsList = getCoursesThatTeacherGives().get(i).getStudentsThatWantsToEnroll();
            for (int j = 0; j < studentsList.size(); ++j) {
                if (studentsList.get(j).getCoursesThatStudentTakes().contains(getCoursesThatTeacherGives().get(i))) {
                    studentsList.remove(studentsList.get(j));
                } else {

                    studentsList.get(j).addCourseToStudent(getOwnerSystemOfUser().getCoursesOfTheSystem().get(getOwnerSystemOfUser().getCoursesOfTheSystem().indexOf(getCoursesThatTeacherGives().get(i))));
                    studentsList.remove(studentsList.get(j));
                }
            }
        }

        return true;
    }

}
