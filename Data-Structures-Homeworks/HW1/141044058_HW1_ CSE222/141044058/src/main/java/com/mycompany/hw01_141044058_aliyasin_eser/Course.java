package com.mycompany.hw01_141044058_aliyasin_eser;

import java.util.ArrayList;
import java.util.GregorianCalendar;
import java.util.Objects;

/**
 * Course class. Has it's own variables and methods for encapsulation.
 *
 * @author Ali Yasin Eser
 */
public class Course {

    /**
     * Name of the course as String
     */
    private String nameOfTheCourse;
    /**
     * Assignment list of the course as ArrayList
     */
    private ArrayList<AbstractAssignment> assignmentsOfTheCourse;
    /**
     * Document list of the course as ArrayList
     */
    private ArrayList<AbstractDocument> documentsOfTheCourse;
    /**
     * Teacher of the course as Teacher
     */
    private Teacher teacherOfTheCourse;
    /**
     * Student list for enrollment part as ArrayList. Teacher can accept the
     * enrollment.
     */
    private ArrayList<Student> studentsThatWantsToEnroll;
    /**
     * Creating date of the course as Calendar
     */
    private GregorianCalendar courseCreateDate;
    /**
     * The day that course closed as Calendar
     */
    private GregorianCalendar courseEndDate;

    /**
     * Constructor of the class
     *
     * @param nameOfTheCourse, name of the course as String
     * @param teacherOfTheCourse, Course's teacher as Teacher
     */
    public Course(String nameOfTheCourse, Teacher teacherOfTheCourse) {
        this.nameOfTheCourse = nameOfTheCourse;
        this.teacherOfTheCourse = teacherOfTheCourse;
        assignmentsOfTheCourse = new ArrayList<>();
        documentsOfTheCourse = new ArrayList<>();
        studentsThatWantsToEnroll = new ArrayList<>();
        courseCreateDate = new GregorianCalendar();
        courseEndDate = new GregorianCalendar();

        teacherOfTheCourse.addCourseToTeacher(this);
    }

    /**
     * Getter of the course create date
     *
     * @return date of course's creation as Calendar
     */
    public GregorianCalendar getCourseCreateDate() {
        return courseCreateDate;
    }

    /**
     * Setter of the course create date
     *
     * @param courseCreateDate, date as Calendar
     */
    public void setCourseCreateDate(GregorianCalendar courseCreateDate) {
        this.courseCreateDate = courseCreateDate;
    }

    /**
     * Getter of the course end date
     *
     * @return date of course's creation as Calendar
     */
    public GregorianCalendar getCourseEndDate() {
        return courseEndDate;
    }

    /**
     * Setter of the course end date
     *
     * @param courseEndDate, date as Calendar
     */
    public void setCourseEndDate(GregorianCalendar courseEndDate) {
        this.courseEndDate = courseEndDate;
    }

    /**
     * Almost unique integer hashcode for equal checkt
     *
     * @return hashcode integer
     */
    @Override
    public int hashCode() {
        int hash = 3;
        hash = 89 * hash + Objects.hashCode(this.nameOfTheCourse);
        hash = 89 * hash + Objects.hashCode(this.assignmentsOfTheCourse);
        hash = 89 * hash + Objects.hashCode(this.documentsOfTheCourse);
        hash = 89 * hash + Objects.hashCode(this.teacherOfTheCourse);
        hash = 89 * hash + Objects.hashCode(this.studentsThatWantsToEnroll);
        hash = 89 * hash + Objects.hashCode(this.courseCreateDate);
        hash = 89 * hash + Objects.hashCode(this.courseEndDate);
        return hash;
    }

