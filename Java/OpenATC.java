//this is an http client applicaton which can read data from openatc.com
//it uses URLConnection class

//usage
//F:\Projects\ACCS\classes>"C:\Program Files\Java\jre6\bin\java" test.OpenATC 
//http://www.openatc.com/GE_Data_EU.asp?SID=KPGpKBpfUuC37zH7KPBGUKOtw53TvFUi

package test;

import java.net.*;
import java.io.*;
import java.util.zip.*;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;

public class OpenATC {

	String zfile = "20080419.zip";	//output zip file read from OpenATC
	
public OpenATC(String sURL)
{
	parseIAgree(sURL);
//	readSite(sURL);
//	parseKML(sURL);
//	cleaner(sURL, "out.kml");
}
	
public static void main(String argv[]) throws Exception
{
	 if(argv.length != 1) {
	    System.out.println("Usage: java OpenATC <url>");
	    System.exit(0);
	 }
	 new OpenATC(argv[0]);
}

public boolean  parseIAgree(String sGEFile)	//ge.asp
{	 
    try {
    	System.out.println("parsing " + sGEFile);

    		DocumentBuilderFactory docBuilderFactory;
    		DocumentBuilder docBuilder;
    		Document doc;
    		
	        docBuilderFactory = DocumentBuilderFactory.newInstance();
	        
	        // Configure it to coalesce CDATA nodes
	        docBuilderFactory.setCoalescing(true);
	        docBuilderFactory.setIgnoringComments(true);
	        docBuilderFactory.setIgnoringElementContentWhitespace(true);
	        docBuilder = docBuilderFactory.newDocumentBuilder();
	        doc = docBuilder.parse (new File(sGEFile));
			    
	        // normalize text representation
	        doc.getDocumentElement ().normalize ();
//	        System.out.println ("Root element of the doc is " + doc.getDocumentElement().getNodeName());

	        //reading NetworkLink
	        NodeList listHref = doc.getElementsByTagName("href");
	        int size = listHref.getLength();
//	        System.out.println("Total no of href : " + size);

	        for(int i=0; i<size; i++)
	        {
	            Node href = listHref.item(i);
	            //System.out.println(href.getNodeName());
	            
	            String sLink = href.getFirstChild().getNodeValue();
	            System.out.println(sLink);
	        }


    }catch (SAXParseException err) {
    System.out.println ("** Parsing error" + ", line " 
         + err.getLineNumber () + ", uri " + err.getSystemId ());
    System.out.println(" " + err.getMessage ());
    return false;
    }catch (SAXException e) {
    	System.out.println("ERROR: SAXException Could not parse XML input file " + e.getMessage());
    	Exception x = e.getException ();
    ((x == null) ? e : x).printStackTrace ();
    return false;
    }catch (Throwable t) {
    	System.out.println("ERROR: Throwable Could not parse XML input file " + t.getMessage());
    t.printStackTrace ();
    return false;
    }
    
    return true;
}

public void	 readSite(String sURL)	//http://www.openatc.com/GE_Data_EU.asp?SID=HgzsPJGtHDQATnCOSAWWtVgYRFdTdzXZ
{	 
	// System.setProperty("http.proxyHost", "StanISA01");
	// System.setProperty("http.proxyPort", "8080");
	 //http.nonProxyHosts (default: <none>)
	
	try {
	 URL url = new URL(sURL);
	 URLConnection con = url.openConnection();
	
	 BufferedInputStream in = new BufferedInputStream(new DataInputStream(con.getInputStream()));
	 DataOutputStream dos = new DataOutputStream(new FileOutputStream(zfile));
	 while (true) {
	     int data = in.read();
	     if (data < 0)
	        break;
	     //System.out.print((char)data);
	     dos.writeByte(data);
	  } 
	} catch(IOException e) { return; }
	 
	System.out.println("Zip file read. Now unzipping it.");
	 unzip(zfile);
}
	
public boolean unzip(String zfile)
{
	System.out.println("unzip is called");

	ZipInputStream zin;
	try {
	 zin = new ZipInputStream(new BufferedInputStream(new FileInputStream(zfile)));
	} catch(IOException e) { System.out.println("Exception 1"); return false; }
	
    // Need a buffer for reading from the input file.
	final int BUF_SIZE = 1000000;
    byte[] input_buffer = new byte[BUF_SIZE];
    int len = 0;	

    // Loop through the entries in the ZIP archive and read
    // each compressed file.
    do {
      try {
        // Need to read the ZipEntry for each file in the archive
        ZipEntry zip_entry = zin.getNextEntry ();
        if (zip_entry == null) break;

        // Use the ZipEntry name as that of the compressed file.
        File output_file = new File ("F:\\Projects\\ACCS\\classes", zip_entry.getName());

        // Create a buffered output stream.
        FileOutputStream out = new FileOutputStream(output_file);
        BufferedOutputStream destination =
          new BufferedOutputStream (out, BUF_SIZE);

        // Reading from the zip input stream will decompress the data
        // which is then written to the output file.
        while ((len = zin.read (input_buffer, 0, BUF_SIZE)) != -1)
          destination.write (input_buffer, 0, len);
        destination.flush (); // Insure all the data is output
        out.close ();
      }
      catch (IOException e) { System.out.println("exception 2"); return false; }
    } while (true);// Continue reading files from the archive

    try {
      zin.close ();
    }
    catch (IOException e) { System.out.println("exception 3"); return false; }
    
    return true;
}

public boolean cleaner(String inFile, String outFile)
{
	BufferedInputStream in;
	try {
	 in = new BufferedInputStream(new FileInputStream(inFile));
	} catch(IOException e) { System.out.println("Exception 1"); return false; }
	
	DataOutputStream out;
	try {
	 out = new DataOutputStream(new FileOutputStream(outFile));
	} catch(IOException e) { System.out.println("Exception 2"); return false; }
	
	try {
	 while (true) {
	     int data = in.read();
	     if (data < 0)
	        break;
	     if(data > 127)
	     {
	    	 System.out.print(data);
	     }
	     else
	    	 out.write(data);
	  } 
	 out.flush();
	 out.close();
	} catch(IOException e) { System.out.println("Exception 3"); return false; }

	return true;
}

public boolean parseKML(String sFile)
{
    try {
System.out.println("parsing " + sFile);

	DocumentBuilderFactory docBuilderFactory;
	DocumentBuilder docBuilder;
	Document doc;
	
        docBuilderFactory = DocumentBuilderFactory.newInstance();
        
        // Configure it to coalesce CDATA nodes
        docBuilderFactory.setCoalescing(true);
        docBuilderFactory.setIgnoringComments(true);
        docBuilderFactory.setIgnoringElementContentWhitespace(true);
        docBuilder = docBuilderFactory.newDocumentBuilder();
        doc = docBuilder.parse (new File(sFile));
		    
        // normalize text representation
        doc.getDocumentElement ().normalize ();
        System.out.println ("Root element of the doc is " + 
             doc.getDocumentElement().getNodeName());

        //reading styles
        NodeList listOfStyles = doc.getElementsByTagName("Style");
        int totalStyles = listOfStyles.getLength();
        System.out.println("Total no of Styles : " + totalStyles);

        //reading Placemarks
        NodeList listOfPlacemarks = doc.getElementsByTagName("Placemark");
        int totalPlacemarks = listOfPlacemarks.getLength();
        System.out.println("Total no of Placemarks : " + totalPlacemarks);

        for(int i=0; i<listOfPlacemarks.getLength() ; i+=2)
        {
            Node firstPersonNode = listOfPlacemarks.item(i);
            
            parsePlacemarkPoint(firstPersonNode);
        	
        	parsePlacemarkPath(firstPersonNode);
 /*       	
             if(firstPersonNode.getNodeType() == Node.ELEMENT_NODE){


                Element firstPersonElement = (Element)firstPersonNode;

                //-------
                NodeList firstNameList = firstPersonElement.getElementsByTagName("first");
                Element firstNameElement = (Element)firstNameList.item(0);

                NodeList textFNList = firstNameElement.getChildNodes();
                System.out.println("First Name : " + 
                       ((Node)textFNList.item(0)).getNodeValue().trim());

                //-------
                NodeList lastNameList = firstPersonElement.getElementsByTagName("last");
                Element lastNameElement = (Element)lastNameList.item(0);

                NodeList textLNList = lastNameElement.getChildNodes();
                System.out.println("Last Name : " + 
                       ((Node)textLNList.item(0)).getNodeValue().trim());

                //----
                NodeList ageList = firstPersonElement.getElementsByTagName("age");
                Element ageElement = (Element)ageList.item(0);

                NodeList textAgeList = ageElement.getChildNodes();
                System.out.println("Age : " + 
                       ((Node)textAgeList.item(0)).getNodeValue().trim());

                //------


            }//end of if clause
*/

        }//end of for loop with s var


    }catch (SAXParseException err) {
    System.out.println ("** Parsing error" + ", line " 
         + err.getLineNumber () + ", uri " + err.getSystemId ());
    System.out.println(" " + err.getMessage ());
    return false;
    }catch (SAXException e) {
    	System.out.println("ERROR: SAXException Could not parse XML input file " + e.getMessage());
    	Exception x = e.getException ();
    ((x == null) ? e : x).printStackTrace ();
    return false;
    }catch (Throwable t) {
    	System.out.println("ERROR: Throwable Could not parse XML input file " + t.getMessage());
    t.printStackTrace ();
    return false;
    }
    
    return true;
}

protected void parsePlacemarkPoint(Node nodePlacemark) throws SAXParseException, SAXException, Throwable
{
	//Placemark
   System.out.println(nodePlacemark.getNodeName());
   
   Node node;
   
   //LookAt
   node = nodePlacemark.getFirstChild();
   if(node!=null)
   {
//	   System.out.println(node.getNodeName());
   }
   
   //Longitude
   Node nodeLongitude = nodePlacemark.getFirstChild().getFirstChild();
   if(nodeLongitude!=null)
   {
///	   System.out.println(nodeLongitude.getNodeName());
//	   System.out.println(nodeLongitude.getFirstChild().getNodeValue());
   }

   //Latitude
   Node nodeLatitude = nodePlacemark.getFirstChild().getChildNodes().item(1);
   if(nodeLatitude!=null)
   {
//	   System.out.println(nodeLatitude.getNodeName());
//	   System.out.println(nodeLatitude.getFirstChild().getNodeValue());
   }
   
   //Point
   Node nodePoint = nodePlacemark.getLastChild();
   if(nodePoint != null)
   {
	   Node nodeCoord = nodePoint.getLastChild();
	   String sCoord	= nodeCoord.getFirstChild().getNodeValue();
	   
	   System.out.println(sCoord);
   }
}

protected void parsePlacemarkPath(Node nodePlacemark)
{
}

}
