// This example is from _Java Examples in a Nutshell_. (http://www.oreilly.com)
// Copyright (c) 1997 by David Flanagan
// This example is provided WITHOUT ANY WARRANTY either expressed or implied.
// You may study, use, modify, and distribute it for non-commercial purposes.
// For any commercial use, see http://www.davidflanagan.com/javaexamples
package test;

import java.io.*;
import java.net.*;

/**
 * This program connects to a Web server and downloads the specified URL
 * from it.  It uses the HTTP protocol directly.
 **/
public class HttpClient {
  public static void main(String[] args) {
    try {
      // Check the arguments
      if ((args.length != 1) && (args.length != 2))
        throw new IllegalArgumentException("Wrong number of arguments");
      
      // Get an output stream to write the URL contents to
      OutputStream to_file;
      if (args.length == 2) to_file = new FileOutputStream(args[1]);
      else to_file = System.out;
      
      // Now use the URL class to parse the user-specified URL into
      // its various parts: protocol, host, port, filename.  Check the protocol
      URL url = new URL(args[0]);
      String protocol = url.getProtocol();
      if (!protocol.equals("http"))
        throw new IllegalArgumentException("URL must use 'http:' protocol");
      String host = url.getHost();
      int port = url.getPort();
      if (port == -1) port = 80;  // if no port, use the default HTTP port
      String filename = url.getFile();
      
      // Open a network socket connection to the specified host and port
      Socket socket = new Socket(host, port);
      System.out.println("socket opened with " + host + ":" + port);
      
      // Get input and output streams for the socket
      InputStream from_server = socket.getInputStream();
      PrintWriter to_server = 
        new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));
      System.out.println("opened stream for the socket");
      
      // Send the HTTP GET command to the Web server, specifying the file.
      // This uses an old and very simple version of the HTTP protocol
      to_server.println("POST " + filename);
      to_server.flush();  // Send it right now!
      System.out.println("GET request sent to web server for file" + filename);
      
      // Now read the server's response, and write it to the file
      System.out.println("reading from web server\n\n\n");
      byte[] buffer = new byte[4096];
      int bytes_read;
      while((bytes_read = from_server.read(buffer)) != -1)
        to_file.write(buffer, 0, bytes_read);
      
      // When the server closes the connection, we close our stuff
      socket.close();
      to_file.close();
    }
    catch (Exception e) {    // Report any errors that arise
      System.err.println(e);
      System.err.println("Usage: java HttpClient <URL> [<filename>]");
    }
  }
}
