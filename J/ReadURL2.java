package test;
//http://java.sun.com/features/2002/11/hilevel_network.html

//usage
//C:\Documents and Settings\ChohanS.INFLITE\My Documents\JBuilder2007\Test\bin>"C:\Program Files\Java\
//jre1.6.0_05\bin\java" ReadURL2 "http://openatc.com/ge.asp/"

import java.net.*;
import java.io.*;
import java.nio.CharBuffer;

public class ReadURL2 {
   public static void main(String argv[]) throws Exception {
      if(argv.length != 1) {
         System.out.println("Usage: java ReadURL2 <url>");
         System.exit(0);
      }
      
      System.setProperty("http.proxyHost", "StanISA01");
      System.setProperty("http.proxyPort", "8080");
      //http.nonProxyHosts (default: <none>)
     
      URL url = new URL(argv[0]);
      System.out.println("URL object created");
      
      BufferedReader in = new BufferedReader(new InputStreamReader(url.openStream()));

      String line;
      StringBuffer sb = new StringBuffer();
      System.out.println("going into read loop");
      while ((line = in.readLine()) != null) {
         sb.append(line);
      }
      in.close();
      System.out.println(sb.toString());
      
//      char cb[] = new char[100000];//new CharBuffer();
//      while (in.read(cb) > 0) {
//   	     System.out.print(cb);    	  
//       }
//      in.close();

   }
}
