package com.mycompany.hw01_141044058_aliyasin_eser;

import java.util.ArrayList;

/**
 *
 * @author Ali Yasin Eser
 */
public class courseManagementSystem {

    /**
     * Course list of the system
     */
    private ArrayList<Course> coursesOfTheSystem;
    /**
     * User list of the system
     */
    private ArrayList<AbstractUser> usersOfTheSystem;

    /**
     * login method of the system.
     *
     * @param userID, id as String
     * @param userPassword, pass as String
     * @param isLogin, boolean variable that if it is true, login is correct
     * @return user reference that user entered his/her id and pass
     */
    public AbstractUser loginToTheSystem(String userID, String userPassword, boolean isLogin) {

        for (AbstractUser user : getUsersOfTheSystem()) {
            if (user.getUserID().equals(userID) && user.getUserPassword().equals(userPassword)) {
                isLogin = true;
                return user;
            }
        }

        isLogin = true;
        return new Student(userID, userPassword, "Guest", this, "guess@mail");
    }

    /**
     * polymorphic print method
     */
    public void printAllUsers() {
        System.out.println("Users of the system:");
        for (int i = 0; i < getUsersOfTheSystem().size(); ++i) {
            System.out.printf("%d- ", i + 1);
            getUsersOfTheSystem().get(i).identifyYourself();
        }
    }

    public void printAllCourses() {
        System.out.println("Courses of the system:");
        for (int i = 0; i < getCoursesOfTheSystem().size(); ++i) {
            System.out.printf("%d- %s\n", i + 1, getCoursesOfTheSystem().get(i));

        }
    }

    /**
     * adds course to system
     *
     * @param courseThatShouldBeAdded, course as Course
     * @return true if course added correctly, false otherwise
     */
    public boolean addCourse(Course courseThatShouldBeAdded) {
        try {
            if (!(getCoursesOfTheSystem().contains(courseThatShouldBeAdded))) {
                return getCoursesOfTheSystem().add(courseThatShouldBeAdded);
            } else {
                throw new Exception("Course couldn't be added. Try again and if occurs again, inform the developer.");
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
            return false;
        }
    }

    /**
     * toString override
     *
     * @return String representation
     */
    @Override
    public String toString() {
        return "courseManagementSystem{" + "coursesOfTheSystem=" + coursesOfTheSystem + ", usersOfTheSystem=" + usersOfTheSystem + '}';
    }

    /**
     * Removes course from the system
     *
     * @param courseThatShouldBeRemoved, course as Course
     * @return true if course removed correctly, false otherwise
     */
    public boolean removeCourse(Course courseThatShouldBeRemoved) {

        if (getCoursesOfTheSystem().contains(courseThatShouldBeRemoved)) {
            for (int m = 0; m < getUsersOfTheSystem().size(); ++m) {
                AbstractUser user = getUsersOfTheSystem().get(m);

                if (user instanceof Student) {

                    ArrayList<AbstractAssignable> assignmentsOfCourseThatWillBeRemove = ((Student) user).getAssignmentsOfStudent();
                    for (int i = 0; i < assignmentsOfCourseThatWillBeRemove.size(); ++i) {

                        if (assignmentsOfCourseThatWillBeRemove.get(i).getAssignmentThatWeAddedDocuments().getWhichCoursesAssignment().equals(courseThatShouldBeRemoved)) {

                            ((Student) user).getAssignmentsOfStudent().remove(assignmentsOfCourseThatWillBeRemove.get(i));
                        }

                    }

                    ((Student) user).getCoursesThatStudentTakes().remove(courseThatShouldBeRemoved);

                } else if (user instanceof Tutor) {
                    if (((Tutor) user).getTutorOfWhichCourse().equals(courseThatShouldBeRemoved)) {
                        addUser(new Student(((Tutor) user).getCoursesThatStudentTakes(), ((Tutor) user).getAssignmentsOfStudent(),
                                user.getUserID(), user.getUserPassword(), user.getUserFullName(), user.getOwnerSystemOfUser(), user.getUserEmail()));

                        removeUser((Tutor) user);

                    }

                } else if (user instanceof Teacher) {
                    ((Teacher) user).getCoursesThatTeacherGives().remove(courseThatShouldBeRemoved);

                }
            }

        }
        getCoursesOfTheSystem().remove(courseThatShouldBeRemoved);

        return true;
    }

    /**
     * Adds user to system
     *
     * @param userThatShouldBeAdded, user as AbstractUser
     * @return true if added correctly, false otherwise
     */
    public boolean addUser(AbstractUser userThatShouldBeAdded) {
        try {
            if (!getUsersOfTheSystem().contains(userThatShouldBeAdded)) {
                return getUsersOfTheSystem().add(userThatShouldBeAdded);
            } else {
                throw new Exception("User couldn't be added. Try again and if occurs again, inform the developer.");
            }

        } catch (Exception e) {
            System.out.println(e.getMessage());
            return false;
        }

    }

    /**
     * Removes user from the system
     *
     * @param userThatShouldBeRemoved, user as AbstractUser
     * @return true if removed, false otherwise
     */
    public boolean removeUser(AbstractUser userThatShouldBeRemoved) {
        try {
            if (getUsersOfTheSystem().remove(userThatShouldBeRemoved)) {
                return true;
            } else {
                throw new Exception("Couldn't remove user, try again late. If occurs again, inform the developer.");
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
            return false;
        }

    }

    /**
     * Constructor of the system
     */
    public courseManagementSystem() {
        coursesOfTheSystem = new ArrayList<>();
        usersOfTheSystem = new ArrayList<>();

    }

    /**
     * Getter of the course list
     *
     * @return course list
     */
    public ArrayList<Course> getCoursesOfTheSystem() {
        return coursesOfTheSystem;
    }

    /**
     * Getter of the user list
     *
     * @return user list
     */
    public ArrayList<AbstractUser> getUsersOfTheSystem() {
        return usersOfTheSystem;
    }

    /**
     * Constructor that takes user and course list
     *
     * @param coursesOfTheSystem
     * @param usersOfTheSystem
     */
    public courseManagementSystem(ArrayList<Course> coursesOfTheSystem, ArrayList<AbstractUser> usersOfTheSystem) {
        this.coursesOfTheSystem = coursesOfTheSystem;
        this.usersOfTheSystem = usersOfTheSystem;
    }

}
