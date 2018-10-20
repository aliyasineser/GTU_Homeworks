package com.mycompany.hw01_141044058_aliyasin_eser;

/**
 * Interface user. Has abstract methods. That's all.
 *
 * @author Ali Yasin Eser
 */
public interface InterfaceUser {

    /**
     * Getter of the user ID
     *
     * @return String ID as String
     */
    public String getUserID();

    /**
     * Getter of the user pass
     *
     * @return String pass as String
     */
    public String getUserPassword();

    /**
     * Setter of the user pass
     *
     * @param userPassword, password of the user as String
     */
    public void setUserPassword(String userPassword);

    /**
     * Getter of the user's full name
     *
     * @return String user's full name as String
     */
    public String getUserFullName();

    /**
     * Setter of the user's full name
     *
     * @param userFullName, name of the user as String
     */
    public void setUserFullName(String userFullName);

    /**
     * Getter of the system reference
     *
     * @return system reference as String
     */
    public courseManagementSystem getOwnerSystemOfUser();

    /**
     * Getter of the user e-mail
     *
     * @return String mail address as String
     */
    public String getUserEmail();

    /**
     * Setter of the user e-mail address
     *
     * @param userEmail, String e-mail as String
     */
    public void setUserEmail(String userEmail);

    /**
     * Setter of the user ID
     *
     * @param userID, String ID as String
     */
    public void setUserID(String userID);

}
