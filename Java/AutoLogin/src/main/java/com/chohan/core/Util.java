package com.chohan.core;

public class Util {

    public static String getClassname() {
        String fullClassName = Thread.currentThread().getStackTrace()[2].getClassName();
        return fullClassName.substring(fullClassName.lastIndexOf('.') + 1);
    }

    public static void trace() {
        StackTraceElement e = Thread.currentThread().getStackTrace()[2];
        System.out.println("\n\n\n################## Salah: " + e.getClassName() + ":" + e.getLineNumber() + " " + e.getMethodName() + "(..) ");
    }
}
