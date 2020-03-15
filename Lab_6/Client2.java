//client that calls remote object
import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;

public class Client2{
  //only client class can create itself
  private Client2 (){}

  public static void main(String[] args) {
    String host=(args.length < 1) ? null: args[0];
    try {
      //find host in registry
      Registry reg =LocateRegistry.getRegistry(host);
      //find remote object in host
      Stack stub = (Stack) reg.lookup("Stack");
      System.out.println("reviso si la pila esta vacia: " + stub.isEmpty());
      if(stub.isEmpty()){
        System.out.println("La pila esta vacia");
      }else{
        System.out.println("Vacio la pila ");
        while(!stub.isEmpty()){
        Object res=stub.pop();
        System.out.println("response: " + res);
        }
      }

      
    } catch (Exception e) {
      //TODO: handle exception
      System.err.println("Client exception: " + e.toString());
      e.printStackTrace();
    }
  }
}