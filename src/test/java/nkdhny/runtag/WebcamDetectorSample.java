package nkdhny.runtag;

/**
 * Created by nkdhny on 19.09.15.
 */
public class WebcamDetectorSample {
    public static void main(String[] args) {
        WebcamDetector d = new WebcamDetector(0);
        System.out.println("Detector started, campturing from the default camera");
        while(true) {
            for(Tag t: d.apply()){
                System.out.println(t.getId());
            }
        }
    }
}
