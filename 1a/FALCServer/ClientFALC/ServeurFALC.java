//README : les classes serveur et thread ont été simplifiées et organisées.
//Des fonctionnalités ont également été retirées car inutiles (cf anciennes versions).
//La partie "script", véritablement fonctionnelle se trouvera dans le run de la classe Thread.

package ClientFALC;

import java.io.PrintWriter;
import java.net.ServerSocket;
import java.util.Vector;

public class ServeurFALC {
	
	private static int nbClients = 0; //Contiendra le nombre total de clients connectés au serveur.
	private static Vector<PrintWriter> vectClients = new Vector<PrintWriter>(); //Contiendra les flux vers tous les clients.
	
	//Le mot-clé static est indispensable pour indiquer que les variables n'appartiennent pas à une instance particulière de la classe mais bien à la classe elle-même.
	//Quelques fonctions de gestion de clients multiples : 
	//L'attribut synchronized est indispensable ici pour que les différents Thread ne se marchent pas dessus. Cf cours sections critiques INF106.
	
	synchronized public static int addClient(PrintWriter outWriter) {
		nbClients++;
		vectClients.addElement(outWriter);
		System.out.println("Il y a au total "+getNbClients()+" clients connectés en ce moment\n");
		return getNbClients()-1;
	}
	
	synchronized public static void remClient(int i) {
		nbClients--;
		if(vectClients.elementAt(i) != null)  {
			vectClients.removeElementAt(i);
		}
	}
	
	synchronized public static int getNbClients() {
		return nbClients;
	}
	
	//On pourrait éventuellement créer une fonction sendAllClients pour envoyer un message à tous les clients au cas où on devrait faire une maintenance du serveur par exemple...
	//Voici un exemple de ce qu'on aurait pu faire : 
	
	synchronized public void sendAllClients(String msg) {
		PrintWriter out;
		for(int i = 0; i < vectClients.size(); i++) {
			out = (PrintWriter) vectClients.elementAt(i); //On cast le client numéro i du vecteur des clients en printwriter (puisque nous, l'admin, on sait que ce vecteur contiendra des PrintWriter)
			if (out!=null) {
				out.print(msg);
				out.flush();
			}
		}
	
	//Reminder pour la partie connect qui sera donc dans une autre classe :
	//La classe du socket serveur n'est pas la même que la classe du socket client...
	//A ce niveau python est plus simple car il n'a qu'un seule socket pour chaque côté. Socket simple pour le client, ServerSocket pour serveur en java.

	
	}
	public static void main(Integer args[]) {
		ServeurFALC serveurFALC = new ServeurFALC();
		try {
			int port;
			if(args.length<=0) port = 8080;
			else port = args[0]; //Par défaut sans argument ça sera le port 8080. Sinon l'argument passé à main.
						
			ServerSocket serverSocket = new ServerSocket(port);
			//Attention : un resource leak est signalé ici : celui qui fermera la connexion n'est pas le serveur mais le client. Cet avertissement est normal... en fonctionnement normal.
			
			while(true) {
				//On bloquera ici en attente d'une connexion. 
				new ServeurFALCThread(serverSocket.accept(),serveurFALC);
				//Dès qu'un client se connecte, un nouveau thread est démarré (cf ServeurFALCThread)
				//On peut afficher l'adresse IP du client grâce au code ci-dessous (on n'accepte qu'une seule fois cependant, attention !
				//String clientAddr = socket.getRemoteSocketAddress().toString();
		        //System.out.println("connection from " + clientAddr); //Affichage du client
			} 
		}
		catch(Exception e) {
		}
	}
}
