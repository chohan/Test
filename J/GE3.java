package test;

//import earth.idl;
import java.io.*;
import java.lang.reflect.*;
import java.awt.event.*;
import java.awt.Component;
import javax.swing.JFrame;

import org.jawin.*;
import org.jawin.constants.*;
import org.jawin.donated.*;
import org.jawin.donated.win32.*;
import org.jawin.donated.win32.io.*;
import org.jawin.donated.win32.User32;
import org.jawin.event.*;
import org.jawin.io.*;
import org.jawin.marshal.*;
import org.jawin.tools.*;
import org.jawin.util.*;
import org.jawin.win32.*;


public class GE3 extends javax.swing.JFrame implements MouseWheelListener, MouseListener {
	
	protected String title = "GE2";
	protected DispatchPtr applicationGE;
    protected Component geComp;
	
	public static void main(String[] args)
	{
		new GE3();
	}
	
    public void init()
    {
        new GE2();
    }
	
	public GE3()
	{
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setTitle("GE3");
        pack();                          // Layout components
        setLocationRelativeTo(null);     // Center window.
        setVisible(true);
        setSize(1000, 800);
        //Start Google Earth
        try{
        	applicationGE = new DispatchPtr("GoogleEarth.ApplicationGE");

                System.out.println("Initializing Google Earth ");
//                while(applicationGE.IsInitialized() <= 0){
//                        Thread.currentThread().sleep(350);
//                        System.out.print(".");
//                }
//                System.out.println("\nGoogle Earth Initialized.\n");
//               Thread.currentThread().sleep(5000);
        }
        catch (org.jawin.COMException e){e.printStackTrace();}
        catch (Exception e){e.printStackTrace();}

        attachRenderHwnd();
        geComp = this.getFocusOwner();
        System.out.println("GE component=" + geComp);
      
//        this.addMouseWheelListener(this);
//        this.addMouseListener(this);
        this.addWindowListener(new WinAdapter());
        this.addComponentListener(new CompAdapter());
	}
	
    public void mouseWheelMoved(MouseWheelEvent e){System.out.println("mouseWeelMoved");}	
    public void mouseClicked(MouseEvent e){System.out.println("mouseClicked");}	
    public void mousePressed(MouseEvent e){System.out.println("mousePressed");}	
    public void mouseReleased(MouseEvent e){System.out.println("mouseReleased");}
    public void mouseEntered(MouseEvent e){System.out.println("mouseEntered");}
    public void mouseExited(MouseEvent e){System.out.println("mouseExited");}

	public int getGEMainHwnd()
	{
        int mainHwnd = 0;
        try {
                mainHwnd = (Integer) applicationGE.invoke("GetMainHwnd");
        } catch (COMException e) {
                e.printStackTrace();
        }
        return mainHwnd;
	}
	
	public int getGERenderHwnd()
	{
        int renderHwnd = 0;
        try {
           renderHwnd = (Integer) applicationGE.invoke("GetRenderHwnd");
        } catch (org.jawin.COMException e) {e.printStackTrace();}
        return renderHwnd;
	}


//	where "title" is the is the string of your Java app window. That's the
//	window you'll have GE rendering.
//	There you can see one of the tricky operation : you have to call a
//	Windows library. More info on this on Jawin main page

    private int getGUIHwnd()
    {
        int hwnd = 0;
        System.loadLibrary("jawt");
        sun.awt.windows.WToolkit tk = (sun.awt.windows.WToolkit)this.getToolkit();
        System.out.println("tk: "+tk);

        System.out.println("windows visibility " + this.isVisible());
//        java.awt.Window w = javax.swing.SwingUtilities.getWindowAncestor(this);
//        System.out.println("windows=" + w);
        
        Object peer = tk.targetToPeer(this);
        System.out.println("peer: "+peer);

        try {
                Class c = peer.getClass();
                System.out.println("class: "+c);

                java.lang.reflect.Field f = getDeclaredField(c, "hwnd");
                System.out.println("Field: "+f);

                f.setAccessible(true);
                Object result = f.get(peer);
                hwnd = ((Long) result).intValue();

        } catch (Throwable t) {throw new RuntimeException(t.toString());}
        return hwnd;
    }
    
    public final static Field getDeclaredField(Class clazz, String fieldName) throws NoSuchFieldException
    {
		Class c = clazz;
		while (c != null && c != Object.class)
		{
			try {
			Field fld = c.getDeclaredField(fieldName);
			System.out.println("GUI class=" + c.getName());
			return fld;
			} catch (NoSuchFieldException e) {}
			c = c.getSuperclass();
		}
		throw new NoSuchFieldException(fieldName);
	}
    
//	** To attach GE redering to you Java app :

    private void attachRenderHwnd()
    {
        //hide GE main window
//        try {
//        	org.jawin.donated.win32.User32.ShowWindow(getGEMainHwnd(), 0); //hide GE main window
//        } catch (COMException e) {e.printStackTrace();}
//          catch (IOException e) {e.printStackTrace();}

        resizeGERenderHwnd();

        //attach GE render window to the GUI
        try {
                org.jawin.FuncPtr setParent = new FuncPtr("USER32.DLL", "SetParent");
                setParent.invoke_I(getGEMainHwnd(), this.getGUIHwnd(), ReturnFlags.CHECK_FALSE);
        } catch (COMException e) { e.printStackTrace(); }

    }

//	geGERenderHwnd : the hwnd you got earlier (the "child" hwnd)
//	this.getGUIHwnd() : you java app hwnd (the new "parent" hwnd)

//	** the rendering resizing method :

