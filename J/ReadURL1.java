package test;
//this client application simply connects to a server on specified port
//http://java.sun.com/features/2002/11/hilevel_network.html

//usage
//C:\Documents and Settings\ChohanS.INFLITE\My Documents\JBuilder2007\Test\bin>"C:\Program Files\Java\
//jre1.6.0_05\bin\java" ReadURL1 "www.apache.org/"

import java.net.*;
import java.io.*;

public class ReadURL1 {

	   public static void main(String argv[]) throws Exception
	   {

		   if(argv.length != 2)
		   {
			   System.out.println("Usage: java ReadURL1 <url> <port>");
			   System.exit(0);
		   }

		   //input parameters
		   String sServer= argv[0];
		   String sPort	= argv[1];
		   int nPort = Integer.valueOf(sPort).intValue();

		   //proxy settings
		   //System.setProperty("http.proxyHost", "StanISA01");
		   //System.setProperty("http.proxyPort", "8080");
		   //http.nonProxyHosts (default: <none>)
		   //System.setProperty("socksProxyHost", "StanISA01");
		   //System.setProperty("socksProxyHost", "8080");

		   //socket creation
		   System.out.println("socket creating with " + sServer + " on " + nPort);
		   Socket socket = new Socket(sServer, nPort);
		   System.out.println("socket created with " + sServer + " on " + nPort);
		      
		   // in/out sreams 
		   BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
//		   BufferedWriter out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
//	   	   out.write("GET /index.html HTTP/1.0\n\n");
//		   out.write("GET /acarsdserver.main HTTP/1.0\n\n");
//	       out.flush();

		   //reading loop
		   String line;
		   StringBuffer sb = new StringBuffer();
		   while((line = in.readLine()) != null)
		   {
			   System.out.println(line);
//		   	  sb.append(line);
		   }
//		   out.close();
		   in.close();
		   System.out.println(sb.toString());
	   }
	
}
