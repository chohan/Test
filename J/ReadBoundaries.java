package test;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;


class Line
{
	public Line(float fLat1, float fLng1, float fLat2, float fLng2)
	{
		fFromLat= fLat1;
		fFromLng= fLng1;
		fToLat	= fLat2;
		fToLng	= fLng2;
	}
	float fFromLat;
	float fFromLng;
	float fToLat;
	float fToLng;
}


public class ReadBoundaries
{
	float fLastLat;
	float fLastLng;
	boolean bFirstPoint = true;

	public static void main(String[] args)
	{
		String sFile = args[0];
		new ReadBoundaries();
	}
	
	public ReadBoundaries()
	{
		BufferedReader in;
		try{
		String dirBoundaries = System.getProperty("user.dir") + "\\boundaries\\";
		System.out.println(dirBoundaries);
		
		File file = new File(dirBoundaries);
			
		File[] files = file.listFiles();
		for(int i=0; i<files.length; i++)
		{
			String sFile = dirBoundaries + files[i].getName();
			System.out.println(sFile);
			in = new BufferedReader(new InputStreamReader(new FileInputStream(sFile)));

			String sArea = in.readLine();
			String sType = in.readLine();
			String sLine;
			while((sLine = in.readLine()) != null)
			{
				Line line = readLine(sLine);
				if(line != null)
				{
					System.out.println("Lat1/Lng1=" + line.fFromLat + "/" + line.fFromLng + " Lat2/Lng2=" + line.fToLat + "/" + line.fToLng);
				}
			}
			in.close();
		}
		}catch(FileNotFoundException e){e.printStackTrace(); System.exit(-1);}
		catch(IOException e){e.printStackTrace(); System.exit(-1);}
	}
	
	protected Line readLine(String sLine)
	{
		sLine = sLine.trim();
		if(sLine.equals("-1"))
		{
			fLastLat = fLastLng = 0;
			bFirstPoint = true;
			return null;
		}
		
		int iComaIndex = sLine.indexOf('+');		
		String sLat = sLine.substring(0, iComaIndex);
		String sLng = sLine.substring(iComaIndex+1);
//		System.out.println("Lat=" + sLat + " Lng=" + sLng);
		
		float fLat = Float.valueOf(sLat).floatValue();
		float fLng = Float.valueOf(sLng).floatValue();
		
		if(bFirstPoint)
		{
			bFirstPoint = false;
			fLastLat = fLat;
			fLastLng = fLng;
			return null;
		}
		
		Line line = new Line(fLastLat, fLastLng, fLat, fLng);
		fLastLat = fLat;
		fLastLng = fLng;
		
		return line;
	}
}
