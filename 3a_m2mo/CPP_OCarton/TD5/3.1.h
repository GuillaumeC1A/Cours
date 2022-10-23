#include <iostream>

class List {

    public:
    struct Element {
        double value;
        Element* prev;
        Element* next;

        Element(double value) { //Un constructeur pour Element, au départ ou ne sait pas qui sont ses voisins, seulement sa value.
            this->value = value;
            this->prev = nullptr;
            this->next = nullptr;
        }
    };
    private:
    Element* head = nullptr; //contient le début de la liste chaînée
    //on ne peut pas faire autrement parce que la liste ne 'possède pas' d'objet. 
    //Pour la fonction Head(), on ne sait pas par où commencer, this->element ne ferait pas sens, 
    //elle est contient un nombre variable, auquel ferait-on référence ? Au premier probablement, d'où l'importance du head. 
    //En revanche, elle a toujours un début (et éventuellement une fin, mais c'est un peu facile et pas indispensable d'avoir un Element* tail...)
    
    
    public:
    Element* Head();
    int NumElements();

    void Remove(Element* element);   
    Element* InsertNewElementAfter(double value, Element* position);
    Element* Find(double d);
    void InsertListAfter(const List* other, Element* position);
    };