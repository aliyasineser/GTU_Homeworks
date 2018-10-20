package com.mycompany.hw01_141044058_aliyasin_eser;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.GregorianCalendar;

/**
 *
 * @author Ali Yasin Eser
 */
public class courseManagementSystemTest {

    public static void main(String[] args) {

        try {
            courseManagementSystem system = new courseManagementSystem();
            SimpleDateFormat dateFormat = new SimpleDateFormat("dd/M/yyyy");

            // Adding Admin
            Admin admin = new Admin("000000001", "admin", "admin", system, "adminofyasinmanagement@gmail.com");
            system.addUser(admin);

            // Adding Teachers
            Teacher firstTeacher = new Teacher("10104451", "reveal55", "Erdogan Sevilgen", system, "sevilgen@gtu.edu.tr");
            Teacher secTeacher = new Teacher("091524518", "korealus", "Yusuf Sinan Akgul", system, "akgul@gtu.edu.tr");
            admin.addUserToSystem(firstTeacher);
            admin.addUserToSystem(secTeacher);

            // Adding courses to system
            Course courseCSE222 = new Course("CSE222", firstTeacher);
            system.addCourse(courseCSE222);

            Course courseCSE241 = new Course("CSE241", secTeacher);
            system.addCourse(courseCSE241);

            // Adding student
            Student firstStudent = new Student("141044058", "savage12", "Yasin Eser", system, "aliyasineser@gmail.com");
            admin.addUserToSystem(firstStudent);

            // Student enrolls to CSE222 course
            firstStudent.enrollCourse(courseCSE222);
            firstTeacher.acceptEnrollment();

            // Student enrolls to CSE241 course
            firstStudent.enrollCourse(courseCSE241);
            secTeacher.acceptEnrollment();

            // Erdogan Sevilgen gives HW2 
            firstTeacher.addAssignentToCourse(courseCSE222, new Homework("HW2/Handwritten", courseCSE222, new GregorianCalendar(2016, 1, 31), new GregorianCalendar(2016, 2, 1)));

            // Student adds Assignment to CSE222
            ArrayList<AbstractDocument> studentDocuments = new ArrayList<>();
            studentDocuments.add(new Code("HW2_YasinEser_141044058.java"));
            firstStudent.uploadAssignment(new AssignableHomework(studentDocuments, firstStudent.getCoursesThatStudentTakes().get(firstStudent.getCoursesThatStudentTakes().indexOf(courseCSE222)).getAssignmentsOfTheCourse().get(0)));

            // Out of Scenario, proof of we added the courses
            System.out.println("\nFirst Student information: " + firstStudent);

            // Erdogan Sevilgen adds documents to course
            firstTeacher.getCoursesThatTeacherGives().get(firstTeacher.getCoursesThatTeacherGives().indexOf(courseCSE222)).addDocument(new Slide("CSE222_Slides"));
            firstTeacher.getCoursesThatTeacherGives().get(firstTeacher.getCoursesThatTeacherGives().indexOf(courseCSE222)).addDocument(new Book("Data_Structures"));
            firstTeacher.getCoursesThatTeacherGives().get(firstTeacher.getCoursesThatTeacherGives().indexOf(courseCSE222)).addDocument(new Url("Date_Structures_video_url"));
            firstTeacher.getCoursesThatTeacherGives().get(firstTeacher.getCoursesThatTeacherGives().indexOf(courseCSE222)).addDocument(new File("HW1_Grades"));

            // Erdogan Sevilgen adds a tutor to course
            Tutor firstTutor = new Tutor(courseCSE222, "131044009 ", "letusgo", "Hasan Men", system, "hmen.56@gmail.com");
            firstTeacher.addUserToSystem(firstTutor);
            firstTutor.setTutorOfWhichCourse(courseCSE222);

            // Students reads documents
            System.out.println("\nCSE222 Documents: " + firstStudent.getCoursesThatStudentTakes().get(((firstStudent.getCoursesThatStudentTakes().indexOf(courseCSE222)))).getDocumentsOfTheCourse());

            // Students reads assignments
            System.out.println("\nCSE222 Assignments: " + firstStudent.getCoursesThatStudentTakes().get(((firstStudent.getCoursesThatStudentTakes().indexOf(courseCSE222)))).getAssignmentsOfTheCourse());

            // printing all users, polymorphic call
            system.printAllUsers();
            System.out.println();

            // printing all courses, for being sure about we added the courses to the system
            system.printAllCourses();

            // What if we remove the course?
            System.out.println("CSE222 will be removed.");
            admin.removeCourseFromSystem(courseCSE222);

            // printing all courses, for being sure about we removed the course from the system
            System.out.println();
            system.printAllCourses();

            // Removing assginment of the student
            System.out.println("You will see that we removed the CSE22 course and student's assignment has been deleted. "
                    + "No course, and no assginment for that reason of course.");
            System.out.println(firstStudent.getAssignmentsOfStudent());

            // Tutor is a student now, his course has been deleted
            System.out.println("Look, tutor is student now! His course has been deleted, so...");
            system.printAllUsers();
        } catch (Exception e) {
            System.out.println("An error occured, please inform the developer");
        }
    }
}
