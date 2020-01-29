package test;

//File   : GUI-lowlevel/animation/analogclock/Clock.java
//Purpose: An analog clock component -- Uses Timer and Calendar.
//Note   : Uses a BufferedImage for clock face so isn't drawn each time.
//Author : Fred Swartz, 1999-2007, Placed in public domain.

//C:\Documents and Settings\ChohanS.INFLITE\My Documents\JBuilder2007\Test\bin>
//c:/jbuilder2007/jre/bin/java pk2.ClockAnalogBuf

import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.awt.image.*;

////////////////////////////////////////////////////////////////Clock class
class Clock extends JComponent {
 
 //============================================================ constants
 private static final double TWO_PI   = 2.0 * Math.PI;
 
 private static final int    UPDATE_INTERVAL = 10;  // Millisecs
 private static int RPM = 2;
// private double interval = RPM*UPDATE_INTERVAL/60000.0;	//angular displacement in fraction in one update_interval
 private double dis = 0;
 //=============================================================== fields
 private Calendar _now = Calendar.getInstance();  // Current time.
 
 private int _diameter;                 // Height and width of clock face
 private int _centerX;                  // x coord of middle of clock
 private int _centerY;                  // y coord of middle of clock
 private BufferedImage _clockImage;     // Saved image of the clock face.
 
 private javax.swing.Timer _timer;      // Fires to update clock.
 
private int nAzimuth = 0;
private int nAzimuthLast = 0;
private ArrayList[][] aryPlots = new ArrayList[5][360];
//private ArrayList[] aryPlots0 = new ArrayList[360];
 
 //==================================================== Clock constructor
 public Clock() {
     setPreferredSize(new Dimension(300,300));
     
     for(int i=0; i<5; i++)
     {
    	 for(int j=0; j<360; j++)
    	 {
    		 aryPlots[i][j] = new ArrayList();
    	 }
     }
     
     for(int i=0; i<36; i++)
     {
    	 Integer it = new Integer(100);//i*10 + 10);
 //   	 System.out.println(it);
    	 aryPlots[0][i*10].add(it);
     }
 
     _timer = new javax.swing.Timer(UPDATE_INTERVAL, new ActionListener() {
         public void actionPerformed(ActionEvent e) {
        	 updateTime();
             repaint();
         }
     });
 }
 
 //================================================================ start
 /** Start the timer. */
 public void start() {
     _timer.start(); 
 }
 
 //================================================================= stop
 /** Stop the timer. */
 public void stop() {
     _timer.stop(); 
 }
 
 //=========================================================== updateTime
 private void updateTime() {
     //... Avoid creating new objects.
     _now.setTimeInMillis(System.currentTimeMillis());
 }
 
 //======================================================= paintComponent
 @Override public void paintComponent(Graphics g) {
     Graphics2D g2 = (Graphics2D)g;
     g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
                         RenderingHints.VALUE_ANTIALIAS_ON);
     
     //... The panel may have been resized, get current dimensions
     int w = getWidth();
     int h = getHeight();
     _diameter = ((w < h) ? w : h);
     _centerX = _diameter / 2;
     _centerY = _diameter / 2;
     