    private void resizeGERenderHwnd()
    {
    try {
    		org.jawin.FuncPtr moveWindow = new FuncPtr("USER32.DLL", "MoveWindow");
    		
            // create a NakedByteStream for the serialization of Java variables
            org.jawin.io.NakedByteStream nbs = new NakedByteStream();
            
            // wrap it in a LittleEndianOutputStream
            org.jawin.io.LittleEndianOutputStream leos = new LittleEndianOutputStream(nbs);
            
            // and then write the Java arguments
            leos.writeInt(getGERenderHwnd());	//Handle to the window
            leos.writeInt(0);		//Specifies the new position of the left side of the window
            leos.writeInt(0);	//Specifies the new position of the top of the window
//	        	leos.writeInt((int) jContentPane.getSize().getWidth());         //Specifies the new width of the window
//	            leos.writeInt((int) jContentPane.getSize().getHeight());        //Specifies the new height of the window
            leos.writeInt((int) this.getWidth());         //Specifies the new width of the window
            leos.writeInt((int) this.getHeight());        //Specifies the new height of the window
            leos.writeBoolean(false);       //Specifies whether the window is to be repainted
            moveWindow.invoke("IIIII:I:", 24, nbs, null, ReturnFlags.CHECK_FALSE);
        } catch (IOException e) {e.printStackTrace();}
          catch (COMException e) {e.printStackTrace();}
     }

//	it gets a little more tricky has you have to use a generic invoke method

//	** at last, a method to quit GE (you'll have to invoke this method
//	when you're closing your Java app :

    private void quitGE()
    {
    try {
    		org.jawin.FuncPtr endTask = new FuncPtr("USER32.DLL", "EndTask");
    		
            //create a NakedByteStream for the serialization of Java variables
    		org.jawin.io.NakedByteStream nbs = new NakedByteStream();
    		
            // wrap it in a LittleEndianOutputStream
            org.jawin.io.LittleEndianOutputStream leos = new LittleEndianOutputStream(nbs);
            
            // and then write the Java arguments
            leos.writeInt(getGERenderHwnd());      //Handle to the window to be closed.
            leos.writeInt(0);                       //Ignored. Must be FALSE.
            leos.writeInt(0);                       //A TRUE for this parameter will force the
//destruction of the window if an initial attempt fails to gently close
//the window using WM_CLOSE. With a FALSE for this parameter, only the
//close with WM_CLOSE is attempted.
            endTask.invoke("III:I:", 12, nbs, null, ReturnFlags.CHECK_FALSE);
    } 	catch (COMException e) {e.printStackTrace();}
    	catch (IOException e) {e.printStackTrace();}
    }
    
    private void setGE()
    {
/*    try {
    		org.jawin.FuncPtr setGE = new FuncPtr("USER32.DLL", "SendMessageW_I");
    		org.jawin.io.NakedByteStream nbs = new NakedByteStream();
            org.jawin.io.LittleEndianOutputStream leos = new LittleEndianOutputStream(nbs);
            leos.writeInt(getGERenderHwnd());      //Handle to the window to be closed.
            leos.writeInt((int) 0x128);	//WM_UPDAGEUISTATE=0x128
            leos.writeInt((int) 0x00040001);	//wParam high order = UISF_HIDEFOCUS=0x1, UISF_HIDEACCEL=0x2,UISF_ACTIVE=0x4
            									//wParam low order  = UIS_SET=1, UIS_CLEAR=2, UIS_INITIALIZE=3
            leos.writeInt(0);			//lParam = 0
            setGE.invoke("III:I:", 12, nbs, null, ReturnFlags.CHECK_FALSE);            
            
    } 	catch (COMException e) {e.printStackTrace();}
    	catch (IOException e) {e.printStackTrace();}
   */
        try {
        	org.jawin.donated.win32.User32.UpdateWindow(getGERenderHwnd()); //
        } catch (COMException e) {e.printStackTrace();}
          catch (IOException e) {e.printStackTrace();}
    }

    private void setCaptureGE()
    {
    try {
    		org.jawin.FuncPtr setCapture = new FuncPtr("USER32.DLL", "SetCapture");
            setCapture.invoke_I(getGERenderHwnd(), ReturnFlags.CHECK_NONE);
//            applicationGE.invoke("SetCapture");
    } 	catch (COMException e) {e.printStackTrace();}

    }

    
    
    class WinAdapter extends WindowAdapter
    {
        public void windowClosing(WindowEvent event)
        {
            setVisible( false );
            quitGE();
//            try {
//            	org.jawin.donated.win32.User32.PostQuitMessage(getGERenderHwnd());
//            } catch (COMException e) {e.printStackTrace();}
//              catch (IOException e) {e.printStackTrace();}            
            dispose(); 
            System.exit(0);
        }	
    }
    class CompAdapter extends ComponentAdapter
    {
    	public void componentResized(ComponentEvent e)
    	{
    		resizeGERenderHwnd();
//    		setGE();
    	}
    	public void componentMoved(ComponentEvent e)
    	{
//    		resizeGERenderHwnd();
    		setGE();
    	}
    }
}
