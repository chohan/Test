package test;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;

public class FileReaderWriter {

public FileReaderWriter() {
	// TODO Auto-generated constructor stub
}

/**
 * DataInputStream (byte oriented)
 */
public static void method1() {

    File file = new File("C:\\MyFile.txt");
    FileInputStream fis = null;
    BufferedInputStream bis = null;
    DataInputStream dis = null;

    try {
      fis = new FileInputStream(file);
      bis = new BufferedInputStream(fis);// Here BufferedInputStream is added for fast reading.
      dis = new DataInputStream(bis);

      // dis.available() returns 0 if the file does not have more lines.
      while (dis.available() != 0) {

      // this statement reads the line from the file and print it to
        // the console.
        System.out.println(dis.readLine());
      }

      // dispose all the resources after using them.
      fis.close();
      bis.close();
      dis.close();

    } catch (FileNotFoundException e) {
      e.printStackTrace();
    } catch (IOException e) {
      e.printStackTrace();
    }
}

/**
 * BufferedReader (character oriented)
 * good for reading huge files. using less resources
 */
public static void method2()
{
	try{
	// Open the file that is the first 
	// command line parameter
	FileInputStream fstream = new FileInputStream("textfile.txt");
	// Get the object of DataInputStream
	DataInputStream in = new DataInputStream(fstream);
	BufferedReader br = new BufferedReader(new InputStreamReader(in));
	String strLine;
	//Read File Line By Line
	while ((strLine = br.readLine()) != null)   {
	// Print the content on the console
	System.out.println (strLine);
	}
	//Close the input stream
	in.close();
	  }catch (Exception e){//Catch exception if any
	System.err.println("Error: " + e.getMessage());
	}
}

/**
 * good to read small files
 */
public static void method3()
{
	java.nio.file.Path path = java.nio.file.FileSystems.getDefault().getPath("C:/", "Mytextfile.txt");
	byte[] byteArray = null;
	try {
		byteArray = Files.readAllBytes(path);
	} catch (IOException e) {e.printStackTrace();}

	try {
		Files.write(path, byteArray);
	} catch (IOException e) {e.printStackTrace();}

}

/**
 * using new IO to read big files using buffer
 */
public static void method4()
{
	java.nio.file.Path path = java.nio.file.FileSystems.getDefault().getPath("C:/", "Mytextfile.txt");
	String encoding = System.getProperty("file.encoding");
	java.nio.charset.Charset charset = java.nio.charset.Charset.forName(encoding);//"US-ASCII");
	
	// reading
	try (BufferedReader reader = java.nio.file.Files.newBufferedReader(path, charset)) {
	    String line = null;
	    while ((line = reader.readLine()) != null) {
	        System.out.println(line);
	    }
	} catch (IOException x) {
	    System.err.format("IOException: %s%n", x);
	}	
	
	// writing
	String s = "data to be written";
	try (BufferedWriter writer = Files.newBufferedWriter(path, charset)) {
	    writer.write(s, 0, s.length());
	} catch (IOException x) {
	    System.err.format("IOException: %s%n", x);
	}	
	
}

public static void method5()
{
	java.nio.file.Path path = java.nio.file.FileSystems.getDefault().getPath("C:/", "Mytextfile.txt");
	
	// reading
	try (InputStream in = Files.newInputStream(path);
	    BufferedReader reader = new BufferedReader(new InputStreamReader(in))) {
	    String line = null;
	    while ((line = reader.readLine()) != null) {
	        System.out.println(line);
	    }
	} catch (IOException x) {
	    System.err.println(x);
	}	
	
	// writing
	try (OutputStream os = Files.newOutputStream(path);
	    BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(os))) {
	    String line = "data to be written";
	    writer.write(line);
	} catch (IOException x) {
	    System.err.println(x);
	}	
	
	// Convert the string to a
	// byte array.
	String s = "data to be written";
	byte data[] = s.getBytes();
	//import static java.nio.file.StandardOpenOption.*;
	try (OutputStream out = new BufferedOutputStream(Files.newOutputStream(path, java.nio.file.StandardOpenOption.CREATE, java.nio.file.StandardOpenOption.APPEND))) {

	    out.write(data, 0, data.length);
	} catch (IOException x) {
	    System.err.println(x);
	}	
	
}


}
