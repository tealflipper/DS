//import remote to implement
import java.rmi.Remote;
import java.rmi.RemoteException;

//create remote interface
public interface Stack2 extends Remote{
  void push(Object toInsert) throws RemoteException;
  Object pop() throws RemoteException;
  boolean isEmpty() throws RemoteException;
  Object top() throws RemoteException;
}