//remote interface
package example;

//import remote to implement
import java.rmi.Remote;
import java.rmi.RemoteException;

//create remote interface
public interface Hello extends Remote{
  String sayHello() throws RemoteException;
}