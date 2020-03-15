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
      System.out.println("\ncliente 2 revisa si la pila esta vacia: " + stub.isEmpty());
      if(stub.isEmpty()){
        System.out.println("cliente 2: La pila esta vacia");
      }else{
        System.out.println("cliente 2 vacia la pila ");
        while(!stub.isEmpty()){
        Object res=stub.pop();
        System.out.println("cliente 2 respuesta: " + res);
        }
      }

      
    } catch (Exception e) {
      //TODO: handle exception
      System.err.println("Client exception: " + e.toString());
      e.printStackTrace();
    }
  }
}