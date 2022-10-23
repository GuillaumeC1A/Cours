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

//Pour faire des threads, l'une des fa�ons de faire en java est d'impl�menter Runnable.
//Il y aura autant d'instances de cette classe (i.e. autant de Threads) que de clients connect�s, c'est le principe de multithreading.

class serveurFALCThread implements Runnable {
	
	//Quelques variables qui seront propres � chaque thread, ou plut�t � chaque client.
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
	
	//Pas indispensable, mais on peut ajouter un num�ro de client unique � chacun :
	private int numClient = 0;

	//Le constructeur dont se servira la classe ALC : 
	serveurFALCThread(Socket socket, ServeurFALC serveurFALC) {
		this.serveurFALC = serveurFALC; //R�cup�ration du global.
		this.socket = socket; //Donn� par serverSocket.accept()
		try {
			out = new PrintWriter(socket.getOutputStream()); 
			/*C'est dans out que l'on �crira pour envoyer les data back au serveur.
			* On l'utilisera pour retour 1 (texte modifi�), 
			*		 			  retour 2 (mots cl�s), 
			*		 			  retour 3 (synonymes de ces mots-cl�s) 
			*		     	   et retour 4 (images)*/
			in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			//Initialiser les autres attributs notamment pour l'envoi des images !
			numClient = serveurFALC.addClient(out);
		} catch (Exception e) {}
		thread = new Thread(this);
		thread.start(); //On lance le thread ! De l� le client sera g�r� ind�pendamment; 
	}
	//La m�thode suivante qu'on va Override, run, est ex�c�ut�e au lancement du thread.
	//Pour rappel, nous fonctionnons en mode manuel pour PAN4 avec comme mode automatique
	//le mode manuel en cliquant simplement sur OK � chaque �tape tout b�tement.
	//Cette m�thode doit faire les choses suivantes : 
	//R�ceptionner le "colis" du client, c�d texte + keywords
	//Renvoyer une seconde simplification pour �valuation
	//Renvoyer les keywords pour �valuation
	//Envoyer les synonymes - simples - des keywords pr�c�dents pour �valuation
	//Envoyer les images pour �valuation
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
		//A mettre encore toutes les variables qui permettront le renvoi des images... et la r�ception des selectors, ie des ratings...
		//Update : pas besoin car ce sera tout en String let's GO.
		
		System.out.println("Traitement du client "+numClient);
        System.out.println("Mots-cl�s re�us, on passe � l'�tape de simplification");
		/**
		 * Ici est la partie R�ception du texte initial et des mots-cl�s identifi�s.
		 * Une fois la r�ception termin�e, le client va commencer � attendre le retour du serveur pour la simplification supervis�e.
		 * ETAPE 0 CI-DESSOUS : R�ception TEXTE, Renvoi TEXTE.
		 */
	
