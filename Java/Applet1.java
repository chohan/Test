package Client;

import java.awt.*;
import java.awt.event.*;
import java.applet.*;
import javax.swing.*;

public class Applet1 extends Applet
{
  boolean isStandalone = false;
  String var1;
  int var2;
  float var3;

//Construct the applet
public Applet1()
{
}

//Initialize the applet
public void init()
{
  try
  {
    jbInit();
  }
  catch(Exception e)
  {
    e.printStackTrace();
  }
  try { var1 = this.getParameter("Name1", ""); } catch (Exception e) { e.printStackTrace(); }
  try { var2 = Integer.parseInt(this.getParameter("Name2", "0")); } catch (Exception e) { e.printStackTrace(); }
  try { var3 = Float.valueOf(this.getParameter("Name3", "0")).floatValue(); } catch (Exception e) { e.printStackTrace(); }
  try  {
  }
  catch(Exception e)  {
    e.printStackTrace();
  }
}

//Component initialization
private void jbInit() throws Exception
{
  this.setSize(new Dimension(400,300));
}

//Start the applet
public void start()
{
}

//Stop the applet
public void stop()
{
}

//Destroy the applet
public void destroy()
{
}

//Get Applet information
public String getAppletInfo()
{
  return "Applet Information";
}

//Get parameter info
public String[][] getParameterInfo()
{
  return null;
}

//Get a parameter value
public String getParameter(String key, String def)
{
    return isStandalone ? System.getProperty(key, def) :
      (getParameter(key) != null ? getParameter(key) : def);
}

//Main method
public static void main(String[] args)
{
  Applet1 applet = new Applet1();
  applet.isStandalone = true;
  JFrame frame = new JFrame();
  frame.setTitle("Applet Frame");
  frame.getContentPane().add(applet, BorderLayout.CENTER);
  applet.init();
  applet.start();
  frame.setSize(400,320);
  Dimension d = Toolkit.getDefaultToolkit().getScreenSize();
  frame.setLocation((d.width - frame.getSize().width) / 2, (d.height - frame.getSize().height) / 2);
  frame.setVisible(true);
}
// static initializer for setting look & feel
static {
  try
  {
    UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
    //UIManager.setLookAndFeel(UIManager.getCrossPlatformLookAndFeelClassName());
  }
  catch (Exception e) {}
}

}