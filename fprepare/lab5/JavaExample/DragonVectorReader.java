/*
 *  DragonVectorReader
 *
 *  Opens and reads Dragon .VEC file, creating
 *  instances of GeoFeatures.
 *
 *  Created by Sally Goldin, 23 June 2005
 *  Updated 30 December 2011
 */

import java.io.*;
import java.text.*;
import java.awt.*;

/**
 * This class is a simple reader for Dragon vector files.
 * Dragon vector files are a text-based, non-topological
 * external representation for vectors created with the
 * Dragon VEC command. The reader creates an instance of a
 * GeoFeature from each feature it reads from the file.
 * The reader can only read features sequentially.
 */
public class DragonVectorReader
   {
   public static final String FIGURE = "-FIGURE";
   public static final String COORDS = "-COORDS";

   /* reader for the files */
   private BufferedReader reader = null;

   /**
    * Open a vector file, if possible. It will be closed
    * when we open a new file, or get to the end of the old one.
    * @param filename   File to open
    * @return true if successfully opened, false if not found.
    */
   public boolean open(String filename)
      {
      boolean bOk = true;
      try
	 {
	 if (reader != null)
            reader.close();
         }
      catch (IOException io)
	 {
         reader = null;
	 }
      try
	 {
         reader = new BufferedReader(new FileReader(filename));
	 }
      catch (FileNotFoundException fnf)
	 {
         bOk = false;
         reader = null;
	 }
      return bOk;
      }    

   /** 
    * Try to read and parse the next feature from the
    * Dragon vector file. 
    * @return newly constructed GeoFeature, or null if not found
    * or an error occurred.
    */   
   public GeoFeature getNextFeature()
      {
      GeoFeature newFeature = null;
      int featureType = GeoFeature.UNKNOWN;
      Color whichColor = Color.black;
      int pointCount = 0;
      String lineRead = "Start";
      try
	 {
	 if (reader != null)  /* if reader is null, file is not open */
	    {
	    while ((lineRead != null) && (!lineRead.startsWith(FIGURE)))
		lineRead = reader.readLine();
            if (lineRead == null)  /* end of the file */
	       {
	       newFeature = null;
	       return newFeature;
	       }
            
	    /* parse the -FIGURE line */
            String tokens[] = lineRead.split("[\\s]");
            if (tokens.length >= 5)
	       {
	       if (tokens[2].equals("P"))
		  newFeature = new GeoFeature(GeoFeature.POLYGON);
	       else  
	          newFeature = new GeoFeature(GeoFeature.POLYLINE);
	       pointCount = Integer.parseInt(tokens[3]);
	       if (newFeature.getFeatureType() == GeoFeature.POLYGON)
	          pointCount -=1;  /* Dragon stores twice */
	       int colVal = Integer.parseInt(tokens[4]);
	       newFeature.setColor(xlateColor(colVal));
	       for (int i = 0; i < pointCount; i++)
		  {
		  lineRead = reader.readLine();
		  if (!lineRead.startsWith(COORDS))
                     continue; 
		  tokens = lineRead.split("[\\s]");
		  if (tokens.length < 3)
		     break; 
		  int x = (int) 
                         Double.parseDouble(tokens[1]);
		  int y = (int)  
                         Double.parseDouble(tokens[2]);
		  newFeature.addPoint(x,y);
		  }
	       }
	    } /* end if reader not null */
	 }
      catch (IOException ioe)
	 {
         newFeature = null;
         }
      return newFeature;
      }

    /** 
     * Arbitrarily remap a color value between 0 and 255 to
     * a Java color.
     * @param Dragon color index
     * @return Java color to use for drawing.
     */ 
    private Color xlateColor(int colVal)
       {
       if (colVal > 223)
          return Color.blue;
       else if (colVal > 191)
          return Color.magenta;
       else if (colVal > 159)
	  return Color.red;
       else if (colVal > 127)
	  return Color.green;
       else if (colVal > 95)
	  return Color.orange;
       else if (colVal > 63)
	  return Color.cyan;
       else if (colVal > 31)
	  return Color.yellow;
       else
	  return Color.darkGray;
       }
   }




