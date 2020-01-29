package Client;
import Miscellaneous.*;
import java.awt.Point;

public class Targets
{
  protected Client  client;
	public    Target  trackHook       = null;

public Targets()
{
}

public Targets(Client client)
{
  this.client = client;
}

public void add()
{
  DlgTargetUpdate dlg = new DlgTargetUpdate(client, null);
}

public int add(Target target)
{
  return client.targetCont.add(target);
}

public void update()
{
  DlgTargetUpdate dlg = new DlgTargetUpdate(client, trackHook);
}

public void update(Target target)
{
  client.targetCont.update(target);
}

public void delete()
{
  if(trackHook != null)
    delete(trackHook.nID);
}

public boolean delete(int nSTN)
{
  return client.targetCont.delete(nSTN);
}

public void idChange(char cID)
{
  if((cID != 0) && (trackHook!=null))
    idChange(trackHook.nID, cID);
}

public boolean idChange(int nSTN, char cID)
{
  if(client.targetCont.idChange(nSTN, cID))
  {
    trackHook.cID = cID;
    trackHook.cRID= cID;
    return true;
  }
  return false;
}

public void idRecommend(char cID)
{
  if((cID != 0) && (trackHook!=null))
    idRecommend(trackHook.nID, cID);
}

public boolean idRecommend(int nSTN, char cID)
{
  if(client.targetCont.idRecommend(nSTN, cID))
  {
    trackHook.cRID= cID;
    return true;
  }
  return false;
}

public void stnChange(int nSTNNew)
{
  if((nSTNNew > 0) && (trackHook!=null))
    stnChange(trackHook.nID, nSTNNew);
}

public boolean stnChange(int nOldSTN, int nNewSTN)
{
  return client.targetCont.stnChange(nOldSTN, nNewSTN);
}

public void reposition(Point point)
{
	if(trackHook != null)
	{
    Spot spt;
		spt = client.Pxl2LatLong(point);
		trackHook.fLatitude	= spt.fLatitude;
		trackHook.fLongitude= spt.fLongitude;
    update(trackHook);
//    client.targetCont.update(trackHook);
	}
}
/*
public boolean hook(Point pt)
{
	trackHook = (Target)client.console.hookObject(tracks, pt);
	if(trackHook == null)
		return false;
	else
		return true;
}

public Mark isHooked()
{
	if(trackHook != null)
		return trackHook;
  else
    return null;
}

public void deleteHooked()
{
	if(trackHook != null)
    delete(trackHook.nID);
}
*/
}