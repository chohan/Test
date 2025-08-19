package test;
//this is an http client applicaton 
// it uses URLConnection class

// http://www.devdaily.com/java/edu/pj/pj010023/

//http://java.sun.com/features/2002/11/hilevel_network.html

//usage
//C:\Documents and Settings\ChohanS.INFLITE\My Documents\JBuilder2007\Test\bin>"C:\Program Files\Java\
//jre1.6.0_05\bin\java" ReadURL2 "http://openatc.com/ge.asp/"

import java.net.*;
import java.io.*;

public class ReadURL3 
{
	public static void main(String argv[]) throws Exception
	{
		if(argv.length != 1)
		{
			System.out.println("Usage: java ReadURL3 <url>");	//http://old.fysb.de/acarsdserver.main
			System.exit(0);
		}
		
		//input parameters
		String sURL = argv[0];
    
		//proxy settings
		System.setProperty("http.proxyHost", "StanISA01");
		System.setProperty("http.proxyPort", "8080");
		//http.nonProxyHosts (default: <none>)
   
		//connecting server
		URL url = new URL(sURL);
		URLConnection con = url.openConnection();
		
		// in/out sreams
		BufferedReader in = new BufferedReader(new InputStreamReader(con.getInputStream()));

		//reading loop
		String line;
		StringBuffer sb = new StringBuffer();
		while ((line = in.readLine()) != null)
		{
			sb.append(line);
//			System.out.println(line);
		}
		in.close();
//		System.out.println(sb.toString());
		BufferedWriter file = new BufferedWriter(new FileWriter("debug.txt"));
		file.write(sb.toString());
    
//    char cb[] = new char[100000];//new CharBuffer();
//    while (in.read(cb) > 0) {
// 	     System.out.print(cb);    	  
//     }
//    in.close();

 }
}
