/**
 * StudentManagerHash.java
 *
 * Copy StudentManager.java to StudentManagerHash.java.
 * Chang the implementation to use the Hashtable class 
 * instead of the call getStudent() and then listStudent()
 *
 * Created by Panithi Suwanno (Big) 63070503426
 */
import java.io.*;
import java.util.*;

public class StudentManagerHash
{
	protected static Hashtable<Integer, Student> allStudent = new Hashtable<Integer, Student>();
	
	public static void getStudent() 
	{
		boolean bContinue = true;
		while(bContinue) 
		{ 
			Student addStudent = new Student();
			allStudent.put(addStudent.getStudentId(), addStudent);
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
		Iterator<Student> it = allStudent.values().iterator();
		System.out.println("Student lists: ");
		int number = 1;
		while(it.hasNext())
		{
			System.out.println(number + ".) " + it.next().getStudentName());
			++number;
		}
	}

	public static void findStudent()
	{
		while(true)
		{
			Integer key = IOUtils.getInteger("\nPlease enter the Student ID you want to search for. (0 to exit)");
			if(key == 0)
				break;

			if(allStudent.get(key) != null)
			{
				allStudent.get(key).display();
				System.out.println("Avg. Grade: " + allStudent.get(key).computeAvgGrade());
			}
			else 
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
