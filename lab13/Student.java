/*
 *  Simple class to represent a student in a registration system.
 *  Includes methods to initialize the student's information.
 *
 *  Created by Sally Goldin, 30 April 2014, for CPE113 Lab 14.
 */


import java.io.*;
import java.util.*;

public class Student
{
	/** student's name */
	protected String studentName = null;

	/** student's ID */    
	protected int studentId = 0;

	/** student's grades in four subjects */
	protected int grades[] = new int[4];

	/** Constructor asks for all the data for a student */
	public Student()
	{
		studentName = IOUtils.getString("Type first and last name for student: ");
		studentId = -999;
		while (studentId == -999)
		{
			studentId = IOUtils.getInteger("Enter student ID number (8 digits): ");
		}
		int i = 0;
		while (i < 4)
		{
			grades[i] = IOUtils.getInteger("Enter numeric grade for subject " + i + "(0 to 100): ");
			if ((grades[i] >= 0) && (grades[i] <= 100)) 
				i++;  
		} 
	}


	/** public getter functions for all member variables */
	public String getStudentName() 
	{
		return studentName;
	}

	/** student's ID */    
	public int getStudentId()
	{
		return studentId; 
	}

	/** student's grades in four subjects 
	 * @param  which - index 0 to 3 for which grade to return
	 * @return grade or -1 if which is out of range
	 */
	public int getOneGrade(int which) 
	{
		int value = -1;
		if ((which >=0) && (which < 4))
			value = grades[which];
		return value;
	}

	/** compute and return the student's average for this year
	 * @return Average of all four grades
	 */
	public double computeAvgGrade()
	{
		double total = 0;
		for (int i = 0; i < 4; i++)
			total += grades[i];
		return total/4;
	}

	/** Show all information about this student.
	*/
	public void display()
	{
		System.out.println("Name:   " + studentName);
		System.out.println("ID:     " + studentId);
		System.out.println("Grades: " +
				grades[0] + " " +
				grades[1] + " " +
				grades[2] + " " +
				grades[3]);
	}


	/* Main method creates one student and then prints it.
	*/
	public static void main(String arguments[])
	{
		Student exampleStudent = new Student();
		System.out.println("Created the following student: ");
		exampleStudent.display();
		System.out.println("Average grade is " + exampleStudent.computeAvgGrade());
	}
}
