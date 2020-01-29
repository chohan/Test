
//package StackOverflowQ443708_JavaCallBackTest;
//http://www.javaworld.com/article/2077462/learn-java/java-tip-10--implement-callback-routines-in-java.html

import java.lang.reflect.*;
import java.util.concurrent.*;

class CallbackMethod
{
    ExecutorService EXE =
        //Executors.newCachedThreadPool ();
        Executors.newSingleThreadExecutor ();

    public static void PrintLine ()
    {
        System.out.println ("--------------------------------------------------------------------------------");
    }

    public void SetTimer (final int timeout, final Object obj, final String methodName, final Object... args)
    {
        SetTimer (timeout, obj, false, methodName, args);
    }
    public void SetTimer (final int timeout, final Object obj, final boolean isStatic, final String methodName, final Object... args)
    {
        Class<?>[] argTypes = null;
        if (args != null)
        {
            argTypes = new Class<?> [args.length];
            for (int i=0; i<args.length; i++)
            {
                argTypes[i] = args[i].getClass ();
            }
        }

        SetTimer (timeout, obj, isStatic, methodName, argTypes, args);
    }
    public void SetTimer (final int timeout, final Object obj, final String methodName, final Class<?>[] argTypes, final Object... args)
    {
        SetTimer (timeout, obj, false, methodName, argTypes, args);
    }
    public void SetTimer (final int timeout, final Object obj, final boolean isStatic, final String methodName, final Class<?>[] argTypes, final Object... args)
    {
        EXE.execute (
            new Runnable()
            {
                public void run ()
                {
                    Class<?> c;
                    Method method;
                    try
                    {
                        if (isStatic) c = (Class<?>)obj;
                        else c = obj.getClass ();

                        System.out.println ("Wait for " + timeout + " seconds to invoke " + c.getSimpleName () + "::[" + methodName + "]");
                        TimeUnit.SECONDS.sleep (timeout);
                        System.out.println ();
                        System.out.println ("invoking " + c.getSimpleName () + "::[" + methodName + "]...");
                        PrintLine ();
                        method = c.getDeclaredMethod (methodName, argTypes);
                        method.invoke (obj, args);
                    }
                    catch (Exception e)
                    {
                        e.printStackTrace();
                    }
                    finally
                    {
                        PrintLine ();
                    }
                }
            }
        );
    }
    public void ShutdownTimer ()
    {
        EXE.shutdown ();
    }
}

public class CallBackTest
{
    public void onUserTimeout ()
    {
        System.out.println ("onUserTimeout");
    }
    public void onTestEnd ()
    {
        System.out.println ("onTestEnd");
    }
    public void NullParameterTest (String sParam, int iParam)
    {
        System.out.println ("NullParameterTest: String parameter=" + sParam + ", int parameter=" + iParam);
    }
    public static void main (String[] args)
    {
        CallBackTest test = new CallBackTest ();
        MyTimer timer = new MyTimer ();

        timer.SetTimer ((int)(Math.random ()*10), test, "onUserTimeout");
        timer.SetTimer ((int)(Math.random ()*10), test, "onTestEnd");
        timer.SetTimer ((int)(Math.random ()*10), test, "A-Method-Which-Is-Not-Exists");    // java.lang.NoSuchMethodException

        timer.SetTimer ((int)(Math.random ()*10), System.out, "println", "this is an argument of System.out.println() which is called by timer");
        timer.SetTimer ((int)(Math.random ()*10), System.class, true, "currentTimeMillis");
        timer.SetTimer ((int)(Math.random ()*10), System.class, true, "currentTimeMillis", "Should-Not-Pass-Arguments");    // java.lang.NoSuchMethodException

        timer.SetTimer ((int)(Math.random ()*10), String.class, true, "format", "%d %X", 100, 200); // java.lang.NoSuchMethodException
        timer.SetTimer ((int)(Math.random ()*10), String.class, true, "format", "%d %X", new Object[]{100, 200});

        timer.SetTimer ((int)(Math.random ()*10), test, "NullParameterTest", new Class<?>[]{String.class, int.class}, null, 888);

        timer.ShutdownTimer ();
    }
}