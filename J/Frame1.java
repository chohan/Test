
//Title:        Your Product Name
//Version:      
//Copyright:    Copyright (c) 1999
//Author:       Salahuddin
//Company:      
//Description:  Your description

package Client;

import java.awt.*;
import javax.swing.*;
import com.borland.jbcl.layout.*;

public class Frame1 extends JFrame
{
  JScrollPane jScrollPane1 = new JScrollPane();
  JButton jButton1 = new JButton();
  JButton jButton2 = new JButton();
  JPanel jPanel1 = new JPanel();
  JButton jButton3 = new JButton();
  JButton jButton4 = new JButton();
  JButton jButton5 = new JButton();
  JButton jButton7 = new JButton();
  JSlider jSlider1 = new JSlider();

  public Frame1()
  {
    try 
    {
      jbInit();
    }
    catch(Exception e)
    {
      e.printStackTrace();
    }
  }

  private void jbInit() throws Exception
  {
    jButton1.setPreferredSize(new Dimension(59, 27));
    jButton1.setText("jButton1");
    jButton2.setPreferredSize(new Dimension(59, 27));
    jButton2.setText("jButton2");
    jButton3.setPreferredSize(new Dimension(59, 27));
    jButton3.setText("jButton3");
    FlowLayout fl = new FlowLayout(FlowLayout.LEFT);
    jPanel1.setLayout(fl);
    jButton4.setPreferredSize(new Dimension(59, 27));
    jButton4.setText("jButton4");
    jButton5.setPreferredSize(new Dimension(59, 27));
    jButton5.setText("jButton5");
    this.getContentPane().setLayout(null);
    jPanel1.setBounds(new Rectangle(196, 10, 202, 232));
    jScrollPane1.setBounds(new Rectangle(0, 0, 4, 4));
    jButton7.setText("jButton7");
    jSlider1.setBounds(new Rectangle(65, 151, 234, 18));
    this.getContentPane().add(jPanel1, null);
    jPanel1.add(jButton1, null);
    jPanel1.add(jButton2, null);
    jPanel1.add(jButton3, null);
    jPanel1.add(jButton4, null);
    jPanel1.add(jButton5, null);
    this.getContentPane().add(jScrollPane1, null);
    this.getContentPane().add(jSlider1, null);
    jScrollPane1.getViewport().add(jButton7, null);
  }
}
