package Server;
import Miscellaneous.*;
import java.util.*;

public class Timers
{
  Server  server;
  Timer   timer;

public Timers(Server svr)
{
  server = svr;

  TimerTask task50ms = new TimerTask()
  {
    public void run()
    {
    }
  };

  TimerTask task500ms = new TimerTask()
  {
    public void run()
    {
    }
  };

  TimerTask task1000ms = new TimerTask()
  {
    public void run()
    {
    }
  };

  TimerTask task2000ms = new TimerTask()
  {
    public void run()
    {
      server.aeroSpace.controller(2000);
    }
  };

  TimerTask task4000ms = new TimerTask()
  {
    public void run()
    {
    }
  };

  TimerTask task8000ms = new TimerTask()
  {
    public void run()
    {
    }
  };

  TimerTask task10000ms = new TimerTask()
  {
    public void run()
    {
    }
  };

  TimerTask task15000ms = new TimerTask()
  {
    public void run()
    {
//			_pDoc->m_pNetComm->SendLinkSignal(uTime);
    }
  };

  TimerTask task20000ms = new TimerTask()
  {
    public void run()
    {
    }
  };
  TimerTask task60000ms = new TimerTask()
  {
    public void run()
    {
//			_pDoc->m_pNetComm->MonitorLinkSignal(uTime);
//			client.targets.missionUpdator(60000);
    }
  };

  timer = new Timer(true);
  timer.scheduleAtFixedRate(task50ms,   new Date(System.currentTimeMillis()+5000), 50);
  timer.scheduleAtFixedRate(task500ms,  new Date(System.currentTimeMillis()+5000), 500);
  timer.scheduleAtFixedRate(task2000ms, new Date(System.currentTimeMillis()+5000), 2000);
  timer.scheduleAtFixedRate(task4000ms, new Date(System.currentTimeMillis()+5000), 4000);
  timer.scheduleAtFixedRate(task8000ms, new Date(System.currentTimeMillis()+5000), 8000);
  timer.scheduleAtFixedRate(task10000ms,new Date(System.currentTimeMillis()+5000), 10000);
  timer.scheduleAtFixedRate(task15000ms,new Date(System.currentTimeMillis()+5000), 15000);
  timer.scheduleAtFixedRate(task20000ms,new Date(System.currentTimeMillis()+5000), 20000);
  timer.scheduleAtFixedRate(task60000ms,new Date(System.currentTimeMillis()+5000), 60000);

}


}
