package ClientFALC;

import java.io.PrintWriter;
import java.io.Reader;
import java.awt.image.BufferedImage;
import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;

import javax.imageio.ImageIO;

import java.io.StringReader;

public class ClientFALC {
	
	
    public static void main(String[] args){
    	String text = "Le chat qui joue avec cette balle ovale est marron comme les feuilles d'automne";
    	String simpleText = "";
    	String keywords = "chat balle joue marron";
        String servMsg;
        Scanner scanner = new Scanner(System.in);
        try {
            Socket clisoc = new Socket("localhost",11111); //Cr�ation de la socket c�t� client (� la diff de python, c'est pas la m�me pour le client et le serv)
            PrintWriter wOut = new PrintWriter(clisoc.getOutputStream()); //�crire dans wOut pour �crire dans la socket, rOut lira les octets re�us
            BufferedReader rOut = new BufferedReader(new InputStreamReader(clisoc.getInputStream()));
            StringReader rKeys = new StringReader(keywords);
            //On commence l'envoi des donn�es une fois la connexion �tablie
            System.out.println("D�but de l'envoi du texte au serveur");
            wOut.write(text + "\n"); //le '\n' est indispensable au bon fonctionnement du readLine � l'arriv�e.
            wOut.flush(); //Premier "commit" du texte (pour le contexte)
            wOut.write("####ENDSENDTEXT####\n");
            wOut.flush();
            System.out.println("D�but de l'envoi des mots-cl�s");
            int caract = rKeys.read(); 
            while(caract != -1) {
            	if(caract != ' ') {
            		wOut.write(Character.toString(caract));
            	}
            	else {
            		wOut.write("\n");
            		wOut.flush();
            		}
            	caract = rKeys.read(); 
            }
            wOut.write("\n");
            wOut.flush(); //Pour le dernier mot-cl� qui pourrait ne pas avoir d'espace apr�s lui dans la string
            wOut.write("####ENDSENDKEYS####\n");
            wOut.flush();
            
            System.out.println("Toutes les informations n�cessaires � la simplification sont parties, on attend le retour du serveur.");
       
            /** A partir d'ici, tous les mots-cl�s et le texte ont �t� envoy�s, et on attend le retour du serveur;
             *  Il a �t� choisi de renvoyer dans l'ordre le texte simplifi� puis les images associ�es identifi�es.
             *  Il faut donc faire deux parties de renvoi : une partie pour le texte qui va �tre exactement la m�me que dans l'autre sens,
             *  et une partie images que l'on va voir juste apr�s.
             */            
            
            //Partie texte : on refait la m�me mais dans l'autre sens ! On utilise la m�me socket et on suppose que le texte 
            //sera dans une variable simpleText de type String comme convenu pr�alablement. 
 
            System.out.println("D�but de r�ception du texte simplifi�");
            servMsg = rOut.readLine();
            System.out.println(servMsg);
            while (servMsg.compareTo("####ENDBACKSTXT####")!=0){
            	simpleText.concat(servMsg);
              try{
                	servMsg = rOut.readLine();
              } catch(Exception e){
                e.printStackTrace();
                System.out.println("Rien envoy�");
              }

            }
            //servMsg = rOut.readLine();
            //Peut-�tre il va y avoir des conflits entre les inputstreamreader et les inputstream.read
            //Le passage de l'un � l'autre dans la socket ne se fera pas forc�ment bien
            //par exemple l'initialisation du inputstream.read se fera-t-elle au d�part, sur le dernier lu? 
            
            System.out.println("R�ception du texte termin�e, r�ception des images en cours...");
            int i=0;
            InputStream inputStream = clisoc.getInputStream();
            int size; //Contiendra la taille des images (sizeRaw en bits, size en utilisable, en "normal")
            //On prend par convention les 4 premiers octets pour la taille de l'image 
            //Pour information java utilisera en gros pour optimiser 3 ou 4 octets mais rien entre les deux. 3 octets codent jusqu'� 16Mo.
            //C'est du d�tail, mais voil� pourquoi, par s�ret�, on en prend un de plus.
            //Au d�part on a utilis� un StreamOutput pour les images, donc idem � l'arriv�e pour r�ceptionner les bytes
            //Les images seront contenues dans un dossier et seront t�l�charg�es � l'arriv�e dans un autre dossier. 
            
            int offset = 4;
            
            while(!clisoc.isClosed()) { //Pour tout le reste de la connexion, c�d tant que le serveur n'a pas fini d'envoyer
            	TimeUnit.SECONDS.sleep(3);
            	byte[] rawInput = inputStream.readAllBytes(); //Gr�ce � getInt qui avance pile de 4 pour lire le contenu on ne devrait m�me plus avoir besoin de rawSize.
            	ByteBuffer byteBuffer = ByteBuffer.wrap(rawInput);
            	while(true) {
            		size = byteBuffer.getInt();
            		System.out.println(byteBuffer.position());
            		System.out.println(size);
            		//inputStream.mark(size);
            		//Par contre imageRaw et image seront cr��es ici uniquement car la taille d�pend de size qui change � chaque tour.
            		byte[] imageRaw = new byte[size]; //Comme justement illustr� ici.
                    byteBuffer.position(offset);
            		byteBuffer.get(imageRaw);
            		//I just don't get it, everything seems fine. I take the four first bytes, read them, create a window just large enough to save the pic, and repeat, yet I get nullPointerException AND that strange pic duplicata.
            		//On lit le flux entrant et on le stocke dans imageRaw avant de transformer l'array en vraie image � travers ImageIO.read
            		//Attention : ce n'est pas read(imageRaw, offset, size + OFFSET car �a va d�j� de offset � size+offset sans le pr�ciser. En gros �a d�borderait.
            		BufferedImage image = null;
            		ByteArrayInputStream based = new ByteArrayInputStream(imageRaw); //Il faut r�initialiser le ByteArrayInputStream � chaque fois car ImageIO fermera le stream � chaque fois. 
            		image = ImageIO.read(based);
            		//Le probl�me peut venir du fait qu'il nous faut plusieurs readers.
            		System.out.println("Re�u l'image "+i+" : "+image.getHeight()+"x"+image.getWidth());
            		File fichierImage = new File("C:\\Users\\Guillaume\\Desktop\\dossier photo esp\\DrapeauxArrivee\\image"+i+".png"); 
            		//Sp�cification du chemin d'acc�s vers le dossier dans lequel on devra enregistrer l'image !
            		ImageIO.write(image, "PNG", fichierImage); //Op�ration d'enregistrement ici
            		i++; //Cette incr�mentation anodine permet en fait de cr�er autant de fichier dont on aura besoin. Si le fichier existe d�j�, on �crira par-dessus.
            		//Pas besoin alors de syst�me de vidage puisqu'on r�utilise les "emplacements" pr�c�dents. 
            		//Maintenant on enregistre l'image dans un dossier de l'application pour reconstruire le pdf :
            		//System.out.wait(1000);
            		//inputStream.mark(ByteBuffer.wrap(imageRaw).asIntBuffer().get());
            		//byteBuffer.position(byteBuffer.position()+size);
            		offset += 4 + size;
            		based.read();
            		image.flush();    
            		based.close();
            	}
            }
        wOut.close();
        rOut.close();
        clisoc.close();
        }catch(Exception e){
            e.printStackTrace();
        }
	}
}
