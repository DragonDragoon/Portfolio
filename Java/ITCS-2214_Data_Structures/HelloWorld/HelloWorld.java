package HelloWorld;
import edu.uncc.cs.bridges.*;

public class HelloWorld {
  public static void main(String[] args) {
    GraphVisualizer gv = new GraphVisualizer();
    Bridge.init(0, "1355347875827", gv, "wwoodar1");
    Vertex<String> HelloWorld = new Vertex<String>("HelloWorld", gv);
    HelloWorld.setColor("red").setSize(15);
    
    Vertex<String> GoodByeWorld = new Vertex<String>("GoodByeWorld", gv);
    HelloWorld.createEdge(GoodByeWorld);
    GoodByeWorld.setColor("yellow");
    
    Bridge.complete();
  }
}