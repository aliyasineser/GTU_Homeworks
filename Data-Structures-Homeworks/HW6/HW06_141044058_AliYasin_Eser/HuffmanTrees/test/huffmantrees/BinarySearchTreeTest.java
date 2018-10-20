/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package huffmantrees;

import java.util.Iterator;
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
public class BinarySearchTreeTest {

    public BinarySearchTreeTest() {
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
     * Test of getIterator method, of class BinarySearchTree.
     */
    @Test
    public void IteratorTraversal() {
        System.out.println("getIterator");
        BinarySearchTree instance = new BinarySearchTree();

        instance.add(2);
        instance.add(1);
        instance.add(12);
        instance.add(20);
        instance.add(4);
        instance.add(11);
        instance.add(290);
        instance.add(54);
        instance.add(111);
        instance.add(220);
        instance.add(41);
        instance.add(211);
        instance.add(0);

        Iterator result = instance.getIterator();

        while (result.hasNext()) {
            System.out.println(result.next());
        }

    }

}
