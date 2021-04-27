/**
 * RectangleTester.java
 *
 * Lab12 - This las is intended to give a practive compiling and running 
 * Java programs, and in implementing simple classes of your own.
 *
 * Created by Panithi Suwanno (Big) 63070503426
 * Tue. 27 April 2021 
 */
import java.io.*;

public class RectangleTester
{

	/**
	 * Asks for one of the coordinates, and returns it as the function value.
	 * @param   prompt    String to print, telling which coordinate
	 * @return  the coordinate. Exits with error if user types in
	 *          something that can't be read as an integer 
	 */
	protected static int getOneCoordinate(String prompt)
	{
		int value = 0;	   
		String inputString;
		int readBytes = 0;
		byte buffer[] = new byte[200]; 
		System.out.println(prompt);
		try
		{
			readBytes = System.in.read(buffer,0,200);
		}
		catch (IOException ioe)
		{
			System.out.println("Input/output exception - Exiting");
			System.exit(1);
		}
		inputString = new String(buffer);
		try 
		{
			int pos = inputString.indexOf("\r");
			if (pos < 0)
				pos = inputString.indexOf("\n");
			if (pos >= 0)
				inputString = inputString.substring(0,pos);
			value = Integer.parseInt(inputString);
		}
		catch (NumberFormatException nfe) 
		{
			System.out.println("Bad number entered - Exiting");
			System.exit(1);
		}
		return value;
	}

	/* Main method asks for coordinates and then creates new Rectangles. Then it calls 
	 * the perimeter and area methods for the newly created triangle.
	 */
	public static void main(String arguments[])
	{
		boolean bContinue = true;
		while (bContinue)
		{
			int x1, x2;
			int y1, y2;
			x1 = getOneCoordinate("Enter x for point 1 (negative to exit): ");
			if (x1 < 0)
			{
				bContinue = false;
			}
			else
			{
				y1 = getOneCoordinate("Enter y for point 1: ");
				x2 = getOneCoordinate("Enter x for point 2: ");
				y2 = getOneCoordinate("Enter y for point 2: ");
				MyRectangle myRectangle = new MyRectangle(x1, y1, x2, y2);
				double perim = myRectangle.calcPerimeter();
				System.out.println("Perimeter is " + perim);
				double area = myRectangle.calcArea();
				System.out.println("Area is " + area + "\n\n");
			}
		}   
	}
}
