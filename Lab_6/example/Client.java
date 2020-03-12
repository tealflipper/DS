//client that calls remote object
package example;

import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;

public class Client{
  //only client class can create itself
  private Client (){}

  public static void main(String[] args) {
    String host=(args.length < 1) ? null: args[0];
    try {
      //find host in registry
      Registry reg =LocateRegistry.getRegistry(host);
      //find remote object in host
      Hello stub = (Hello) reg.lookup("Hello");
      String res=stub.sayHello();
      System.out.println("response: " + res);
    } catch (Exception e) {
      //TODO: handle exception
      System.err.println("Client exception: " + e.toString());
      e.printStackTrace();
    }
  }
}