package Client;
import Miscellaneous.*;
import javax.swing.*;
import java.awt.*;
/*
//////////////////////////
class SessionSite extends Mark
{
  Client  client;
  Session session;

public SessionSite(Client client, Session session)
{
  this.client = client;
  this.session = session;
  session.panel= this;
  client.getContentPane().add(this);
}

public void paint(Graphics g)
{
  Point pt = client.LatLong2Pxl(session.fLatitude, session.fLongitude);
  setLocation(pt);
  g.drawRect(pt.x, pt.y, 10, 10);
}

}

//////////////////////////
class BaseEnemy extends Mark
{
  Client  client;
  Base    base;

public BaseEnemy(Client client, Base base)
{
  this.client = client;
  this.base = base;
  base.panel= this;
  client.getContentPane().add(this);
}

public void paint(Graphics g)
{
  Point pt = client.LatLong2Pxl(base.fLatitude, base.fLongitude);
  setLocation(pt);
  g.drawOval(pt.x, pt.y, 10, 10);
}

}

//////////////////////////
class BaseFriendly extends Mark
{
  Client  client;
  Base    base;

public BaseFriendly(Client client, Base base)
{
  this.client = client;
  this.base = base;
  base.panel= this;
  client.getContentPane().add(this);
}

public void paint(Graphics g)
{
  Point pt = client.LatLong2Pxl(base.fLatitude, base.fLongitude);
  setLocation(pt);
  g.drawOval(pt.x, pt.y, 10, 10);
}

}

//////////////////////////
class RadarSite extends Mark
{
  Client    client;
  RadarSite radarSite;

public RadarSite(Client client, RadarSite radarSite)
{
  this.client = client;
  this.radarSite = radarSite;
//  radarSite.panel= this;
//  client.getContentPane().add(this);
}
public void drawInit(JFrame frame)
{
panel = new P();
frame.getContentPane().add(panel);
}
class P extends JPanel
{
float a;
public void paint(Graphics g)
{
a = fLatitude;
  Point pt = client.LatLong2Pxl(radarSite.fLatitude, radarSite.fLongitude);
  setLocation(pt);
  g.drawOval(pt.x, pt.y, 10, 10);
}
}

}
*/
/*
//////////////////////////
abstract class Pic extends JPanel
{
  Client  client;
  Symbol  symbol;

public Pic(Client client, Symbol symbol)
{
  this.client = client;
  this.symbol = symbol;
  symbol.panel= this;
  client.getContentPane().add(this);
}
}

//////////////////////////
class Balloon extends Pic
{

public Balloon(Client client, Symbol symbol)
{
  super(client, symbol);
}

public void paint(Graphics g)
{
  Point pt = client.LatLong2Pxl(symbol.fLatitude, symbol.fLongitude);
  setLocation(pt);
  g.fillOval(pt.x, pt.y, 20, 10);
  g.drawString(symbol.sName, pt.x, pt.y+20);
}

}

//////////////////////////
class Bridge extends Pic
{

public Bridge(Client client, Symbol symbol)
{
  super(client, symbol);
}

public void paint(Graphics g)
{
  Point pt = client.LatLong2Pxl(symbol.fLatitude, symbol.fLongitude);
  setLocation(pt);
  g.drawLine(pt.x-5, pt.y-1, pt.x+5, pt.y-1);
  g.drawLine(pt.x-5, pt.y+1, pt.x+5, pt.y+1);
  g.drawString(symbol.sName, pt.x-5, pt.y+9);
}

}

//////////////////////////
class CAP extends Pic
{

public CAP(Client client, Symbol symbol)
{
  super(client, symbol);
}

public void paint(Graphics g)
{
  Point pt = client.LatLong2Pxl(symbol.fLatitude, symbol.fLongitude);
  setLocation(pt);
  g.drawOval(pt.x, pt.y, 10, 10);
  g.drawString(symbol.sName, pt.x-8, pt.y+10);
}

}

//////////////////////////
class COC extends Pic
{

public COC(Client client, Symbol symbol)
{
  super(client, symbol);
}

public void paint(Graphics g)
{
  Point pt = client.LatLong2Pxl(symbol.fLatitude, symbol.fLongitude);
  setLocation(pt);
  g.drawOval(pt.x, pt.y, 10, 10);
}

}

//////////////////////////
class CRC extends Pic
{

public CRC(Client client, Symbol symbol)
{
  super(client, symbol);
}

public void paint(Graphics g)
{
  Point pt = client.LatLong2Pxl(symbol.fLatitude, symbol.fLongitude);
  setLocation(pt);
  g.drawOval(pt.x, pt.y, 10, 10);
}

}

//////////////////////////
class Cursor extends Pic
{

public Cursor(Client client, Symbol symbol)
{
  super(client, symbol);
}

public void paint(Graphics g)
{
  Point pt = client.LatLong2Pxl(symbol.fLatitude, symbol.fLongitude);
  setLocation(pt);
  g.setColor(Color.red);
  g.drawOval(pt.x, pt.y, 10, 10);
}

}

//////////////////////////
class Gun extends Pic
{

public Gun(Client client, Symbol symbol)
{
  super(client, symbol);
}

public void paint(Graphics g)
{
  Point pt = client.LatLong2Pxl(symbol.fLatitude, symbol.fLongitude);
  setLocation(pt);
  g.drawOval(pt.x, pt.y, 10, 10);
}

}

//////////////////////////
class LandMark extends Pic
{

public LandMark(Client client, Symbol symbol)
{
  super(client, symbol);
}

public void paint(Graphics g)
{
  Point pt = client.LatLong2Pxl(symbol.fLatitude, symbol.fLongitude);
  setLocation(pt);
  Point pt1 = new Point(pt.x, pt.y-3);
  Point pt2 = new Point(pt.x+3, pt.y+3);
  Point pt3 = new Point(pt.x-3, pt.y+3);
  g.drawLine(pt1.x, pt1.y, pt2.x, pt2.y);
  g.drawLine(pt1.x, pt1.y, pt3.x, pt3.y);
  g.drawLine(pt3.x, pt3.y, pt2.x, pt2.y);
  g.drawString(symbol.sName, pt.x-5, pt.y+12);
}

}

//////////////////////////
class MOU extends Pic
{

public MOU(Client client, Symbol symbol)
{
  super(client, symbol);
}

public void paint(Graphics g)
{
  Point pt = client.LatLong2Pxl(symbol.fLatitude, symbol.fLongitude);
  setLocation(pt);
  g.drawOval(pt.x, pt.y, 10, 10);
}

}

//////////////////////////
class OCC extends Pic
{

public OCC(Client client, Symbol symbol)
{
  super(client, symbol);
}

public void paint(Graphics g)
{
  Point pt = client.LatLong2Pxl(symbol.fLatitude, symbol.fLongitude);
  setLocation(pt);
  g.drawOval(pt.x, pt.y, 10, 10);
}

}

//////////////////////////
class SAM extends Pic
{

public SAM(Client client, Symbol symbol)
{
  super(client, symbol);
}

public void paint(Graphics g)
{
  Point pt = client.LatLong2Pxl(symbol.fLatitude, symbol.fLongitude);
  setLocation(pt);
  g.drawOval(pt.x, pt.y, 10, 10);
}

}

//////////////////////////
class SOC extends Pic
{

public SOC(Client client, Symbol symbol)
{
  super(client, symbol);
}

public void paint(Graphics g)
{
  Point pt = client.LatLong2Pxl(symbol.fLatitude, symbol.fLongitude);
  setLocation(pt);
  g.drawOval(pt.x, pt.y, 10, 10);
}

}

//////////////////////////
class NavAid extends Pic
{

public NavAid(Client client, Symbol symbol)
{
  super(client, symbol);
}

public void paint(Graphics g)
{
  Point pt = client.LatLong2Pxl(symbol.fLatitude, symbol.fLongitude);
  setLocation(pt);
  g.drawLine(pt.x, pt.y, pt.x, pt.y+10);
  g.drawLine(pt.x, pt.y, pt.x-3, pt.y+3);
  g.drawLine(pt.x, pt.y, pt.x+3, pt.y+3);
  g.drawString(symbol.sName, pt.x+2, pt.y+12);
}

}

//////////////////////////
class VP extends Pic
{

public VP(Client client, Symbol symbol)
{
  super(client, symbol);
}

public void paint(Graphics g)
{
  Point pt = client.LatLong2Pxl(symbol.fLatitude, symbol.fLongitude);
  setLocation(pt);
  g.drawLine(pt.x-3, pt.y, pt.x, pt.y+6);
  g.drawLine(pt.x+3, pt.y, pt.x, pt.y+6);
  g.drawString(symbol.sName, pt.x-5, pt.y+14);
}

}
*/
