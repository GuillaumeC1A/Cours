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
            Socket clisoc = new Socket("localhost",11111); //Création de la socket côté client (à la diff de python, c'est pas la même pour le client et le serv)
            PrintWriter wOut = new PrintWriter(clisoc.getOutputStream()); //écrire dans wOut pour écrire dans la socket, rOut lira les octets reçus
            BufferedReader rOut = new BufferedReader(new InputStreamReader(clisoc.getInputStream()));
            StringReader rKeys = new StringReader(keywords);
            //On commence l'envoi des données une fois la connexion établie
            System.out.println("Début de l'envoi du texte au serveur");
            wOut.write(text + "\n"); //le '\n' est indispensable au bon fonctionnement du readLine à l'arrivée.
            wOut.flush(); //Premier "commit" du texte (pour le contexte)
            wOut.write("####ENDSENDTEXT####\n");
            wOut.flush();
            System.out.println("Début de l'envoi des mots-clés");
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
            wOut.flush(); //Pour le dernier mot-clé qui pourrait ne pas avoir d'espace après lui dans la string
            wOut.write("####ENDSENDKEYS####\n");
            wOut.flush();
            
            System.out.println("Toutes les informations nécessaires à la simplification sont parties, on attend le retour du serveur.");
       
            /** A partir d'ici, tous les mots-clés et le texte ont été envoyés, et on attend le retour du serveur;
             *  Il a été choisi de renvoyer dans l'ordre le texte simplifié puis les images associées identifiées.
             *  Il faut donc faire deux parties de renvoi : une partie pour le texte qui va être exactement la même que dans l'autre sens,
             *  et une partie images que l'on va voir juste après.
             */            
            
            //Partie texte : on refait la même mais dans l'autre sens ! On utilise la même socket et on suppose que le texte 
            //sera dans une variable simpleText de type String comme convenu préalablement. 
 
            System.out.println("Début de réception du texte simplifié");
            servMsg = rOut.readLine();
            System.out.println(servMsg);
            while (servMsg.compareTo("####ENDBACKSTXT####")!=0){
            	simpleText.concat(servMsg);
              try{
                	servMsg = rOut.readLine();
              } catch(Exception e){
                e.printStackTrace();
                System.out.println("Rien envoyé");
              }

            }
            //servMsg = rOut.readLine();
            //Peut-être il va y avoir des conflits entre les inputstreamreader et les inputstream.read
            //Le passage de l'un à l'autre dans la socket ne se fera pas forcément bien
            //par exemple l'initialisation du inputstream.read se fera-t-elle au départ, sur le dernier lu? 
            
            System.out.println("Réception du texte terminée, réception des images en cours...");
            int i=0;
            InputStream inputStream = clisoc.getInputStream();
            int size; //Contiendra la taille des images (sizeRaw en bits, size en utilisable, en "normal")
            //On prend par convention les 4 premiers octets pour la taille de l'image 
            //Pour information java utilisera en gros pour optimiser 3 ou 4 octets mais rien entre les deux. 3 octets codent jusqu'à 16Mo.
            //C'est du détail, mais voilà pourquoi, par sûreté, on en prend un de plus.
            //Au départ on a utilisé un StreamOutput pour les images, donc idem à l'arrivée pour réceptionner les bytes
            //Les images seront contenues dans un dossier et seront téléchargées à l'arrivée dans un autre dossier. 
            
            int offset = 4;
            
            while(!clisoc.isClosed()) { //Pour tout le reste de la connexion, càd tant que le serveur n'a pas fini d'envoyer
            	TimeUnit.SECONDS.sleep(3);
            	byte[] rawInput = inputStream.readAllBytes(); //Grâce à getInt qui avance pile de 4 pour lire le contenu on ne devrait même plus avoir besoin de rawSize.
            	ByteBuffer byteBuffer = ByteBuffer.wrap(rawInput);
            	while(true) {
            		size = byteBuffer.getInt();
            		System.out.println(byteBuffer.position());
            		System.out.println(size);
            		//inputStream.mark(size);
            		//Par contre imageRaw et image seront créées ici uniquement car la taille dépend de size qui change à chaque tour.
            		byte[] imageRaw = new byte[size]; //Comme justement illustré ici.
                    byteBuffer.position(offset);
            		byteBuffer.get(imageRaw);
            		//I just don't get it, everything seems fine. I take the four first bytes, read them, create a window just large enough to save the pic, and repeat, yet I get nullPointerException AND that strange pic duplicata.
            		//On lit le flux entrant et on le stocke dans imageRaw avant de transformer l'array en vraie image à travers ImageIO.read
            		//Attention : ce n'est pas read(imageRaw, offset, size + OFFSET car ça va déjà de offset à size+offset sans le préciser. En gros ça déborderait.
            		BufferedImage image = null;
            		ByteArrayInputStream based = new ByteArrayInputStream(imageRaw); //Il faut réinitialiser le ByteArrayInputStream à chaque fois car ImageIO fermera le stream à chaque fois. 
            		image = ImageIO.read(based);
            		//Le problème peut venir du fait qu'il nous faut plusieurs readers.
            		System.out.println("Reçu l'image "+i+" : "+image.getHeight()+"x"+image.getWidth());
            		File fichierImage = new File("C:\\Users\\Guillaume\\Desktop\\dossier photo esp\\DrapeauxArrivee\\image"+i+".png"); 
            		//Spécification du chemin d'accès vers le dossier dans lequel on devra enregistrer l'image !
            		ImageIO.write(image, "PNG", fichierImage); //Opération d'enregistrement ici
            		i++; //Cette incrémentation anodine permet en fait de créer autant de fichier dont on aura besoin. Si le fichier existe déjà, on écrira par-dessus.
            		//Pas besoin alors de système de vidage puisqu'on réutilise les "emplacements" précédents. 
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
