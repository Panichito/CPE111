/**
 * StudentManager.java
 *
 * Lab13 - This lab is intended to practice using ArrayList, 
 * one of the simplest of the Java collection classes.
 *
 * Created by Panithi Suwanno (Big) 63070503426
 */
import java.io.*;
import java.util.ArrayList;

public class StudentManager 
{
	protected static ArrayList<Student> allStudent = new ArrayList<Student>();
	
	public static void getStudent() 
	{
		boolean bContinue = true;
		while(bContinue) 
		{ 
			Student addStudent = new Student();
			allStudent.add(addStudent);
			String input = IOUtils.getString("Do yo want to add more students? (Type Y for continue) ");
			if(input.equals("Y") || input.equals("y"))
				System.out.println("Adding more students!\n");
			else 
			{
				System.out.println("Finish Adding Process!\n");
				bContinue = false;
			}
		}
	}

	public static void listStudent()
	{
		System.out.println("Student lists: ");
		int number = 1;
		for(Student nextStudent : allStudent)
		{
			System.out.println(number + ".) " + nextStudent.getStudentName());
			++number;
		}
	}

	public static void findStudent()
	{
		while(true) 
		{
			boolean found = false;
			Integer input = IOUtils.getInteger("\nPlease enter the Student ID you want to search for. (0 to exit)");
			if(input == 0)
				break;
			for(Student findStudent : allStudent)
			{
				if(findStudent.getStudentId() == input)
				{
					found = true;
					findStudent.display();
					System.out.println("Avg. Grade: " + findStudent.computeAvgGrade());
				}
			}
			if(!found)
				System.out.println("Student not found!");
		}
	}

	public static void main(String arguments[]) 
	{
		getStudent();
		listStudent();
		findStudent();
	}
}
