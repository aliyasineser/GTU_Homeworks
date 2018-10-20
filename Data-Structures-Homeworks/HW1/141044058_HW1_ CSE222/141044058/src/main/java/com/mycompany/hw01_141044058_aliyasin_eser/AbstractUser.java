package com.mycompany.hw01_141044058_aliyasin_eser;

import java.util.Objects;

/**
 * Abstract user class. Student, Tutor, Teacher and Admin will inherit this
 * class. Includes fundamental method implementations and variables.
 *
 * @author Ali Yasin Eser
 */
public abstract class AbstractUser implements InterfaceUser {

    /**
     * ID of the user as String
     */
    private String userID;
    /**
     * Password of the user as String
     */
    private String userPassword;
    /**
     * Full name of the user as String
     */
    private String userFullName;
    /**
     * System reference for backing as courseManagementSystem reference
     */
    private courseManagementSystem ownerSystemOfUser;
    /**
     * e-mail of the user as String
     */
    private String userEmail;

    /**
     * Abstract class that user prints something about himself/herself Added for
     * proof that i already know polymorphism
     */
    public abstract void identifyYourself();

    /**
     * Constructor
     *
     * @param userID, ID of the user as String
     * @param userPassword, Password of the user as String
     * @param userFullName, Full name of the user as String
     * @param ownerSystemOfUser, System reference for backing
     * @param userEmail, e-mail of the user as String
     */
    public AbstractUser(String userID, String userPassword, String userFullName, courseManagementSystem ownerSystemOfUser, String userEmail) {
        this.userID = userID;
        this.userPassword = userPassword;
        this.userFullName = userFullName;
        this.ownerSystemOfUser = ownerSystemOfUser;
        this.userEmail = userEmail;
    }

    /**
     * Override toString
     *
     * @return String representation
     */
    @Override
    public String toString() {
        return "User full name" + userFullName + ", " + getClass().getTypeName() + ", userID=" + userID + ", userEmail=" + userEmail;
    }

    /**
     * Hashcode override
     *
     * @return uniquelike integer
     */
    @Override
    public int hashCode() {
        int hash = 3;
        hash = 67 * hash + Objects.hashCode(this.userID);
        hash = 67 * hash + Objects.hashCode(this.userPassword);
        hash = 67 * hash + Objects.hashCode(this.userFullName);
        hash = 67 * hash + Objects.hashCode(this.ownerSystemOfUser);
        hash = 67 * hash + Objects.hashCode(this.userEmail);
        return hash;
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
        final AbstractUser other = (AbstractUser) obj;
        if (!Objects.equals(this.userID, other.userID)) {
            return false;
        }
        if (!Objects.equals(this.userPassword, other.userPassword)) {
            return false;
        }
        if (!Objects.equals(this.userFullName, other.userFullName)) {
            return false;
        }
        if (!Objects.equals(this.userEmail, other.userEmail)) {
            return false;
        }
        if (!Objects.equals(this.ownerSystemOfUser, other.ownerSystemOfUser)) {
            return false;
        }
        return true;
    }

    /**
     * Getter of the user ID
     *
     * @return user ID as String
     */
    @Override
    public String getUserID() {
        return userID;
    }

    /**
     * Setter of the user ID
     *
     * @param userID as String
     */
    @Override
    public void setUserID(String userID) {
        this.userID = userID;
    }

    /**
     * Getter of the user pass
     *
     * @return user pass as String
     */
    @Override
    public String getUserPassword() {
        return userPassword;
    }

    /**
     * Setter of the user pass
     *
     * @param userPassword as String
     */
    @Override
    public void setUserPassword(String userPassword) {
        this.userPassword = userPassword;
    }

    /**
     * Getter of the users full name
     *
     * @return full name of the user as String
     */
    @Override
    public String getUserFullName() {
        return userFullName;
    }

    /**
     * Setter of the user Full name
     *
     * @param userFullName, user name as String
     */
    @Override
    public void setUserFullName(String userFullName) {
        this.userFullName = userFullName;
    }

    /**
     * Getter of the system reference
     *
     * @return system reference as courseManagementSystem
     */
    @Override
    public courseManagementSystem getOwnerSystemOfUser() {
        return ownerSystemOfUser;
    }

    /**
     * Getter of the user e-mail
     *
     * @return user e-mail as a String
     */
    @Override
    public String getUserEmail() {
        return userEmail;
    }

    /**
     * Setter of the user e-mail
     *
     * @param userEmail, mail as String
     */
    @Override
    public void setUserEmail(String userEmail) {
        this.userEmail = userEmail;
    }

}
