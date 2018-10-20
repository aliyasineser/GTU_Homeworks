/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.mycompany.hw01_141044058_aliyasin_eser;

import java.util.ArrayList;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author Ali Yasin Eser
 */
public class TeacherTest {

    public TeacherTest() {
    }

    @BeforeClass
    public static void setUpClass() {
    }

    @AfterClass
    public static void tearDownClass() {
    }

    @Before
    public void setUp() {
    }

    @After
    public void tearDown() {
    }

    /**
     * Test of toString method, of class Teacher.
     */
    @Test
    public void testToString() {
        courseManagementSystem system = new courseManagementSystem();
        System.out.println("toString");
        Teacher instance = new Teacher("152152152", "3215", "teacher", system, "@gmail.");

        String expResult = "{ Teacher name: teacher,  Courses that teacher give }";
        String result = instance.toString();
        assertEquals(expResult, result);

    }

    /**
     * Test of removeCourseFromSystem method, of class Teacher.
     */
    @Test
    public void testRemoveCourseFromSystem() {
        courseManagementSystem system = new courseManagementSystem();
        System.out.println("removeCourseFromSystem");

        Teacher instance = new Teacher("152152152", "3215", "teacher", system, "@gmail.");
        Course courseThatShouldBeRemoved = new Course("CSE111", instance);
        instance.addCourseToSystem(courseThatShouldBeRemoved);
        boolean expResult = true;
        boolean result = instance.removeCourseFromSystem(courseThatShouldBeRemoved);
        assertEquals(expResult, result);

    }

    /**
     * Test of addUserToSystem method, of class Teacher.
     */
    @Test
    public void testAddUserToSystem() {
        courseManagementSystem system = new courseManagementSystem();
        System.out.println("addUserToSystem");
        AbstractUser userWhoShouldBeAdded = new Student("3215132", "sadasf", "stu", system, "@gmail");
        Teacher instance = new Teacher("152152152", "3215", "teacher", system, "@gmail.");
        boolean expResult = true;
        boolean result = instance.addUserToSystem(userWhoShouldBeAdded);
        assertEquals(expResult, result);
        
    }

    /**
     * Test of addCourseToSystem method, of class Teacher.
     */
    @Test
    public void testAddCourseToSystem() {
        courseManagementSystem system = new courseManagementSystem();
        System.out.println("addCourseToSystem");
        
        Teacher instance = new Teacher("152152152", "3215", "teacher", system, "@gmail.");
        Course courseThatShouldBeAdded = new Course("CSE111", instance);
        boolean expResult = true;
        boolean result = instance.addCourseToSystem(courseThatShouldBeAdded);
        assertEquals(expResult, result);
        
    }

    /**
     * Test of removeUserFromSystem method, of class Teacher.
     */
    @Test
    public void testRemoveUserFromSystem() {
        courseManagementSystem system = new courseManagementSystem();
        System.out.println("removeUserFromSystem");
        AbstractUser userWhoShouldBeRemoved = new Student("3215132", "sadasf", "stu", system, "@gmail");
        Teacher instance = new Teacher("152152152", "3215", "teacher", system, "@gmail.");
        instance.addUserToSystem(userWhoShouldBeRemoved);
        boolean expResult = true;
        boolean result = instance.removeUserFromSystem(userWhoShouldBeRemoved);
        assertEquals(expResult, result);
        
    }



}
