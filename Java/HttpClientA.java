package test;

import org.apache.commons.httpclient.HttpClient;
import org.apache.commons.httpclient.HttpStatus;
import org.apache.commons.httpclient.methods.*;
import org.apache.commons.httpclient.ConnectMethod;


import java.io.BufferedReader;
import java.io.InputStreamReader;


public class HttpClientA {


	  public static void main(String args[]) {

	    HttpClient client = new HttpClient();
	    client.getParams().setParameter("http.useragent", "Test Client");

	    BufferedReader br = null;

//	    PostMethod method = new PostMethod("http://search.yahoo.com/search");
//	    method.addParameter("p", "\"java2s\"");
	    GetMethod method = new GetMethod(args[0]);
//	    ConnectMethod con = new ConnectMethod();
	    

	    try{
	    System.out.println("Executing method");
	      int returnCode = client.executeMethod(method);

//	      if(returnCode == HttpStatus.SC_NOT_IMPLEMENTED)
	      if(returnCode == HttpStatus.SC_OK)
	      {
	        System.err.println("The Post method is not implemented by this URI");
	        // still consume the response body
	        method.getResponseBodyAsString();
	      } else 
	      {
	    	  System.out.println("Reading from web server\n\n\n");
	    	  br = new BufferedReader(new InputStreamReader(method.getResponseBodyAsStream()));
	    	  String readLine;
	    	  while(((readLine = br.readLine()) != null))
	    	  {
	    		  System.err.println(readLine);
	    	  }
	      }
	    } catch (Exception e) {
	      System.err.println(e);
	    } finally {
	      method.releaseConnection();
	      if(br != null) try { br.close(); } catch (Exception fe) {}
	    }

	  }
}
