/**
 * Extension of RectangleTester that displays Rectangles, too.
 *
 * Created by Panithi Suwanno (Big) 63070503426
 */
import java.io.*;
import java.util.*;

public class RectangleTesterGraphics extends RectangleTester
{
	/* Main method first creates the viewer. Then it asks for coordinates, 
	 * creates new triangles, and displays them. Then prints the perimetr and area as well.
	 */
	public static void main(String arguments[])
	{

		boolean bContinue = true;
		FigureViewer viewer = new FigureViewer();
		viewer.pack();
		viewer.show();

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
				viewer.drawRectangle(myRectangle);
				double perim = myRectangle.calcPerimeter();
				System.out.println("Perimeter is " + perim);
				double area = myRectangle.calcArea();
				System.out.println("Area is " + area + "\n\n");
			}
		}   
		System.exit(0);
	}
}