    /**
     * Adds a student to the enroll list
     *
     * @param wantsToEnroll, students who wants to enroll
     * @return true if operation done correctly, false otherwise
     */
    public boolean addStudentToEnrollList(Student wantsToEnroll) {

        try {
            if (getStudentsThatWantsToEnroll().add(wantsToEnroll)) {
                return true;
            } else {
                throw new Exception("Student can't enroll the list at the moment. Please try again late");
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
            return false;
        }
    }

    /**
     * Removes student from enroll list
     *
     * @param wantsToUnenroll, students who wants to enroll or when theacher
     * accepts the student then it's the removing the enroll list
     * @return true if operation done correctly, false otherwise
     */
    public boolean removeStudentFromEnrollList(Student wantsToUnenroll) {

        try {
            if (getStudentsThatWantsToEnroll().remove(wantsToUnenroll)) {
                return true;
            } else {
                throw new Exception("Student can't enroll the list at the moment. Please try again late");
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
            return false;
        }

    }

    /**
     * Getter of the student list whose want to enroll
     *
     * @return, student enroll list
     */
    public ArrayList<Student> getStudentsThatWantsToEnroll() {
        return studentsThatWantsToEnroll;
    }

    /**
     * Equals override
     *
     * @param obj, other object
     * @return
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
        final Course other = (Course) obj;
        if (!Objects.equals(this.nameOfTheCourse, other.nameOfTheCourse)) {
            return false;
        }
        if (!Objects.equals(this.assignmentsOfTheCourse, other.assignmentsOfTheCourse)) {
            return false;
        }
        if (!Objects.equals(this.documentsOfTheCourse, other.documentsOfTheCourse)) {
            return false;
        }
        if (!Objects.equals(this.teacherOfTheCourse, other.teacherOfTheCourse)) {
            return false;
        }
        return true;
    }

    /**
     * Getter of the name of the course
     *
     * @return String name of the course as String
     */
    public String getNameOfTheCourse() {
        return nameOfTheCourse;
    }

    /**
     * Getter of the assignment list of the course
     *
     * @return assignment list of the course as ArrayList
     */
    public ArrayList<AbstractAssignment> getAssignmentsOfTheCourse() {
        return assignmentsOfTheCourse;
    }

    /**
     * Getter of the document list of the course
     *
     * @return document list of the course as ArrayList
     */
    public ArrayList<AbstractDocument> getDocumentsOfTheCourse() {
        return documentsOfTheCourse;
    }

    /**
     * Getter of the teacher of the course
     *
     * @return teacher of the course as a Teacher object as Teacher
     */
    public Teacher getTeacherOfTheCourse() {
        return teacherOfTheCourse;
    }

    /**
     * Adds an assignment to the course
     *
     * @param assignmentThatShouldBeAdded, assignment that we will add to the
     * course as AbstractAssignment
     * @return true if add operation done, false otherwise
     */
    public boolean addAssignment(AbstractAssignment assignmentThatShouldBeAdded) {
        try {
            if (assignmentThatShouldBeAdded instanceof Quiz) {
                if (getAssignmentsOfTheCourse().add(new Quiz(assignmentThatShouldBeAdded.getAssignmentName(), this,
                        assignmentThatShouldBeAdded.getDeadlineDate(),
                        assignmentThatShouldBeAdded.getLastDeadlineDate()))) {
                    return true;
                } else {
                    throw new Exception("Assignment couldn't added.Please try again and if occurs again, inform the developer.");
                }

            } else if (assignmentThatShouldBeAdded instanceof Homework) {
                if (getAssignmentsOfTheCourse().add(new Homework(assignmentThatShouldBeAdded.getAssignmentName(), this,
                        assignmentThatShouldBeAdded.getDeadlineDate(),
                        assignmentThatShouldBeAdded.getLastDeadlineDate()))) {
                    return true;
                } else {
                    throw new Exception("Assignment couldn't added.Please try again and if occurs again, inform the developer.");
                }

            } else if (assignmentThatShouldBeAdded instanceof GroupProject) {
                if (getAssignmentsOfTheCourse().add(new GroupProject(assignmentThatShouldBeAdded.getAssignmentName(), this,
                        assignmentThatShouldBeAdded.getDeadlineDate(),
                        assignmentThatShouldBeAdded.getLastDeadlineDate()))) {
                    return true;
                }
            } else {
                throw new Exception("Assignment couldn't added.Please try again and if occurs again, inform the developer.");
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        return false;
    }

    /**
     * Removes the assignment from course
     *
     * @param assignmentThatShouldBeRemoved, assignment that we will remove
     * @return true if remove operation done correct, false otherwise
     */
    public boolean removeAssignment(AbstractAssignment assignmentThatShouldBeRemoved) {
        try {
            if (assignmentThatShouldBeRemoved instanceof Quiz) {

                if (getAssignmentsOfTheCourse().remove((Quiz) assignmentThatShouldBeRemoved)) {
                    return true;
                } else {
                    throw new Exception("Quiz couldn't removed. Please try again later and if occurs again, inform the developer.");
                }

            } else if (assignmentThatShouldBeRemoved instanceof Homework) {

                if (getAssignmentsOfTheCourse().remove((Homework) assignmentThatShouldBeRemoved)) {
                    return true;
                } else {
                    throw new Exception("Homework couldn't removed. Please try again later and if occurs again, inform the developer.");
                }
            } else if (assignmentThatShouldBeRemoved instanceof GroupProject) {

                if (getAssignmentsOfTheCourse().remove((GroupProject) assignmentThatShouldBeRemoved)) {
                    return true;
                } else {
                    throw new Exception("Group Project couldn't removed. Please try again later and if occurs again, inform the developer.");
                }

            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
            return false;
        }
        return false;
    }

    /**
     * Override toString method
     *
     * @return String representation
     */
    @Override
    public String toString() {
        return "{ Name of the course =" + nameOfTheCourse + ", Teacher of the course=" + teacherOfTheCourse.getUserFullName() + "}";
    }

    /**
     * adds document to course
     *
     * @param documentThatShouldBeAdded, document that we will add to course as
     * AbstractDocument
     * @return true if add operation done correctly, false otherwise
     */
    public boolean addDocument(AbstractDocument documentThatShouldBeAdded) {
        try {
            if (documentThatShouldBeAdded instanceof File) {
                if (getDocumentsOfTheCourse().add((File) documentThatShouldBeAdded)) {
                    return true;
                } else {
                    throw new Exception("Document couldn't be added. Please try again and occurs again, inform the developer.");
                }
            } else if (documentThatShouldBeAdded instanceof Book) {
                if (getDocumentsOfTheCourse().add((Book) documentThatShouldBeAdded)) {
                    return true;
                } else {
                    throw new Exception("Document couldn't be added. Please try again and occurs again, inform the developer.");
                }
            } else if (documentThatShouldBeAdded instanceof Url) {
                if (getDocumentsOfTheCourse().add((Url) documentThatShouldBeAdded)) {
                    return true;
                } else {
                    throw new Exception("Document couldn't be added. Please try again and occurs again, inform the developer.");
                }
            } else if (documentThatShouldBeAdded instanceof Slide) {
                if (getDocumentsOfTheCourse().add((Slide) documentThatShouldBeAdded)) {
                    return true;
                } else {
                    throw new Exception("Document couldn't be added. Please try again and occurs again, inform the developer.");
                }
            } else if (documentThatShouldBeAdded instanceof WhiteboardDescription) {
                if (getDocumentsOfTheCourse().add((WhiteboardDescription) documentThatShouldBeAdded)) {
                    return true;
                } else {
                    throw new Exception("Document couldn't be added. Please try again and occurs again, inform the developer.");
                }
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
            return false;
        }

        return false;
    }

    /**
     * Removes document from the course
     *
     * @param documentThatShouldBeRemoved, documents that we will remove from
     * the list
     * @return if operation done well returns true, otherwise false
     */
    public boolean removeDocument(AbstractDocument documentThatShouldBeRemoved) {
        try {
            if (documentThatShouldBeRemoved instanceof File) {
                if (getDocumentsOfTheCourse().remove((File) documentThatShouldBeRemoved)) {
                    return true;
                } else {
                    throw new Exception("File couldn't removed. Please try again later and if occurs again, inform the developer.");
                }
            } else if (documentThatShouldBeRemoved instanceof Book) {

                if (getDocumentsOfTheCourse().remove((Book) documentThatShouldBeRemoved)) {
                    return true;
                } else {
                    throw new Exception("Book couldn't removed. Please try again later and if occurs again, inform the developer.");
                }
            } else if (documentThatShouldBeRemoved instanceof Url) {

                if (getDocumentsOfTheCourse().remove((Url) documentThatShouldBeRemoved)) {
                    return true;
                } else {
                    throw new Exception("Url couldn't removed. Please try again later and if occurs again, inform the developer.");
                }

            } else if (documentThatShouldBeRemoved instanceof Slide) {

                if (getDocumentsOfTheCourse().remove((Slide) documentThatShouldBeRemoved)) {
                    return true;
                } else {
                    throw new Exception("Slide couldn't removed. Please try again later and if occurs again, inform the developer.");
                }
            } else if (documentThatShouldBeRemoved instanceof WhiteboardDescription) {

                if (getDocumentsOfTheCourse().remove((WhiteboardDescription) documentThatShouldBeRemoved)) {
                    return true;
                } else {
                    throw new Exception("Whiteboard Description couldn't removed. Please try again later and if occurs again, inform the developer.");
                }

            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
            return false;
        }
        return false;
    }

}
