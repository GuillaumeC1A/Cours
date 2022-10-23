#include <iostream>
#include "3.1.h"

using namespace std;

List::Element* List::Head() {
    return this->head;  
}     

int List::NumElements() {
    Element *element = head;
    int i = 0;

    while(element != nullptr) {
      i++;
      element = element->next;
    }
    return i; 
}
    
void List::Remove(Element* element) {
    if(element == nullptr) {
        cout << "Argument non valide, on ne peut pas retirer du void" << endl;
        return;
    }
        
    Element* cur = head;
    if(head == nullptr) {//si la liste est vide
      cout << "la liste est deja vide" << endl;
      return;
    }
    
    while(cur->next != nullptr && cur != element)
      cur = cur->next;

    if(cur != element) 
      return;
        //si l'élément sur lequel on a fini est le dernier de la liste,
        // et qu'on n'a pas rencontré element, alors on ne peut pas le supprimer.
        //pour détailler, si on arrive ici, c'est qu'on n'a pas trouvé element et que 
        //l'élément suivant du courant est nullptr i.e. qu'on est à la fin de la liste.         

        //Sinon, c'est qu'on a bien trouvé l'élément à supprimer et qu'on est dessus. 
        //Il reste deux dernières distinctions, si c'est le dernier (pas de suivant), 
        //et si c'est le premier (i.e. pas de précédent), ou les deux.

    if(cur->prev == nullptr && cur->next == nullptr) { 
        
        //S'il n'y a pas de précédent, je suis forcément au début. 
        //Et s'il n'y a pas de suivant, alors je suis le seul élément et il suffit de me supprimer. 
        //Cependant c'est particulier ici : en supprimant le dernier élément, on supprime la liste. Alors le head devient nullptr.
        head = nullptr;
        
    } else if(cur->prev == nullptr) { //si je suis au début mais que je ne suis pas tout seul
        (cur->next)->prev = nullptr; //on enlève le lien du deuxième vers ce premier et on détruit le premier
        head = cur->next;

    } else if(cur->next == nullptr) { //si je suis à la fin mais que j'ai quelqu'un derrière moi au moins
        (cur->prev)->next = nullptr; //je fais pointer le précédent dans le vide et on détruit le dernier
        
    } else {
        (cur->next)->prev = cur->prev;
        (cur->prev)->next = cur->next; //je relie les éléments qui m'entourent, plus personne ne pointe sur moi
    }

    delete cur; //je n'oublie pas de me détruire, sinon il y a fuite memoire. Personne ne sait où elle est mais la MMU n'y accède plus...
    return;          
}

List::Element* List::InsertNewElementAfter(double value, Element* position) {
    Element* element = new Element(value);
    Element* cur = head;

    if(head == nullptr) {//si la liste est vide
      head = element;
      return head;
    }

    if(position == nullptr) { //si on nous demande de l'insérer au début
      element->next = head;
      head->prev = element; //&element en quelque sorte, mais element est déjà un pointeur, pas l'objet lui-même.
      this->head = element; //idem (je m'étais trompé : Element element = new Element(value); au lieu de Element* element... d'où le &.
      return element; //idem
    }

    while(cur->next != nullptr && cur != position)
      cur = cur->next;
     
    if(cur != position) { //Si on parcourt toute la liste sans trouver position, la seule possibilité étant cur = nullptr, à la fin...
      cout << "l'element position n'existe pas" << endl;
      return nullptr;
    }

    //Si on arrive ici, on sait qu'on est à position. Mais il reste encore une distinction à faire selon 
    //s'il y a un élément après où si c'est le dernier élément de la liste.
    
    element->next = cur->next;  //cur->next = nullptr si on est à la fin de la liste, c'est ce qu'on veut.
    // Le suivant de notre élément sera donc bien un nullptr si c'est vide, la bonne adresse sinon.
    element->prev = cur;
    cur->next = element;

    if(element->next != nullptr)  //s'il y a un élément APRES celui qu'on vient d'insérer, il faut corriger son prev. Sinon, on a fini
      (element->next)->prev = element; //adresse de l'élément
        
    return element; //return &element; en quelque sorte, on renvoie l'adresse de l'élément créé et inséré.
}

List::Element* List::Find(double d) {
    Element* cur = head;
    while(cur != nullptr && cur->value != d)
      cur = cur->next;
    return cur;
}

void List::InsertListAfter(const List* other, Element* position) { 
//Pour insérer une liste chaînée dans une autre, on pourrait insérer chaque élément à sa place. 
//Je vais plutôt lier le dernier élément de la première moitié de la liste originale avec le premier élément de other, 
//puis profiter d'avoir la liste other complètement liée pour ensuite lier son dernier élément avec le premier élément
//de la deuxième moitié de la liste originale.


    if(head == nullptr) { //si la liste originale est vide
      head = other->head; //alors la nouvelle liste est celle qu'on devait insérer.
      return; 
    }

    Element* cur = head;

    if (other->head == nullptr) {
      cout << "la liste à inserer est vide" << endl;
      return;
    
    } else if (position == nullptr) { //insertion au début
        Element *curother = other->head;
        while(curother->next != nullptr) {
          curother = curother->next;
        }
        //curother est le cur pour l'autre list (other). On va à la fin de other pour recoller au début de la liste originale.
        curother->next = head;
        head->prev = curother;
        head = other->head; //On n'oublie pas de changer la tête puisqu'on a inséré au début
        return;
        
    } else {
        while(cur->next != nullptr && cur != position) { //Sinon, on commence par chercher l'endroit d'insertion
          cur = cur->next;
        }
        if(cur != position) {
          cout << "l'element position n'existe pas" << endl; //On n'insère pas la liste, pas de point d'insertion.
          return;

        } else if(cur->next == nullptr) { //si on est à la fin de la liste, on colle juste le début de other sur la fin de List. 
          cur->next = other->head; //On lie notre dernier élément vers other
          (other->head)->prev = cur; //on lie le premier élément de other vers notre dernier élement
          return; //la head ne change pas.

        } else { //sinon, on a des voisins devant et derrière et on est au bon endroit
          Element *curother = other->head;
          while(curother->next != nullptr) {
            curother = curother->next;
          }
          //curother est le cur pour l'autre list (other). On va à la fin de other pour recoller à l'autre bout de la liste originale.
          curother->next = cur->next; //milieu vers fin
          (curother->next)->prev = curother; //fin vers milieu
          cur->next = other->head; //début vers milieu (on peut écraser cur->next car la liaison de fin est faite)
          (other->head)->prev = cur; //milieu vers début. On écrase rien ici, other->head->prev est vide (début de other)
          return; //pas besoin de changer la head. 
        }
    }

    return;
    }