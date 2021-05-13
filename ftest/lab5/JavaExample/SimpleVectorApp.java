/*
 *  SimpleVectorApp 
 *
 *  Application to display and do simple calculations
 *  relating to a set of vector features.
 *
 *  Created by Sally Goldin, 23 June 2005
 *  Updated 30 December 2011
 */
 
import javax.swing.*;
import javax.swing.border.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;

/**
 * Application to display and do simple calculations
 * relating to a set of vector features.
 * The application manages the vector features and
 * controls the display. It calls methods in other
 * classes to do the calculations.
 */
public class SimpleVectorApp extends JFrame 
                                     implements ActionListener,
                                                MouseListener
   {
   private static String typeNames[] = {"Unknown", "Point", "Polyline",
                                       "Polygon"};    
   /* collection of vector features managed by this app. */
   private ArrayList<GeoFeature> features = null;

   /* UI objects */
   private DrawingCanvas drawCanvas = null;
   private JButton drawButton = null;
   private JButton drawBoxButton = null;
   private JButton clearButton = null;
   private JButton exitButton = null;
   private JButton readButton = null;
   private JTextField fileNameField = null;
   private JComboBox featureList = null;
   private JTextField messageArea = null;

   /* Instance of class to read Dragon vectors */
   /* This will be created the first time we call
    * getDragonVectors
    */
   private DragonVectorReader vectorReader = null;


   /**
    * Constructor creates the User Interface.
    */
   public SimpleVectorApp()
      {
      super("Simple Vector Application");
      features = new ArrayList<GeoFeature>();
      buildUI();
      initializeGeoFeatures();
      initializeFeatureList();
      }

   /**
    * Create the visible part of the user interface. 
    */
   private void buildUI()
      {
      JPanel mainPanel = new JPanel(new BorderLayout());
      mainPanel.setBorder(new EmptyBorder(10,10,10,10));
      JPanel controlPanel = new JPanel(new BorderLayout());
      controlPanel.setBorder(new EtchedBorder());
      JPanel fileSelectPanel = new JPanel(new BorderLayout(5,5));
      JPanel selectPanel = new JPanel(new FlowLayout(FlowLayout.CENTER,10,10));
      selectPanel.setBorder(new EmptyBorder(5,5,5,5));
      JPanel messagePanel = new JPanel(new BorderLayout());
      messagePanel.setBorder(new EmptyBorder(5,5,5,5));
      featureList = new JComboBox();
      selectPanel.add(featureList);

      drawButton = new JButton("Draw");
      drawButton.addActionListener(this);
      selectPanel.add(drawButton);

      drawBoxButton = new JButton("Draw Bounds");
      drawBoxButton.addActionListener(this);
      selectPanel.add(drawBoxButton);

      clearButton = new JButton("Clear");
      clearButton.addActionListener(this);
      selectPanel.add(clearButton);

      exitButton = new JButton("Exit");
      exitButton.addActionListener(this);
      selectPanel.add(exitButton);

      controlPanel.add(selectPanel,BorderLayout.NORTH);

      JPanel textFieldPanel = new JPanel(new GridLayout(0,1,10,19));
      textFieldPanel.setBorder(new EmptyBorder(5,5,5,5));

      fileNameField = new JTextField();
      fileSelectPanel.add(new JLabel("File: "), BorderLayout.WEST);
      fileSelectPanel.add(fileNameField, BorderLayout.CENTER);
      readButton = new JButton("Read Vectors");       
      readButton.addActionListener(this);
      fileSelectPanel.add(readButton, BorderLayout.EAST);
      JPanel inter1 = new JPanel(new BorderLayout());
      inter1.add(fileSelectPanel, BorderLayout.NORTH);
      textFieldPanel.add(inter1); 

      controlPanel.add(textFieldPanel,BorderLayout.CENTER);

      messageArea=new JTextField();
      // messageArea.setEditable(false);
      messagePanel.setBorder(new BevelBorder(BevelBorder.LOWERED));
      //messagePanel.setBorder(new EtchedBorder());
      messagePanel.add(messageArea,BorderLayout.CENTER);
      controlPanel.add(messagePanel,BorderLayout.SOUTH);
      mainPanel.add(controlPanel, BorderLayout.WEST);
 
      drawCanvas = new DrawingCanvas(400,400);
      drawCanvas.addMouseListener(this);
      drawCanvas.setBorder(new EtchedBorder());
      drawCanvas.setBackground(Color.white);
      mainPanel.add(drawCanvas, BorderLayout.CENTER);
      getContentPane().add(mainPanel, BorderLayout.CENTER);
      }


    /**
     * Read a Dragon vector file and add all vectors found
     * to the list of features that can be drawn.
     * The actual reading is handled by an instance of
     * the DragonVectorReader class.
     * @param vectorFile  Name of the Dragon vector file.
     * @return true if at least one vector feature read,
     *         false if file is empty, can't be read, etc.
     */
    protected boolean getDragonVectors(String vectorFile)
       {
       boolean bOk = true;
       clearMessage();
       if (vectorReader == null)
          vectorReader = new DragonVectorReader();
       if (vectorReader.open(vectorFile) == false)
	  {
          showMessage("Error opening vector file " + vectorFile);
          bOk = false;
	  }
       else
	  {
	  features.clear(); /* discard old features if any */
          GeoFeature feature = null;
          while ((feature = vectorReader.getNextFeature()) != null)
              features.add(feature);
	  }
       if (features.size() == 0) /* nothing read */
          bOk = false;
       return bOk;
       }

     /* set up a dummy list of features just for testing
      */
    private void initializeGeoFeatures()
      {
      GeoFeature f = new GeoFeature(GeoFeature.POLYGON);
      f.setColor(Color.red);
      f.addPoint(40,50);
      f.addPoint(46,60);
      f.addPoint(100,120);
      f.addPoint(125,65);
      f.addPoint(30,210);
      features.add(f);

      f = new GeoFeature(GeoFeature.POLYLINE);
      f.setColor(Color.blue);
      f.addPoint(140,50);
      f.addPoint(246,60);
      f.addPoint(100,120);
      f.addPoint(25,65);
      f.addPoint(130,110);
      features.add(f);

      f = new GeoFeature(GeoFeature.POINT);
      f.setColor(Color.blue);
      f.addPoint(200,260);
      features.add(f);

      f = new GeoFeature(GeoFeature.POLYGON);
      f.setColor(Color.green);
      f.addPoint(50,140);
      f.addPoint(60, 200);
      f.addPoint(100,300);
      f.addPoint(25,65);
      f.addPoint(210,110);
      f.addPoint(300,110);
      features.add(f);
      }  
 

     /** 
      * Initalize the drop down to hold a list
      * of the polygons available to draw.
      */ 
    private void initializeFeatureList()
       {
       /* clear any old values */
       int items = featureList.getItemCount();
       items--;
       while (items >= 0)
	  {
          featureList.removeItemAt(items);
          items--;
          }
       int featureCount = features.size();
       for (int i = 0; i < featureCount; i++)
	  {
          GeoFeature feature = features.get(i);
          StringBuffer buffer = new StringBuffer();
          buffer.append(String.valueOf(i));
          buffer.append(" -- " + typeNames[feature.getFeatureType()]);
	  buffer.append(" - " + String.valueOf(feature.getPointCount()));
	  buffer.append(" points");
          featureList.addItem(buffer.toString());
	  }
       }

     /**
      * This method will be called when the user
      * clicks in the drawing area. The method
      * will find a polygon whose bounding box 
      * includes the point clicked on, if any,
      * and will draw it (after clearing the
      * drawing area). If there is no polygon whose
      * bounding box includes the point, the method
      * will display a message saying this.
      * @param x   X coord where mouse was clicked
      * @param y   Y coord where mouse was clicked
      */
    private void findPolygon(int x, int y)
       {
       StringBuffer buffer = new StringBuffer();
       buffer.append("Mouse was clicked at point ");
       buffer.append(String.valueOf(x) + ", ");
       buffer.append(String.valueOf(y));
       showMessage(buffer.toString());

       /** WRITE YOUR CODE HERE **/

       }
    /**
     * Displays a short message in the message area.
     * Will be truncated if too long.
     * @param message String to display
     */
    public void showMessage(String message)
       {
       messageArea.setText(message);       
       }  

    /**
     * Erases any text in the message area.
     */
    public void clearMessage()
       {
       messageArea.setText("");       
       }  


    /** 
     * This is the method required for the ActionListener 
     * interface. It handles the necessary actions when 
     * buttons are pressed.
     */
    public void actionPerformed(ActionEvent e)
       {
       Object source = e.getSource();
       if (source == exitButton)
          {
	  System.exit(0);
          }
       else if (source == drawButton)
	  {
          int index = featureList.getSelectedIndex();
          if (index >= 0)
	     {
             GeoFeature f = features.get(index);
             f.draw((Graphics2D) drawCanvas.getGraphics()); 
	     }
	  }
       else if (source == drawBoxButton)
	  {
          int index = featureList.getSelectedIndex();
          if (index >= 0)
	     {
             GeoFeature f = features.get(index);
             f.drawBoundingBox((Graphics2D) drawCanvas.getGraphics()); 
	     }
	  }
       else if (source == clearButton)
	  {
          drawCanvas.clear();
	  }
       else if (source == readButton)
	  {
          boolean bOk = getDragonVectors(fileNameField.getText());
          if (bOk)
	     {
             initializeFeatureList();
	     }
	  else
	     {
             if (features.size() == 0)
                 showMessage("No features found in file " +
                             fileNameField.getText());
	     }
	  } 
       }


     /** MouseListener methods **/
     /* we are only interested in clicks, so we leave
      * the other methods empty. If these events
      * happen, the program will simply ignore them.
      */
     public void mouseEntered(MouseEvent mouseEv)
        {
        }
     public void mouseExited(MouseEvent mouseEv)
        {
        }
     public void mousePressed(MouseEvent mouseEv)
        {
        }
     public void mouseReleased(MouseEvent mouseEv)
        {
        }

     /**
      * If the user clicks the mouse in the drawing area,
      * get the point and pass it to findPolygon.
      */
     public void mouseClicked(MouseEvent mouseEv)
        {
	/* Highlight the point clicked */
	Graphics2D g = (Graphics2D) drawCanvas.getGraphics();
	g.setColor(Color.red);
	g.drawString("x",mouseEv.getX(), mouseEv.getY()); 
        findPolygon(mouseEv.getX(), mouseEv.getY());
        }


  /**
   * Driver to start the application running.
   */
  public static void main(String args[])
     {		      
     try
        {
        UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
	}
     catch (Exception ex)
        {
        System.out.println("Error setting look and feel!");
        System.exit(1);
        }
     SimpleVectorApp app = new SimpleVectorApp();
     app.pack();
     app.show();
     }
}




