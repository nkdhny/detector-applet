package nkdhny.runtag;


import java.security.AccessController;
import java.security.PrivilegedAction;
import java.util.List;
/**
 * Created by nkdhny on 19.09.15.
 */
public class WebcamDetector {

    static {
//        AccessController.doPrivileged(new PrivilegedAction() {
//            @Override
//            public Object run() {
                System.loadLibrary("jruntagwebcamdetector");
//                return null;
//            }
//        });

    }

    private final int cameraId;
    private long nativeDetectorPointer;

    public WebcamDetector(int cameraId) {
        this.cameraId = cameraId;
        setupNativeDetector();
    }

    public void release() {
        releaseNativeDetector();
    }

    public int getCameraId() {
        return cameraId;
    }


    @Override
    protected void finalize() throws Throwable {
        this.releaseNativeDetector();
    }

    private native long setupNativeDetector();
    private native void releaseNativeDetector();
    public native Tag[] apply();

}
