package nkdhny.runtag

import java.applet.Applet
import java.util.concurrent.Executors

import netscape.javascript.JSObject

/**
 * Created by nkdhny on 17.09.15.
 */
class Detector extends Applet {

  var detector: WebcamDetector = null

  override def start(): Unit = {

    val window = JSObject.getWindow(this)
    detector = new WebcamDetector(0)

    Executors.newSingleThreadExecutor().execute(new Runnable {
      override def run(): Unit = {
        while(true) {
          val tags = detector.apply()

          tags.foreach(t => window.eval(s"processMessage('${t.getId}')"))

        }
      }
    })

    window.eval("processMessage('Started')")
  }

  override def stop(): Unit = {
    detector.release()
    JSObject.getWindow(this).eval("processMessage('Stopped')")
  }
}
