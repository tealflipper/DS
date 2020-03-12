//server that uses remote interface
//main class creates instance of remote object

package example;

import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

//server implements object's methods
public class Server implements Hello{
  //constructor
  public Server (){}

  //From hello interface
  public String sayHello(){
    return "Hello world";
  }

  //create and export  remote object
  //register remote object within java RMI registry
  public static void main(String args[]){
    try {
      //create remote object
      Server obj=new Server();
      //export remote object to a stub
      Hello stub=(Hello) UnicastRemoteObject.exportObject(obj,0);
      // Bind the remote object's stub in the registry
      Registry registry =LocateRegistry.getRegistry(); //create registry
      //bind remote object ro registry with stub
      registry.bind("Hello",stub);

      System.err.println("server ready");
    } catch (Exception e) {
      //TODO: handle exception
      System.err.println("Server exception: "+ e.toString());
      e.printStackTrace();
    }
  }
}