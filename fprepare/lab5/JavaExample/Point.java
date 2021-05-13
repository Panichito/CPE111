/*
 *  Point.java
 *
 *  Simple class representing a point with X and Y
 *  coordinates. 
 *
 *  Created by Sally Goldin, 23 June 2005
 *  Updated 30 Dec 2011
 */

/**
 * Simple class representing a point. Currently it
 * has no behavior, only data. Furthermore the data
 * is all public, with no access methods.
 */
public class Point
   {
   /* coordinates in pixels */ 
   public int X;  /* X coordinate */ 
   public int Y;  /* Y coordinate */

   /** 
    * Constructor sets the values of the coordinates
    */
   public Point(int x, int y)
      {
      this.X = x;
      this.Y = y;
      } 
   }

