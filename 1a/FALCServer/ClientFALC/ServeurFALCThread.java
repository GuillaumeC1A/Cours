package ClientFALC;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.SocketAddress;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import PythonCaller;

//Pour faire des threads, l'une des façons de faire en java est d'implémenter Runnable.
//Il y aura autant d'instances de cette classe (i.e. autant de Threads) que de clients connectés, c'est le principe de multithreading.

class serveurFALCThread implements Runnable {
	
	//Quelques variables qui seront propres à chaque thread, ou plutôt à chaque client.
	//Avoir un attribut sur serveurFALC est indispensable pour utiliser ses classes convenablement.
	
	private Thread thread;
	private Socket socket;
	private PrintWriter out;
	private BufferedReader in;
	private ServeurFALC serveurFALC; 
	
	//Here une variable pour l'envoi des putains d'images...private ??? outImage
	//Here une autre variable pour la lecture des putains d'images... ??? readImage
	//Here une autre variable pour la taille de l'image quand on l'enverra... ??? sizeImage
	//Un wrapper ? 
	
	private SocketAddress getClientAddr() {
		return socket.getRemoteSocketAddress();
	}
	
	//Pas indispensable, mais on peut ajouter un numéro de client unique à chacun :
	private int numClient = 0;

	//Le constructeur dont se servira la classe ALC : 
	serveurFALCThread(Socket socket, ServeurFALC serveurFALC) {
		this.serveurFALC = serveurFALC; //Récupération du global.
		this.socket = socket; //Donné par serverSocket.accept()
		try {
			out = new PrintWriter(socket.getOutputStream()); 
			/*C'est dans out que l'on écrira pour envoyer les data back au serveur.
			* On l'utilisera pour retour 1 (texte modifié), 
			*		 			  retour 2 (mots clés), 
			*		 			  retour 3 (synonymes de ces mots-clés) 
			*		     	   et retour 4 (images)*/
			in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			//Initialiser les autres attributs notamment pour l'envoi des images !
			numClient = serveurFALC.addClient(out);
		} catch (Exception e) {}
		thread = new Thread(this);
		thread.start(); //On lance le thread ! De là le client sera géré indépendamment; 
	}
	//La méthode suivante qu'on va Override, run, est exécéutée au lancement du thread.
	//Pour rappel, nous fonctionnons en mode manuel pour PAN4 avec comme mode automatique
	//le mode manuel en cliquant simplement sur OK à chaque étape tout bêtement.
	//Cette méthode doit faire les choses suivantes : 
	//Réceptionner le "colis" du client, càd texte + keywords
	//Renvoyer une seconde simplification pour évaluation
	//Renvoyer les keywords pour évaluation
	//Envoyer les synonymes - simples - des keywords précédents pour évaluation
	//Envoyer les images pour évaluation
	//Envoyer tout le package pour construction du pdf sur place.
	      
