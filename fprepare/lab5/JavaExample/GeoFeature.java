/*
 *  GeoFeature
 * 
 *  Represents a geographic feature (point, polyline or
 *  polygon) in a non-topological vector data model.
 *
 *  Created by Sally Goldin, 23 June 2005
 *  Updated 30 Dec 2011
 */

import java.awt.*;
import java.util.*;

/**
 * This class represents a geographic feature (point, polyline
 * or polygon) in a simple, non-topological vector data model.
 * This class assumes that the coordinate system is all positive,
 * and no coordinate is greater than 99999.
 */
public class GeoFeature
   {
   /* Feature types available. For polygons we do NOT explicitly 
    * store the duplicate final point.
    */ 
   public static final int UNKNOWN = 0;
   public static final int POINT = 1;
   public static final int POLYLINE = 2;
   public static final int POLYGON = 3;

   /* ordered collection of points in the feature */
   private ArrayList<Point> points = null;

   /* type of feature */ 
   private int featureType = UNKNOWN;

   /* color to use for drawing */
   private Color drawColor = Color.black;

   /* Bounding box rectangle coordinates */
   private int minX = 100000;
   private int minY = 100000;
   private int maxX = 0;
   private int maxY = 0;

   /* Actual bounding box as a Rectangle */
   private Rectangle boundingBox = null;

   /**
    * Constructor sets the featureType
    * and allocates storage for points
    * @param type  what type of featue?
    */
   public GeoFeature(int type)
      {
      if ((type > UNKNOWN) && (type <= POLYGON))
         featureType = type;
      points = new ArrayList<Point>();
      boundingBox = new Rectangle(0,0,0,0);
      } 
     
   /**
    * Draw the feature on whatever component
    * the passed Graphics2D is associated with.
    * @param graphics   Graphics context that controls drawing.
    */
   public void draw(Graphics2D graphics)
      {
      graphics.setPaint(drawColor);
      int pointCount = points.size();
      /* put up an X for a single point */
      if ((pointCount == 1) ||
          (featureType == POINT))
          graphics.drawString("X",getPoint(0).X, getPoint(0).Y);
      else
	 {  
	 for (int pt = 0; pt < pointCount - 1; pt++)
	    {
	    graphics.drawLine(getPoint(pt).X, 
			      getPoint(pt).Y,
			      getPoint(pt+1).X, 
			      getPoint(pt+1).Y);
	    } 
	 /* close the polygon */
	 if (featureType == POLYGON)
	    graphics.drawLine(getPoint(pointCount-1).X, 
			      getPoint(pointCount-1).Y,
			      getPoint(0).X, getPoint(0).Y);
         }
      } 


   /**
    * Draw the bounding box of the feature on whatever component
    * the passed Graphics2D is associated with.
    * @param graphics   Graphics context that controls drawing.
    */
   public void drawBoundingBox(Graphics2D graphics)
      {
      graphics.setPaint(Color.black);
      if ((points.size() == 1) ||
          (featureType == POINT))
	 return; /* no box for a point */
      else
	 {  
	 graphics.drawLine(minX,minY, minX,maxY); 
	 graphics.drawLine(minX,maxY, maxX,maxY); 
	 graphics.drawLine(maxX,maxY, maxX,minY); 
	 graphics.drawLine(maxX,minY, minX,minY); 
         }
      } 

   /**
    * Add a new point to the feature,
    * given its X and Y coordinates.
    * Adjust the bounding box coordinates if necessary.
    * @param x   X coordinate
    * @param y   Y coordinate
    */ 
   public void addPoint(int x, int y)
      {
      points.add(new Point(x,y));
      if (x < minX)
         minX = x;
      if (x > maxX)
         maxX = x;
      if (y < minY)
         minY = y;
      if (y > maxY)
         maxY = y;
      }

   /**
    * Get the i-th point in the feature.
    * Return null if i is too large.
    */
   public Point getPoint(int i)
      {
      Point returnPoint = null;
      if ((i >= 0) && (i < points.size()))
          returnPoint = points.get(i);
      return returnPoint;
      }

   /**
    * Return the number of points in the feature.
    */
   public int getPointCount()
      {
      return points.size();
      } 

   /* Getter and Setter functions */
   public int getFeatureType()
      {
      return featureType;
      } 

   public void setFeatureType(int type)
      {
      /* if the value is illegal, just ignore it. */
      if ((type > UNKNOWN) && (type <= POLYGON))
         featureType = type;

      } 

   public void setColor(Color newColor)
      {
      drawColor = newColor;
      }

   public Color getColor()
      {
      return drawColor;
      }

   public Rectangle getBoundingBox()
      {
      boundingBox.x = minX;
      boundingBox.y = minY;
      boundingBox.width = maxX - minX;
      boundingBox.height = maxY - minY;
      return boundingBox;
      } 
   } 

