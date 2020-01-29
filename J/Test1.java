package test;

import java.io.DataOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.FileSystems;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.WatchEvent;
import java.nio.file.WatchEvent.Kind;
import java.nio.file.WatchKey;
import java.nio.file.WatchService;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Formatter;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;
import java.util.Vector;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.Future;
import java.util.concurrent.RecursiveAction;

import static java.nio.file.StandardWatchEventKinds.*;

//public abstract interface Test {
public final class Test implements Cloneable {

public static void main(String[] args) {
	
	Test test = new Test();
}

public Test() {
	
	Vector<String> vstr = new Vector<>();
	vstr.add("sdfas");
	Vector<Integer> v2 = new Vector<>();
	v2.add(3);
	
	
	Class clss = java.lang.Integer.class;
	System.out.println(clss.getMethods()[0].getName());
	System.out.println(clss.getMethods()[1].getName());
	System.out.println(this.toString());
	System.out.println(this instanceof Object);
	System.out.println(this.getClass());
	System.out.println("No of Processors=" + Runtime.getRuntime().availableProcessors());
	
	// cloning
	try {
		Test test2 = (Test) this.clone();
	} catch (CloneNotSupportedException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
	
	// copy constructor
	//Test test3 = new Test(this);
	
	java7NewFeatures();
	
	int[][] apartment = new int[5][4];
	
	
	
	// equal() default
//	String s1 = "asdf";
//	String s2 = "asdf";
	java.util.TreeMap<String, Integer> treeMap = new java.util.TreeMap<String, Integer>();
	TreeMap<String, Integer> s1 = treeMap;
	TreeMap<String, Integer> s2 = treeMap;
	if(s1.equals(s2)){
		System.out.println("s1 and s2 are equals");
	}
	else {
		System.out.println("s1 and s2 are NOT equals");
	}
	System.out.println("s1 hashCode=" + s1.hashCode() + ", s2 hasCode=" + s2.hashCode());
	
//	String s3 = new String("asdf");
//	String s4 = new String("asdf");
//	Integer s3 = new Integer(1234);
//	Integer s4 = new Integer(1234);
	TreeMap<String, Integer> s3 = new TreeMap<String, Integer>(treeMap);
	TreeMap<String, Integer> s4 = new TreeMap<String, Integer>(treeMap);
	if(s3.equals(s4)){
		System.out.println("s3 and s4 are equals");
	}
	else {
		System.out.println("s3 and s4 are NOT equals");
	}
	System.out.println("s3 hashCode=" + s3.hashCode() + ", s4 hasCode=" + s4.hashCode());
}

/**
 * 
 */
public void java7NewFeatures() {
	// java 7 new features
	Map<String, List<Test>> trades = new TreeMap <> ();
	
	//switch with string
	String status="s1";
	switch(status)
	{case "s1":
		;
		break;
	case "s2":
		;
		break;
	}
	
	// auto closing of resources
	try (FileOutputStream fos = new FileOutputStream("myfile.txt");
			DataOutputStream dos = new DataOutputStream(fos);)
	{
		dos.writeUTF("Java version 7, new features");
	}catch(IOException e){e.printStackTrace();}
	
	// numbers with visibility
	int million = 1000_000;
	int billion = 1_000_000_000;
	
	// NIO 2
    Path path = Paths.get("D:/Projects/TimeNAttendence/log/AttendanceFeeder_20140126.log");
    System.out.println("Number of Nodes:" + path.getNameCount());
    System.out.println("File Name:" + path.getFileName());
    System.out.println("File Root:" + path.getRoot());
    System.out.println("File Parent:" + path.getParent());
    
    // File change notification
    WatchService  watchService = null;
    WatchKey key = null;
    try {
		watchService = FileSystems.getDefault().newWatchService();
		Path path1 = Paths.get("D:/Projects/TimeNAttendence/sms");
		path1.register(watchService, ENTRY_CREATE, ENTRY_MODIFY, ENTRY_DELETE);
	} catch (IOException e) {e.printStackTrace();}
//    while(true)
//    {
//    	try {
//	    		key = watchService.take();
//	    		for (WatchEvent<?> event : key.pollEvents()) {
//	    			Kind<?> kind = event.kind();
//	    			System.out.println("Event on " + event.context().toString() + " is " + kind);
//	    		}
//
//    	} catch (InterruptedException e) {System.out.println("InterruptedException: "+e.getMessage());}
//
//    	boolean reset = key.reset();
//
//    	if(!reset)
//    		break;
//    }
    
    // Fork and Join
    class MyTask extends RecursiveAction{
    	public void compute(){
    		for(int i=0; i<5; i++){
    			System.out.println("I am from Recursive action");}
    			try {
					Thread.sleep(3000);
				} catch (InterruptedException e) {e.printStackTrace();				}
    		}
    }
    final ForkJoinPool pool = new ForkJoinPool (Runtime.getRuntime().availableProcessors());
    pool.invoke(new MyTask());
 
//    ForkJoinPool pool2 = new ForkJoinPool (Runtime.getRuntime().availableProcessors());
//    pool = pool2;
}

public Test clone () throws CloneNotSupportedException {
	
	Test newObject = (Test)super.clone();
	return newObject; 
}

}

class Base {
	public void Func() throws java.io.FileNotFoundException{}
}

class Derived extends Base {
//	public void Func() throws ClassNotFoundException{}
}
