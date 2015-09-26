package nkdhny.runtag

import java.applet.Applet
import java.util.concurrent.Executors

import netscape.javascript.JSObject

import org.json4s._
import org.json4s.native.JsonMethods._
import org.json4s.native.Serialization
import org.json4s.native.Serialization.{read, write}


/**
 * Created by nkdhny on 17.09.15.
 */
class Detector extends Applet {

  var detector: WebcamDetector = null

  def messageFormat(tag: Tag) = {

    Map("id" -> tag.getId, "left" -> tag.getX, "top" -> tag.getY)
  }

  implicit val format = DefaultFormats

  override def start(): Unit = {

    val window = JSObject.getWindow(this)
    detector = new WebcamDetector(0)

    Executors.newSingleThreadExecutor().execute(new Runnable {
      override def run(): Unit = {
        while(true) {
          val tags = detector.apply()

          tags.foreach(t => window.eval(s"processMessage('${write(messageFormat(t))}')"))

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
