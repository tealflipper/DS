//server that uses remote interface
//main class creates instance of remote object

import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;

//server implements object's methods
public class Server2 implements Stack2{

  private ArrayList<Object> stack = new ArrayList <>();
  int stackSize;
  //constructor
  public Server2 (){
    stackSize=stack.size();
  }

  // From hello interface
  public void push(Object toInsert) {
    stack.add(toInsert);
    stackSize=stack.size();

  }
  public Object pop(){
    Object toRet;
    toRet=stack.get(stackSize-1);
    stack.remove(stackSize-1);
    stackSize=stack.size();
    return toRet;
  }
  public boolean isEmpty(){
    return stack.isEmpty();
  }
  public Object top(){
    return stack.get(stackSize-1);
  }



  //create and export  remote object
  //register remote object within java RMI registry
  public static void main(String args[]){
    try {
      //create remote object
      Server2 obj=new Server2();
      //export remote object to a stub
      Stack2 stub=(Stack2) UnicastRemoteObject.exportObject(obj,0);
      // Bind the remote object's stub in the registry
      Registry registry =LocateRegistry.getRegistry(); //create registry
      //bind remote object ro registry with stub
      registry.bind("Stack2",stub);

      System.err.println("server ready");
    } catch (Exception e) {
      //TODO: handle exception
      System.err.println("Server exception: "+ e.toString());
      e.printStackTrace();
    }
  }
}