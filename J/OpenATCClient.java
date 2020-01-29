package test;


import org.apache.commons.httpclient.HttpClient;
import org.apache.commons.httpclient.methods.GetMethod;


public class OpenATCClient {

	 public static void main(String args[]) throws Exception {
	      HttpClient client = new HttpClient();
	      GetMethod method = new GetMethod("http://www.google.com");
	      int returnCode = client.executeMethod(method);
	      System.err.println(method.getResponseBodyAsString());
	      method.releaseConnection();
	 }
}

/*
import java.net.*;
import java.io.*;

public class OpenATCClient {
   public static void main(String argv[]) throws Exception {
      if(argv.length != 1) {
         System.out.println("Usage: java ReadURL2 <url>");
         System.exit(0);
      }
      HTTPConnection con = new HTTPConnection("www.myaddr.net");
      URL url = new URL(argv[0]);
//      URLConnection con = url.openConnection();
      HttpURLConnection con = (HttpURLConnection) url.openConnection();
      con.connect();
      con.getContent();
      
 //     con.setDoOutput(true);
 //     PrintWriter out = new PrintWriter(con.getOutputStream());
 //     out.println("http://google.co.uk");
//      out.close();
      con.setRequestMethod("POST");
      con.setDoOutput(true);
      PrintWriter out = new PrintWriter(con.getOutputStream());
      // encode the message
//      String name = "name="+URLEncoder.encode("Qusay Mahmoud", "UTF-8");
//      String email = "email="+URLEncoder.encode("qmahmoud@javacourses.com", "UTF-8");
      // send the encoded message
//      out.println(name+"&"+email);
      out.close();

      
      BufferedReader in = new BufferedReader(new InputStreamReader(con.getInputStream()));
      BufferedReader in = new BufferedReader(new InputStreamReader(url.openStream()));

      String line;
      StringBuffer sb = new StringBuffer();
      while ((line = in.readLine()) != null) {
         sb.append(line);
      }
      in.close();
      System.out.println(sb.toString());

   }
}
*/