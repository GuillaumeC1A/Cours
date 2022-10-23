//README : les classes serveur et thread ont �t� simplifi�es et organis�es.
//Des fonctionnalit�s ont �galement �t� retir�es car inutiles (cf anciennes versions).
//La partie "script", v�ritablement fonctionnelle se trouvera dans le run de la classe Thread.

package ClientFALC;

import java.io.PrintWriter;
import java.net.ServerSocket;
import java.util.Vector;

public class ServeurFALC {
	
	private static int nbClients = 0; //Contiendra le nombre total de clients connect�s au serveur.
	private static Vector<PrintWriter> vectClients = new Vector<PrintWriter>(); //Contiendra les flux vers tous les clients.
	
	//Le mot-cl� static est indispensable pour indiquer que les variables n'appartiennent pas � une instance particuli�re de la classe mais bien � la classe elle-m�me.
	//Quelques fonctions de gestion de clients multiples : 
	//L'attribut synchronized est indispensable ici pour que les diff�rents Thread ne se marchent pas dessus. Cf cours sections critiques INF106.
	
	synchronized public static int addClient(PrintWriter outWriter) {
		nbClients++;
		vectClients.addElement(outWriter);
		System.out.println("Il y a au total "+getNbClients()+" clients connect�s en ce moment\n");
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
	
	//On pourrait �ventuellement cr�er une fonction sendAllClients pour envoyer un message � tous les clients au cas o� on devrait faire une maintenance du serveur par exemple...
	//Voici un exemple de ce qu'on aurait pu faire : 
	
	synchronized public void sendAllClients(String msg) {
		PrintWriter out;
		for(int i = 0; i < vectClients.size(); i++) {
			out = (PrintWriter) vectClients.elementAt(i); //On cast le client num�ro i du vecteur des clients en printwriter (puisque nous, l'admin, on sait que ce vecteur contiendra des PrintWriter)
			if (out!=null) {
				out.print(msg);
				out.flush();
			}
		}
	
	//Reminder pour la partie connect qui sera donc dans une autre classe :
	//La classe du socket serveur n'est pas la m�me que la classe du socket client...
	//A ce niveau python est plus simple car il n'a qu'un seule socket pour chaque c�t�. Socket simple pour le client, ServerSocket pour serveur en java.

	
	}
	public static void main(Integer args[]) {
		ServeurFALC serveurFALC = new ServeurFALC();
		try {
			int port;
			if(args.length<=0) port = 8080;
			else port = args[0]; //Par d�faut sans argument �a sera le port 8080. Sinon l'argument pass� � main.
						
			ServerSocket serverSocket = new ServerSocket(port);
			//Attention : un resource leak est signal� ici : celui qui fermera la connexion n'est pas le serveur mais le client. Cet avertissement est normal... en fonctionnement normal.
			
			while(true) {
				//On bloquera ici en attente d'une connexion. 
				new ServeurFALCThread(serverSocket.accept(),serveurFALC);
				//D�s qu'un client se connecte, un nouveau thread est d�marr� (cf ServeurFALCThread)
				//On peut afficher l'adresse IP du client gr�ce au code ci-dessous (on n'accepte qu'une seule fois cependant, attention !
				//String clientAddr = socket.getRemoteSocketAddress().toString();
		        //System.out.println("connection from " + clientAddr); //Affichage du client
			} 
		}
		catch(Exception e) {
		}
	}
}
