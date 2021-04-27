/**
 * MyRectangle.java
 *
 * Lab12 - This las is intended to give a practive compiling and running 
 * Java programs, and in implementing simple classes of your own.
 *
 * Created by Panithi Suwanno (Big) 63070503426
 * Tue. 27 April 2021 
 */

public class MyRectangle
{
	/** X coordinates of three points defining the rectangle */
	private int xcoord[] = new int[2];

	/** Y coordinates of three points defining the rectangle */
	private int ycoord[] = new int[2];

	/**
	 * Constructor creates a new Rectangle by setting the
	 * values of the sets of vertext coordinates.
	 * @param     x1        X coord of first vertex
	 * @param     y1        Y coord of first vertex
	 * @param     x2        X coord of second vertex
	 * @param     y2        Y coord of second vertex
	 */
	public MyRectangle(int x1, int y1, int x2, int y2)
	{
		xcoord[0] = x1;
		xcoord[1] = x2;
		ycoord[0] = y1;
		ycoord[1] = y2;
	}

	/** 
	 * Return one of the X coordinates
	 * @param  which    1 or 2 specifying which vertex we want
	 * @return vertex X coordinate, or -1 if argument is not 1 or 2
	 */
	public int getX(int which)
	{
		int coordVal = -1;
		if((which > 0) && (which < 3))
			coordVal = xcoord[which-1];  /* remember arrays start at o! */
		return coordVal;
	}

	/** 
	 * Return one of the Y coordinates
	 * @param  which    1 or 2 specifying which vertex we want
	 * @return vertex Y coordinate, or -1 if argument is not 1 or 2
	 */
	public int getY(int which)
	{
		int coordVal = -1;
		if((which > 0) && (which < 3))
			coordVal = ycoord[which-1];  /* remember arrays start at o! */
		return coordVal;
	}

	/**
	 * calculate the perimeter of this Rectangle
	 * @return perimeter value
	 */
	public double calcPerimeter()
	{
		double perimeter = (2 * Math.abs(xcoord[0] - xcoord[1])) + (2 * Math.abs(ycoord[0] - ycoord[1]));
		return perimeter;
	}

	/**
	 * calculate the area of this Rectangle
	 * @return area value
	 */
	public double calcArea()
	{
		int area = Math.abs(xcoord[0] - xcoord[1]) * Math.abs(ycoord[0] - ycoord[1]);
		return area;
	}
}
