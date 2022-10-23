using uint64 = unsigned long long;

class Uint2048 {
 public:
  Uint2048();
  Uint2048(const int& x); 

  bool operator<(const Uint2048& other) const;
  bool operator==(const Uint2048& other) const;
  Uint2048 operator+(const Uint2048& other) const;
  Uint2048 operator-(const Uint2048& other) const;
  Uint2048 operator*(const Uint2048& other) const;
  Uint2048 operator/(const Uint2048& other) const;
  void Print() const;

  static int NumAdditions();
  //Une fonction static n'est pas appelée sur un objet en particulier, alors que const dit que la fonction ne modifie pas les 
  //objets appelés. On ne peut donc pas les mettre tous les deux en même temps, et on a besoin du static.

 private:
  static int numAdd; //Nombre d'additions effectuées dans la classe -> obligé d'être static pour être le même pour toutes les instances.
  uint64 u_[32];
};
