package com.mycompany.hw01_141044058_aliyasin_eser;

/**
 * Authorized abstract user class. Has methods like adding courses, users etc.
 * and all of them abstract. Admin and Teacher will inherit this.
 *
 * @author Ali Yasin Eser
 */
public abstract class AbstractAuthorizedUser extends AbstractUser {

    /**
     * Constructor
     *
     * @param userID, user ID as String
     * @param userPassword, user Pass as String
     * @param userFullName, user Full Name as String
     * @param ownerSystemOfUser, system as courseManagementSystem reference
     * @param userEmail, user e-mail as String
     */
    public AbstractAuthorizedUser(String userID, String userPassword, String userFullName, courseManagementSystem ownerSystemOfUser, String userEmail) {
        super(userID, userPassword, userFullName, ownerSystemOfUser, userEmail);
    }

    /**
     * Adds a user to system user list
     *
     * @param userWhoShouldBeAdded user who we will add to system
     * @return true if added, false otherwise
     */
    public abstract boolean addUserToSystem(AbstractUser userWhoShouldBeAdded);

    /**
     * Removes user from the system, includes their assignment documents
     *
     * @param userWhoShouldBeRemoved user who we will remove from the system
     * @return true if removed, false otherwise
     */
    public abstract boolean removeUserFromSystem(AbstractUser userWhoShouldBeRemoved);

    /**
     * Adds a course to system course list
     *
     * @param courseThatShouldBeAdded course that we will add to system
     * @return true if added, false otherwise
     */
    public abstract boolean addCourseToSystem(Course courseThatShouldBeAdded);

    /**
     * Removes a course from the system course list
     *
     * @param courseThatShuldBeRemoved course that we will remove from the
     * system
     * @return true if removes, false otherwise
     */
    public abstract boolean removeCourseFromSystem(Course courseThatShuldBeRemoved);

}