		try {
			recu = rOut.readLine();
		} catch (IOException e2) {
			// TODO Auto-generated catch block
			e2.printStackTrace();
		}
        System.out.println("R�ception du texte en cours depuis ; " + getClientAddr());
        System.out.println(recu);
        while (recu.compareTo("####ENDSENDTEXT####")!=0){
        	text.concat(recu);
          try{
       		recu = rOut.readLine();
          } catch(Exception e){
            e.printStackTrace();
            System.out.println("Rien envoy�");
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
		
        
        /*System.out.println("R�ception du texte termin�e, r�ception des mots-cl�s en cours...");
        while ((recu.compareTo("####ENDSENDKEYS####")!=0)){
          System.out.println(recu);
          keywords.add(recu); //On ajoute les mots un par un � l'arraylist des keywords.
          try {
        	  recu = rOut.readLine();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        }
        System.out.println("Mots-cl�s re�us, on passe � l'�tape de simplification");
        */
        /**
         * ETAPE 0 TERMINEE - Si elle n'�tait pas faite en local, d�j�... - Les modules de simplification (Cl�ment, Maxime, Clara?) entrent en jeu ici. 
         * IL FAUT INSERER ICI LA PARTIE RUN DE CES MODULES PRECEDENTS.
         * ETAPE 1 CI-DESSOUS : Envoi TEXTE, R�ception TEXTE. 
         */
        
        //On supposera l'existence d'une variable String simpleSendText contenant le texte simplifi� par la premi�re �tape.
        //Bien �videmment toute op�ration ici a son miroir chez le client et vice-versa. Un write puis flush aura comme compl�mentaire un read ou readLine avec contr�le du token.
        String simpleSendText = "";
        try {
        	wOut.write(simpleSendText + '\n');
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} //Pour le readLine � l'arriv�e. 
        try {
			wOut.write("####STEP1####\n");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} //Token de contr�le encore.
        try {
			wOut.flush();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        
        //Partie r�ception pour correction grammaticale : 
        
        System.out.println("R�ception �tape grammaticale depuis ; " + getClientAddr());
        recu = rOut.readLine();
        //System.out.println(recu); 
        while (recu.compareTo("####ENDSTEP1####")!=0){
        	text.concat(recu);
          try{
           	recu = rOut.readLine();
          } catch(Exception e){
            e.printStackTrace();
            System.out.println("Rien envoy� �tape 1");
          }
        }
        try {
			recu = rOut.readLine();
        } catch (IOException e1) {
        	// TODO Auto-generated catch block
        	e1.printStackTrace();
        } //Pour passer le token de fin de texte.
        
        System.out.println("Etape 1 bis : mots-cl�s en cours...");
        /**
         * ETAPE 1 TERMINEE -
         * IL FAUT CONTINUER A INSERER LA PARTIE RUN DES MODULES SUS-NOMMES.
         * ETAPE 2 CI-DESSOUS : Envoi KEYWORDS, R�ception KEYWORDS 
         */
        
        //On supposera l'existence d'une variable ArrayList<String>, on pourrait aussi imaginer une String[] mais �a semble moins int�ressant.
        //A nouveau il semblerait que les keywords aient d�j� �t� identifi�s par la partie locale...
        //En fait il semble que la premi�re partie fait r�sum� et que la premi�re bis fait simplif du r�sum�... ? Voir demain
        
        ArrayList<String> keywordsToSend = new ArrayList<String>();
        for(int i = 0; i < keywordsToSend.size(); i++) {
			try {
			wOut.write(keywordsToSend.get(i)+"\n");
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} 
        }//Peut-�tre flush � chaque tour m�me si �a consomme plus, pour la taille du buffer � envoyer. 
        try {
        	wOut.write("####STEP2####\n");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}   //M�me si pour le coup on arrivait � envoyer des images donc �a devrait le faire.
        try {
			wOut.flush();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        
        //Partie r�ception
        
            System.out.println("R�ception �tape mots-cl�s depuis ; " + getClientAddr());
            //System.out.println(recu); 
            recu = rOut.readLine();
            while (recu.compareTo("####ENDSTEP2####")!=0){ //R�ception d'une ArrayList<String> mot par mot
            	keywords.add(recu);
              try{
               	recu = rOut.readLine();
              } catch(Exception e){
                e.printStackTrace();
                System.out.println("Rien envoy� �tape 2");
              }  
            }
            try {
    			recu = rOut.readLine();
            } catch (IOException e1) {
            	// TODO Auto-generated catch block
            	e1.printStackTrace();
            } //Pour passer le token de fin de keywords.
            
            System.out.println("Etape 2 bis : mots-cl�s en cours...");
        
        /**
         * ETAPE 2 TERMINEE -
         * IL FAUT CONTINUER A INSERER LA PARTIE RUN DES MODULES SUS-NOMMES.
         * ETAPE 3 CI-DESSOUS : Envoi SYNONYMES, R�ception SYNONYMES  (String)
         */
        
        //Pour cette �tape c'est un peu tricky : on va supposer l'existence d'une variable ArrayList<String> PAR mot dont on s'int�resse aux synonymes.
        //Cela peut se faire en ArrayList<ArrayList<String>> avec le premier de chaque ArrayList interne �tant le mot � "synonymiser" et les suivants ses synonymes potentiels.
        
        Synonymie s = new Synonymie("in.txt");
        String propositions = s.finalPropositionsToString();
        try {
        wOut.write(propositions+'\n'); //On d�construit l'objet en string qui sera reconstruit chez le client en userSynonymie.
        } catch (IOException e) {}
        try {
        wOut.write("####STEP3####"); //Jeton pour indiquer la fin de l'�tape tout enti�re. Le dernier synonyme du dernier mot ne sera pas suivi d'un autre mot. Le test compareTo ENDSYN au d�but apr�s r�ception du NEXTWORD arr�tera cette �tape pour le client.
        wOut.flush();
        } catch (IOException e) {
        	e.printStackTrace();
        }
        recu = rOut.readLine();
      	System.out.println("R�ception �tape synonymes depuis ; " + getClientAddr());
        //System.out.println(recu); 
        while (recu.compareTo("####ENDSTEP3####")!=0) {
         	choices.concat(recu); //Normalement on ne re�oit qu'une seule String � chaque fois. Donc cette boucle ne ferait qu'un seul tour par fonctionnement.
            try{
           	recu = rOut.readLine();
            } catch(Exception e){
            e.printStackTrace();
            System.out.println("Rien envoy� �tape 3");
            }
              
            }
            try {
    			recu = rOut.readLine();
            } catch (IOException e1) {
            	// TODO Auto-generated catch block
            	e1.printStackTrace();
            } //Pour passer le token de fin de synonymes.
            
            System.out.println("Etape 3 bis : int�gration des images en cours...");
            s.stringToUserChoices(choices);
            s.treatUserChoice();
        
        /**
         * ETAPE 3 TERMINEE -
         * IL FAUT INSERER ICI LA PARTIE TRAITANT LA SELECTION DES IMAGES PUIS LA CONSTITUTION DU DOSSIER A ENVOYER.
         * COTE CLIENT IL FAUT GERER LA CREATION DU DOSSIER DANS LES FICHIERS DE L'APPLICATION ET LEUR SUPPRESSION IN FINE APRES FABRICATION DU PDF.
         * ETAPE 4 CI-DESSOUS : Envoi IMAGES, R�ception REFERENCES AUX IMAGES
         */
        
        System.out.println("Parties textuelles trait�es, d�but de l'envoi des liens images � l'utilisateur");
        
        //On supposera qu'on a un ArrayList<String> qui contient les URL vers les images. 
        ArrayList<String> urls = new ArrayList<String>();
        urls.add("C:\\Users\\Guillaume\\Desktop\\dossier photo esp\\Drapeaux\\DOMINICA.png"); 
        urls.add("C:\\Users\\Guillaume\\Desktop\\dossier photo esp\\Drapeaux\\STVICENTE.png"); //Pour tests whitebox, on va s'envoyer des drapeaux d'un dossier � l'autre... en url cette fois.
        urls.add("C:\\Users\\Guillaume\\Desktop\\dossier photo esp\\Drapeaux\\1France.png");
        for(int i = 0; i < urls.size(); i++) {
			try {
				wOut.write(urls.get(i)+'\n');
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
        }//Peut-�tre flush � chaque tour m�me si �a consomme plus, pour la taille du buffer � envoyer. 
        try {
			wOut.write("####STEP4####\n");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}                                                         //M�me si pour le coup on arrive � envoyer des images donc �a devrait le faire.
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
         * Les retours sont importants mais juste pour l'apprentissage : le client a ses URL � l'�tape 4 et son texte lui sera renvoy� (m�me s'il est en th�orie compl�table depuis �tape 3) �tape 5
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
		} //Le client aura d�j� les URL on lui renvoie juste le texte avec le remplacement fait des synonymes je sais pas trop o�.
        try {
        	wOut.flush();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        
        /**
         * ETAPE 5 TERMINEE - 
         * Fermeture de tout ce qui doit �tre ferm� (type Stream, Reader...)
         * Fermeture du thread.
         */
        
       System.out.println("Les images ont �t� s�lectionn�es par le client, le texte simplifi� final a �t� envoy� : Fin du Thread");
       
       	try {
        wOut.close();
        rOut.close();
       	} catch (IOException e) {}
       	finally {
		try {
			//C'est la d�connexion du client qui fera arriver le Thread � cet endroit. Normalement, cela co�ncide �galement avec la fin du run.
			System.out.println("Le client s'est d�connect�");
			serveurFALC.remClient(numClient);
			socket.close(); //Normalement d�j� ferm� � cause de l'exception lev�e menant au finally.
		} catch (IOException e) {}
    
	}//run { }
	
	}
}//classBody { }

/* Poubelle non utilis�e : on n'envoie pas des images mais des URL �a prend moins de place et c'est l'utilisateur qui les t�l�chargera. 
 * OutputStream outputStream = socket.getOutputStream();
        ByteArrayOutputStream bytesOut = new ByteArrayOutputStream();
        byte[] size;
        int i = 0;
        ArrayList<String> imgLocations = new ArrayList<String>();
        
        //Pour des tests en local, je vais m'envoyer des drapeaux d'un dossier � l'autre
        
        imgLocations.add("C:\\Users\\Guillaume\\Desktop\\dossier photo esp\\Drapeaux\\DOMINICA.png");
        imgLocations.add("C:\\Users\\Guillaume\\Desktop\\dossier photo esp\\Drapeaux\\STVICENTE.png");
        imgLocations.add("C:\\Users\\Guillaume\\Desktop\\dossier photo esp\\Drapeaux\\1France.png");
        
        //Cette ArrayList contient les chemins d'acc�s aux images qui devront �tre envoy�es (sous la forme C:\\Users\\Me\\Desktop\\AuroraBorealis.png)
        
        for(String loc : imgLocations) try {
        	System.out.println(loc);
        	BufferedImage image = ImageIO.read(new File(loc));
        	//Un probl�me est encore non r�solu : pour 2 fichiers ou plus, image devient null � un moment donn� entre le d�part et l'arriv�e.
        	//Ce qui est surprenant, c'est que le pathfile est bien bon, le fonctionnement et les boucles tournent �galement, le inputstream lit ce qu'il faut � l'arriv�e...
        	//Le probl�me semble venir de la classe ImageIO qui lit toujours depuis le d�but la cha�ne d'octets entrante. Mais m�me apr�s flush rien ne fonctionne. 
        	ImageIO.write(image, "png", bytesOut);
        	FileOutputStream sortie = new FileOutputStream(new File("mon fichier.txt"));
        	sortie.write(bytesOut.toByteArray());
        	sortie.close();
            size = ByteBuffer.allocate(4).putInt(bytesOut.size()).array();
            System.out.println(size);
            outputStream.write(size);
            outputStream.write(bytesOut.toByteArray()); //write prendra en argument un byte array mais pas un ByteArrayOutputStream.
            //Dans l'ordre, la taille va arriver d'abord et on recevra correctement les bits correspondant � l'image pour la reconstruire.
            System.out.println("Envoi de l'image "+i+" : "+System.currentTimeMillis()); //La commande System.currentTimeMillis() pour estimer la vitesse.
            outputStream.flush();   
            i++;
        } catch(IOException e) {
        }
        
        //Pour envoyer des images en TCP, ce qui se fait de plus courant est d'abord d'envoyer la taille de l'image qui va �tre re�ue
        //avant de l'envoyer elle-m�me. On va vouloir envoyer des byteArray dont les premiers (poids faible) contiennent la taille. 
        //Pour les images, on va directement travailler sur le stream avec les bytes. Plus pr�s de la machine.
        */

/* Poubelle non utilis�e : on n'utilisera pas de fichier txt dans lequel on �crira, juste des ArrayList de String qui seront des 'pointeurs' vers un peu tout et n'importe quoi.
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
        //R�cup�rer dans out.t
        //cr�ation du dossier des images
   		
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

