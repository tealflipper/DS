//client that calls remote object
import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;

public class Client1{
  //only client class can create itself
  private Client1 (){}

  public static void main(String[] args) {
    String host=(args.length < 1) ? null: args[0];
    try {
      //find host in registry
      Registry reg =LocateRegistry.getRegistry(host);
      //find remote object in host
      Stack stub = (Stack) reg.lookup("Stack");
      Integer a=0;
      Double b=2.5;
      Character c='a';
      stub.push(a);
      stub.push(b);
      stub.push(c);
      Object res=(Character)stub.pop();
      System.out.println("response: " + res);
      res=(Double)stub.pop()+0.0008;
      System.out.println("response: " + res);
      res=((Integer)stub.pop());
      res=((Integer) res)+9;
      System.out.println("response: " + res);

      System.out.println("response: " + stub.isEmpty());
    } catch (Exception e) {
      //TODO: handle exception
      System.err.println("Client exception: " + e.toString());
      e.printStackTrace();
    }
  }
}