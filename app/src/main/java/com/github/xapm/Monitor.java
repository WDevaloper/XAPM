package com.github.xapm;

public class Monitor {
    public static void release() {
        native_release();
    }


    public static void init(String path) {
        native_init(path);
    }

    public static native void native_init(String path);

    public static native void native_release();
}
