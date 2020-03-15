//client that calls remote object
import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;

public class Client1{
  //only client class can create itself
  private Client1 (){}

  public static void main(String[] args) {
    String host=(args.length < 1) ? null: args[0];
    String host2=(args.length < 2) ? null: args[0];

    try {
      //find host in registry
      Registry reg =LocateRegistry.getRegistry(host);
      //find remote object in host
      Stack stub1 = (Stack) reg.lookup("Stack");
      if(args.length< 2) reg =LocateRegistry.getRegistry(host2);
      Stack stub2 = (Stack) reg.lookup("Stack");
      Integer a=0;
      Double b=2.5;
      Character c='a';
      stub1.push(a);
      stub1.push(b);
      stub1.push(c);
      System.out.println("Cliente 1 subio a la pila 1: "+a);
      System.out.println("Cliente 1 subio a la pila 1: "+b);
      System.out.println("Cliente 1 subio a la pila 1: "+c);
      a=1;
      b=3.5;
      c='d';
      stub2.push(a);
      stub2.push(b);
      stub2.push(c);
      System.out.println("Cliente 1 subio a la pila 2: "+a);
      System.out.println("Cliente 1 subio a la pila 2: "+b);
      System.out.println("Cliente 1 subio a la pila 2: "+c);
      Object res=(Character)stub2.pop();
      System.out.println("saco "+res+" de la pila 2");
      res=(Double)stub2.pop();
      System.out.println("saco "+res+" de la pila 2");
      res=((Integer)stub2.pop());
      System.out.println("saco "+res+" de la pila 2");
      System.out.println("reviso si la pila 1 esta vacia: " + stub1.isEmpty());
      System.out.println("reviso si la pila 2 esta vacia: " + stub2.isEmpty());
      res=stub2.top() ;
      System.out.println("saco "+res+" de la pila 2");
      while(true);
    } catch (Exception e) {
      //TODO: handle exception
      System.err.println("Client exception: " + e.toString());
      e.printStackTrace();
    }
  }
}