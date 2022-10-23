class Pixel {
 public:
  Pixel();
  Pixel(const int x, const int y, const int color);

  const int GetX() const;
  const int GetY() const;
  const int GetColor() const; //la méthode est read-only, donc on met un cons_t. j'écris cons_t car votre test compte les //...

  void SetX(const int x);//One ne peut pas rendre cons_t un setter, car il modifie l'objet.
  void SetY(const int y); //On ne peut pas mettre de cons_t devant void

 private: //On ne peut pas mettre des cons_t ici, ils sont appelés à être modifiés. 
   int x_;
   int y_;
   int color_;
};