     //... Create the clock face background image if this is the first time,
     //    or if the size of the panel has changed
     if (_clockImage == null
             || _clockImage.getWidth() != w
             || _clockImage.getHeight() != h) {
         _clockImage = (BufferedImage)(this.createImage(w, h));
         
         //... Get a graphics context from this image
         Graphics2D g2a = _clockImage.createGraphics();
         g2a.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
                              RenderingHints.VALUE_ANTIALIAS_ON);
         drawClockFace(g2a);
     }
     
     //... Draw the clock face from the precomputed image
     g2.drawImage(_clockImage, null, 0, 0);
     
     //... Draw the clock hands dynamically each time.
 //    drawClockHands(g2);
     drawSweep(g2);
 }
 
 //====================================== convenience method drawClockHands
 private void drawClockHands(Graphics2D g2) {
     //... Get the various time elements from the Calendar object.
     int hours   = _now.get(Calendar.HOUR);
     int minutes = _now.get(Calendar.MINUTE);
     int seconds = _now.get(Calendar.SECOND);
     int millis  = _now.get(Calendar.MILLISECOND);
     
     //... second hand
     int handMin = _diameter / 8;    // Second hand doesn't start in middle.
     int handMax = _diameter / 2;    // Second hand extends to outer rim.
     double fseconds = (seconds + (double)millis/1000) / 60.0;
//     double fseconds = (RPM * UPDATE_INTERVAL)/60000.0;
//     dis = fseconds * interval;
     dis = RPM*fseconds - (int)(RPM*fseconds);
     drawRadius(g2, dis, 0, handMax);
     
     
     //... minute hand
     handMin = 0;                    // Minute hand starts in middle.
     handMax = _diameter / 3; 
     double fminutes = (minutes + fseconds) / 60.0;
     drawRadius(g2, fminutes, 0, handMax);
     
     //... hour hand
     handMin = 0;
     handMax = _diameter / 4;
     drawRadius(g2, (hours + fminutes) / 12.0, 0, handMax);
 }
 
 //======================================= convenience method drawClockFace
 private void drawClockFace(Graphics2D g2) {
     // ... Draw the clock face.  Probably into a buffer.        
     g2.setColor(Color.black);
     g2.fillOval(0, 0, _diameter, _diameter);
     g2.setColor(Color.BLACK);
     g2.drawOval(0, 0, _diameter, _diameter);
     
     int radius = _diameter / 2;
     
     //... Draw the tick marks around the circumference.
     for (int sec = 0; sec < 60; sec++) {
         int tickStart;
         if (sec%5 == 0) {
             tickStart = radius - 10;  // Draw long tick mark every 5.
         } else {
             tickStart = radius - 5;   // Short tick mark.
         }
         drawRadius(g2, sec / 60.0, tickStart , radius);
     }
 }
 
 //==================================== convenience method drawRadius
 // This draw lines along a radius from the clock face center.
 // By changing the parameters, it can be used to draw tick marks,
 // as well as the hands.
 private void drawRadius(Graphics2D g2, double percent,
                         int minRadius, int maxRadius) {
     //... percent parameter is the fraction (0.0 - 1.0) of the way
     //    clockwise from 12.   Because the Graphics2D methods use radians
     //    counterclockwise from 3, a little conversion is necessary.
     //    It took a little experimentation to get this right.
     double radians = (0.5 - percent) * TWO_PI;
     double sine   = Math.sin(radians);
     double cosine = Math.cos(radians);
     
     int dxmin = _centerX + (int)(minRadius * sine);
     int dymin = _centerY + (int)(minRadius * cosine);
     
     int dxmax = _centerX + (int)(maxRadius * sine);
     int dymax = _centerY + (int)(maxRadius * cosine);
     g2.drawLine(dxmin, dymin, dxmax, dymax);
 }
 
 private void drawSweep(Graphics2D g2)
 {
	 _now.setTimeInMillis(System.currentTimeMillis());
     int seconds = _now.get(Calendar.SECOND);
     int millis  = _now.get(Calendar.MILLISECOND);
     double fseconds = seconds + (double)millis/1000;
     double ds = RPM*fseconds/60.0;
     double radians = (0.5 - ds) * 2*Math.PI;
     nAzimuthLast = nAzimuth;
     nAzimuth = (int)(180 - radians*360/2/Math.PI);
     while(nAzimuth>=360) 	nAzimuth -= 360;
	 while(nAzimuth <0) 	nAzimuth += 360;
//	 System.out.println("Az=" + nAzimuth + " Last Az=" + nAzimuthLast);
     if(nAzimuth-nAzimuthLast > 10)
    	 return;
	 
	 
     int w = getWidth();
     int h = getHeight();
     int dia = ((w < h) ? w : h);
     int[] x = new int[5];
     int[] y = new int[5];
     x[0] = dia/2;
     y[0] = dia/2;
     
     for(int i=1; i<5; i++)
     {
    	 x[i] = (int)(x[0] + x[0] * Math.sin(radians+(i-1)*0.1));
    	 y[i] = (int)(y[0] + y[0] * Math.cos(radians+(i-1)*0.1));
     }
     g2.setColor(Color.blue);
     g2.drawLine(x[0], y[0], x[1], y[1]);
     
     float alpha = 0.25f;
     int type = AlphaComposite.SRC_OVER; 
     AlphaComposite composite = AlphaComposite.getInstance(type, alpha);
     g2.setComposite(composite);
     g2.fillPolygon(x, y, 5);
     
     
     //draw Blips on every sweep moves
     //remove blips on every sweep moves
     if(nAzimuth == nAzimuthLast) return;
//	 System.out.println("Az=" + nAzimuth + " Last Az=" + nAzimuthLast);
     draw(g2, nAzimuthLast+1,	nAzimuth, 		255, aryPlots[0], aryPlots[1]);
     draw(g2, nAzimuthLast-30,  nAzimuth-30,	230, aryPlots[1], aryPlots[2]);
     draw(g2, nAzimuthLast-90,	nAzimuth-90,	200, aryPlots[2], aryPlots[3]);
     draw(g2, nAzimuthLast-210, nAzimuth-210,	100, aryPlots[3], aryPlots[4]);
     draw(g2, nAzimuthLast-350, nAzimuth-350,	50,  aryPlots[4], aryPlots[0]);
     
 }
 
 private void draw(Graphics2D g2, int nAzimuthFrom, int nAzimuthTo, int color, ArrayList[] aryFrom, ArrayList[] aryTo)
 {
	 while(nAzimuthFrom<0) 		nAzimuthFrom += 360;
     while(nAzimuthFrom>=360) 	nAzimuthFrom -= 360;
	 while(nAzimuthTo  <0) 		nAzimuthTo   += 360;
     while(nAzimuthTo  >=360) 	nAzimuthTo   -= 360;
     if(nAzimuth-nAzimuthLast > 10)
    	 return;
	 
	 if(nAzimuthFrom > nAzimuthTo)
	 {
		 draw(g2, nAzimuthFrom, 359, color, aryFrom, aryTo);
		 draw(g2, 0, nAzimuthTo, color, aryFrom, aryTo);
	 }
	 
//	 System.out.println("From Az=" + nAzimuthFrom + " To Az=" + nAzimuthTo);
	 for(int i=nAzimuthFrom; i<=nAzimuthTo; i++)
	 {
		 //iterate a loop thru aryFrom[i] list
		 Iterator itr = aryFrom[i].iterator();
		 while(itr.hasNext())
		 {
		 	//draw blip
			 Integer it = (Integer)itr.next();
			 draw(g2, color, it.intValue(), i);
		 	if(aryTo != null)
		 	{
		 	  //add it to aryTo[i] list
		 		aryTo[i].add(it);
		 	}
		 }
		 //once loop is over, clear aryFrom[i]
		 aryFrom[i].clear();
		 
	 }
	 
 	
 }
 
private void draw(Graphics2D g2, int color, int rng, int brg)
{
//	System.out.println("Rng=" + rng + " Brg=" + brg);
	double rad = (180-brg)*2*Math.PI/360.0;

	int x = (int)(_centerX + rng * Math.sin(rad));
	int y = (int)(_centerY + rng * Math.cos(rad));
	
    Graphics2D g2a = _clockImage.createGraphics();
    g2a.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
                         RenderingHints.VALUE_ANTIALIAS_ON);
	g2a.setColor(new Color(0,0,color));
	g2a.fillOval(x, y, 10, 10);
}
}
