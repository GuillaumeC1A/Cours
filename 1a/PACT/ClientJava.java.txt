import java.io.PrintWriter;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.Socket;
import java.util.Scanner;

public class ClientFALC {
    public static void main(String[] args) {

        String msg;
        Scanner scanner = new Scanner(System.in); //Scanne pour récupérer le texte en entrée, dans la CONSOLE.
        try{
            Socket soc = new Socket("localhost",8080); //Création de la socket
            PrintWriter wOut = new PrintWriter(soc.getOutputStream()); //écrire dans wOut pour écrire dans la socket, rOut lira les octets reçus
            BufferedReader rOut = new BufferedReader(
                new InputStreamReader(soc.getInputStream())
            );
            System.out.print(">>> ");
            msg = scanner.nextLine();
            while (!msg.equals("stop")){
                // on écrit dans la socket, et on flush pour envoyer les données
                wOut.write(msg+'\n');
                wOut.flush();
                //On peut tester et lire l'écho du serveur
                msg = rOut.readLine();
                System.out.println(msg);
                System.out.print(">>> ");
                msg = scanner.nextLine();
            }
            //On n'oublie pas de tout fermer
            wOut.close();
            rOut.close();
            soc.close();
        }catch(Exception e){
            e.printStackTrace();
        }
	}
}
