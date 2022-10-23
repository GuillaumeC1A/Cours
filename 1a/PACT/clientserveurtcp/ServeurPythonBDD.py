#!/usr/bin/env python3
#coding: utf-8

import socket
import threading

class ThreadClient(threading.Thread):
    def init(this, connected):
        threading.Thread.init(this)
        init.connection = connected

    def run(this):
        #La partie qui travaille le fichier
        key = ""
        recu = connection.recv(1024)
        connection.send(b'Debut de reception de requete\n')
        #Il faudra envoyer tout le texte au départ pour l'analyse syntaxique (PAN4)
        while recu:
            if(recu != b'####ENDSEND####\n'):
                key+=recu.decode('utf-8')
                #La ligne juste au-dessus est à modifier si c'est un fichier qu'on veut reconstruire et dont on veut extraire le texte.
                recu = connection.recv(1024)
            elif:
                connection.send(b'Fin de reception, traitement en cours...\n')
                print("Fin de la reception, traitement en cours pour le client "+this.getName())
                ###ICI A LIEU LE TRAITEMENT
                ###Création des fichiers de retour...
                """Exemple :
                for
                for image in images:
                    size = sizeof(image)
                    connection.send(size.to_bytes(8, byteorder='big')
                    connection.send(image)"""
            key += recu.decode('utf-8')
        this.connection.close() #Coupure côté serveur
        del(clients[this.getName()])
        print("Le client "+ this.getName()+ "a ete deconnecte par le serveur a la fin du renvoi")
        #Client déconnecté => Fin du Thread

clients = {} #Dictionnaire des clients qui passent
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(('0.0.0.0', 8888))
sock.listen()

#Il est possible de mettre un timer pour arrêter d'écoute au bout de 15 secondes par exemple,
#mais on va plutôt le faire venir du client puisque le serveur est censé tourner en permanence sur un poste distant.

while True:

    client,address = sock.accept()
    threadClient = ThreadClient(connection)
    threadClient.start()

    #Le nouveau thread est lancé, on s'occupe maintenant de la gestion générale des clients
    #Mise à jour du dictionnaire et confirmation de requêtes / connexions :

    clients[threadClient.getName()]=client
    print("connection received on database from client "+ threadClient.getName()+" of IP '"+address[0]+"' on port "+address[1])


def send_image():
    sock.send(size.to_bytes(8, byteorder='big'))
    sock.send(data)
    print("image sent, waiting for confirmation...")