	@Override
	public void run() { 
		
		//A few initializations...
		String recu = "";      
        String text = "";
    	String simpleText = "";
    	String choices = "";
		ArrayList<String> keywords = new ArrayList<String>();
		BufferedReader rOut = new BufferedReader(
	            new InputStreamReader(socket.getInputStream(), StandardCharsets.UTF_8));
		BufferedWriter wOut = new BufferedWriter(
				new OutputStreamWriter(socket.getOutputStream(), StandardCharsets.UTF_8));
		//A mettre encore toutes les variables qui permettront le renvoi des images... et la réception des selectors, ie des ratings...
		//Update : pas besoin car ce sera tout en String let's GO.
		
		System.out.println("Traitement du client "+numClient);
        System.out.println("Mots-clés reçus, on passe à l'étape de simplification");
		/**
		 * Ici est la partie Réception du texte initial et des mots-clés identifiés.
		 * Une fois la réception terminée, le client va commencer à attendre le retour du serveur pour la simplification supervisée.
		 * ETAPE 0 CI-DESSOUS : Réception TEXTE, Renvoi TEXTE.
		 */
	
		try {
			recu = rOut.readLine();
		} catch (IOException e2) {
			// TODO Auto-generated catch block
			e2.printStackTrace();
		}
        System.out.println("Réception du texte en cours depuis ; " + getClientAddr());
        System.out.println(recu);
        while (recu.compareTo("####ENDSENDTEXT####")!=0){
        	text.concat(recu);
          try{
       		recu = rOut.readLine();
          } catch(Exception e){
            e.printStackTrace();
            System.out.println("Rien envoyé");
          }

        }
        try {
			recu = rOut.readLine();
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		} //Pour passer le token de fin de texte.
        
        
        
        //ICI COMMENCE LE MODULE 1 - RESUME + MOTS CLES 
        
		FalcAppModel model = this.falcApp.getFalcApp().getFalcAppModel();
	
		model.writeInFile("falc/data/texte.txt", this.falcApp.getWritePanel().getJTextArea().getText());
		
		String[] cmd = {"python", "falc/code/main.py", "falc/data/texte.txt", "test.pdf", "0.5", "0.1"};
		
		model.runTraductionHelp(cmd);
		
		String keywords = model.getTextFromFile("falc/data/keywords.txt");
		
		String summary = model.getTextFromFile("falc/data/resume.txt");
		
		this.clientFalc.sendFALC(summary, keywords);
		
		
		String[] cmd2 = {"python", "falc/code/WriteInPdf.py", "falc/data/resume.txt", "images/", "hist/"+ writeFrame.getWritePanel().getJTextField().getText()};

		model.runTraductionHelp(cmd2);
		
		model.setCurrentFile("hist/" + falcApp.getWritePanel().getJTextField().getText() +"_FINAL.pdf");
		
        
        /*System.out.println("Réception du texte terminée, réception des mots-clés en cours...");
        while ((recu.compareTo("####ENDSENDKEYS####")!=0)){
          System.out.println(recu);
          keywords.add(recu); //On ajoute les mots un par un à l'arraylist des keywords.
          try {
        	  recu = rOut.readLine();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        }
        System.out.println("Mots-clés reçus, on passe à l'étape de simplification");
        */
        /**
         * ETAPE 0 TERMINEE - Si elle n'était pas faite en local, déjà... - Les modules de simplification (Clément, Maxime, Clara?) entrent en jeu ici. 
         * IL FAUT INSERER ICI LA PARTIE RUN DE CES MODULES PRECEDENTS.
         * ETAPE 1 CI-DESSOUS : Envoi TEXTE, Réception TEXTE. 
         */
        
        //On supposera l'existence d'une variable String simpleSendText contenant le texte simplifié par la première étape.
        //Bien évidemment toute opération ici a son miroir chez le client et vice-versa. Un write puis flush aura comme complémentaire un read ou readLine avec contrôle du token.
        String simpleSendText = "";
        try {
        	wOut.write(simpleSendText + '\n');
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} //Pour le readLine à l'arrivée. 
        try {
			wOut.write("####STEP1####\n");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} //Token de contrôle encore.
        try {
			wOut.flush();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        
        //Partie réception pour correction grammaticale : 
        
        System.out.println("Réception étape grammaticale depuis ; " + getClientAddr());
        recu = rOut.readLine();
        //System.out.println(recu); 
        while (recu.compareTo("####ENDSTEP1####")!=0){
        	text.concat(recu);
          try{
           	recu = rOut.readLine();
          } catch(Exception e){
            e.printStackTrace();
            System.out.println("Rien envoyé étape 1");
          }
        }
        try {
			recu = rOut.readLine();
        } catch (IOException e1) {
        	// TODO Auto-generated catch block
        	e1.printStackTrace();
        } //Pour passer le token de fin de texte.
        
        System.out.println("Etape 1 bis : mots-clés en cours...");
        /**
         * ETAPE 1 TERMINEE -
         * IL FAUT CONTINUER A INSERER LA PARTIE RUN DES MODULES SUS-NOMMES.
         * ETAPE 2 CI-DESSOUS : Envoi KEYWORDS, Réception KEYWORDS 
         */
        
        //On supposera l'existence d'une variable ArrayList<String>, on pourrait aussi imaginer une String[] mais ça semble moins intéressant.
        //A nouveau il semblerait que les keywords aient déjà été identifiés par la partie locale...
        //En fait il semble que la première partie fait résumé et que la première bis fait simplif du résumé... ? Voir demain
        
        ArrayList<String> keywordsToSend = new ArrayList<String>();
        for(int i = 0; i < keywordsToSend.size(); i++) {
			try {
			wOut.write(keywordsToSend.get(i)+"\n");
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} 
        }//Peut-être flush à chaque tour même si ça consomme plus, pour la taille du buffer à envoyer. 
        try {
        	wOut.write("####STEP2####\n");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}   //Même si pour le coup on arrivait à envoyer des images donc ça devrait le faire.
        try {
			wOut.flush();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        
        //Partie réception
        
            System.out.println("Réception étape mots-clés depuis ; " + getClientAddr());
            //System.out.println(recu); 
            recu = rOut.readLine();
            while (recu.compareTo("####ENDSTEP2####")!=0){ //Réception d'une ArrayList<String> mot par mot
            	keywords.add(recu);
              try{
               	recu = rOut.readLine();
              } catch(Exception e){
                e.printStackTrace();
                System.out.println("Rien envoyé étape 2");
              }  
            }
            try {
    			recu = rOut.readLine();
            } catch (IOException e1) {
            	// TODO Auto-generated catch block
            	e1.printStackTrace();
            } //Pour passer le token de fin de keywords.
            
            System.out.println("Etape 2 bis : mots-clés en cours...");
        
        /**
         * ETAPE 2 TERMINEE -
         * IL FAUT CONTINUER A INSERER LA PARTIE RUN DES MODULES SUS-NOMMES.
         * ETAPE 3 CI-DESSOUS : Envoi SYNONYMES, Réception SYNONYMES  (String)
         */
        
        //Pour cette étape c'est un peu tricky : on va supposer l'existence d'une variable ArrayList<String> PAR mot dont on s'intéresse aux synonymes.
        //Cela peut se faire en ArrayList<ArrayList<String>> avec le premier de chaque ArrayList interne étant le mot à "synonymiser" et les suivants ses synonymes potentiels.
        
        Synonymie s = new Synonymie("in.txt");
        String propositions = s.finalPropositionsToString();
        try {
        wOut.write(propositions+'\n'); //On déconstruit l'objet en string qui sera reconstruit chez le client en userSynonymie.
        } catch (IOException e) {}
        try {
        wOut.write("####STEP3####"); //Jeton pour indiquer la fin de l'étape tout entière. Le dernier synonyme du dernier mot ne sera pas suivi d'un autre mot. Le test compareTo ENDSYN au début après réception du NEXTWORD arrêtera cette étape pour le client.
        wOut.flush();
        } catch (IOException e) {
        	e.printStackTrace();
        }
        recu = rOut.readLine();
      	System.out.println("Réception étape synonymes depuis ; " + getClientAddr());
        //System.out.println(recu); 
        while (recu.compareTo("####ENDSTEP3####")!=0) {
         	choices.concat(recu); //Normalement on ne reçoit qu'une seule String à chaque fois. Donc cette boucle ne ferait qu'un seul tour par fonctionnement.
            try{
           	recu = rOut.readLine();
            } catch(Exception e){
            e.printStackTrace();
            System.out.println("Rien envoyé étape 3");
            }
              
            }
            try {
    			recu = rOut.readLine();
            } catch (IOException e1) {
            	// TODO Auto-generated catch block
            	e1.printStackTrace();
            } //Pour passer le token de fin de synonymes.
            
            System.out.println("Etape 3 bis : intégration des images en cours...");
            s.stringToUserChoices(choices);
            s.treatUserChoice();
        
        /**
         * ETAPE 3 TERMINEE -
         * IL FAUT INSERER ICI LA PARTIE TRAITANT LA SELECTION DES IMAGES PUIS LA CONSTITUTION DU DOSSIER A ENVOYER.
         * COTE CLIENT IL FAUT GERER LA CREATION DU DOSSIER DANS LES FICHIERS DE L'APPLICATION ET LEUR SUPPRESSION IN FINE APRES FABRICATION DU PDF.
         * ETAPE 4 CI-DESSOUS : Envoi IMAGES, Réception REFERENCES AUX IMAGES
         */
        
        System.out.println("Parties textuelles traitées, début de l'envoi des liens images à l'utilisateur");
        
        //On supposera qu'on a un ArrayList<String> qui contient les URL vers les images. 
        ArrayList<String> urls = new ArrayList<String>();
        urls.add("C:\\Users\\Guillaume\\Desktop\\dossier photo esp\\Drapeaux\\DOMINICA.png"); 
        urls.add("C:\\Users\\Guillaume\\Desktop\\dossier photo esp\\Drapeaux\\STVICENTE.png"); //Pour tests whitebox, on va s'envoyer des drapeaux d'un dossier à l'autre... en url cette fois.
        urls.add("C:\\Users\\Guillaume\\Desktop\\dossier photo esp\\Drapeaux\\1France.png");
        for(int i = 0; i < urls.size(); i++) {
			try {
				wOut.write(urls.get(i)+'\n');
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
        }//Peut-être flush à chaque tour même si ça consomme plus, pour la taille du buffer à envoyer. 
        try {
			wOut.write("####STEP4####\n");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}                                                         //Même si pour le coup on arrive à envoyer des images donc ça devrait le faire.
        try {
			wOut.flush();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        
        //Trucs ici Maxime comme le synonymie finalPropositionsToString();
       
        /**
         * ETAPE 4 TERMINEE -
         * NE RESTE PLUS QU'A TOUT RENVOYER ET LAISSER LE CLIENT FINIR DE FABRIQUER SON PDF.
         * LA FERMETURE DU SOCKET EST FAITE PAR LE CLIENT ET NON PAR LE SERVEUR.
         * Les retours sont importants mais juste pour l'apprentissage : le client a ses URL à l'étape 4 et son texte lui sera renvoyé (même s'il est en théorie complétable depuis étape 3) étape 5
         * ETAPE 5 CI-DESSOUS : Envoi IMAGES, Envoi TEXTE, Fermeture socket. 
         * ETAPE 5 : INUTILE DE RENVOYER CE QUI EST DEJA SUR PLACE
         */
        
        String simpleFinalText = "";
        try {
        	wOut.write(simpleFinalText + '\n');
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        try {
        	wOut.write("####STEP5####\n");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} //Le client aura déjà les URL on lui renvoie juste le texte avec le remplacement fait des synonymes je sais pas trop où.
        try {
        	wOut.flush();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        
        /**
         * ETAPE 5 TERMINEE - 
         * Fermeture de tout ce qui doit être fermé (type Stream, Reader...)
         * Fermeture du thread.
         */
        
       System.out.println("Les images ont été sélectionnées par le client, le texte simplifié final a été envoyé : Fin du Thread");
       
       	try {
        wOut.close();
        rOut.close();
       	} catch (IOException e) {}
       	finally {
		try {
			//C'est la déconnexion du client qui fera arriver le Thread à cet endroit. Normalement, cela coïncide également avec la fin du run.
			System.out.println("Le client s'est déconnecté");
			serveurFALC.remClient(numClient);
			socket.close(); //Normalement déjà fermé à cause de l'exception levée menant au finally.
		} catch (IOException e) {}
    
	}//run { }
	
	}
}//classBody { }

/* Poubelle non utilisée : on n'envoie pas des images mais des URL ça prend moins de place et c'est l'utilisateur qui les téléchargera. 
 * OutputStream outputStream = socket.getOutputStream();
        ByteArrayOutputStream bytesOut = new ByteArrayOutputStream();
        byte[] size;
        int i = 0;
        ArrayList<String> imgLocations = new ArrayList<String>();
        
        //Pour des tests en local, je vais m'envoyer des drapeaux d'un dossier à l'autre
        
        imgLocations.add("C:\\Users\\Guillaume\\Desktop\\dossier photo esp\\Drapeaux\\DOMINICA.png");
        imgLocations.add("C:\\Users\\Guillaume\\Desktop\\dossier photo esp\\Drapeaux\\STVICENTE.png");
        imgLocations.add("C:\\Users\\Guillaume\\Desktop\\dossier photo esp\\Drapeaux\\1France.png");
        
        //Cette ArrayList contient les chemins d'accès aux images qui devront être envoyées (sous la forme C:\\Users\\Me\\Desktop\\AuroraBorealis.png)
        
        for(String loc : imgLocations) try {
        	System.out.println(loc);
        	BufferedImage image = ImageIO.read(new File(loc));
        	//Un problème est encore non résolu : pour 2 fichiers ou plus, image devient null à un moment donné entre le départ et l'arrivée.
        	//Ce qui est surprenant, c'est que le pathfile est bien bon, le fonctionnement et les boucles tournent également, le inputstream lit ce qu'il faut à l'arrivée...
        	//Le problème semble venir de la classe ImageIO qui lit toujours depuis le début la chaîne d'octets entrante. Mais même après flush rien ne fonctionne. 
        	ImageIO.write(image, "png", bytesOut);
        	FileOutputStream sortie = new FileOutputStream(new File("mon fichier.txt"));
        	sortie.write(bytesOut.toByteArray());
        	sortie.close();
            size = ByteBuffer.allocate(4).putInt(bytesOut.size()).array();
            System.out.println(size);
            outputStream.write(size);
            outputStream.write(bytesOut.toByteArray()); //write prendra en argument un byte array mais pas un ByteArrayOutputStream.
            //Dans l'ordre, la taille va arriver d'abord et on recevra correctement les bits correspondant à l'image pour la reconstruire.
            System.out.println("Envoi de l'image "+i+" : "+System.currentTimeMillis()); //La commande System.currentTimeMillis() pour estimer la vitesse.
            outputStream.flush();   
            i++;
        } catch(IOException e) {
        }
        
        //Pour envoyer des images en TCP, ce qui se fait de plus courant est d'abord d'envoyer la taille de l'image qui va être reçue
        //avant de l'envoyer elle-même. On va vouloir envoyer des byteArray dont les premiers (poids faible) contiennent la taille. 
        //Pour les images, on va directement travailler sur le stream avec les bytes. Plus près de la machine.
        */

/* Poubelle non utilisée : on n'utilisera pas de fichier txt dans lequel on écrira, juste des ArrayList de String qui seront des 'pointeurs' vers un peu tout et n'importe quoi.
 * 
      	File fileDir = new File("C:\\Users\\Guillaume\\Desktop\\dossier photo esp\\Drapeaux\\in.txt");
		
   		try(FileOutputStream fos = new FileOutputStream(fileDir);
   			OutputStreamWriter osw = new OutputStreamWriter(fos,"UTF8");
   			Writer out = new BufferedWriter(osw);) {	

   			out.append(text);
    			
   		}catch(UnsupportedEncodingException e) {e.printStackTrace();}
   		 catch(IOException e)				   {e.printStackTrace();}
   		 catch(Exception e)  				   {e.printStackTrace();}
   		
    	//simpleText = text.simplify(); Pour simplifier
        //Ecrire dans in.txt
        //Récupérer dans out.t
        //création du dossier des images
   		
   		File fileOut = new File("C:\\Users\\Guillaume\\Desktop\\dossier photo esp\\Drapeaux\\out.txt");
		
		try(FileReader fileReader = new FileReader(fileOut);
			BufferedReader reader = new BufferedReader(fileReader);){
            	 
			String line = reader.readLine();

			while(line != null) {

					simpleText = simpleText + line;	

					line = reader.readLine();					 
				}		 
			
        } 
		  catch(FileNotFoundException e) { e.printStackTrace();;}
		  catch(IOException e) 			 { e.printStackTrace();;}
		  */

