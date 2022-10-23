#include "2.2.h"

const int Pixel::GetX() const {
    return x_;
}

const int Pixel::GetY() const {
    return y_;
}

const int Pixel::GetColor() const {
    return color_;
}

void Pixel::SetX(const int x) {
    x_ = x;
}

void Pixel::SetY(const int y) {
    y_ = y;
}

Pixel::Pixel() { //Constructeur par défaut, que l'on est obligé de recoder si on veut aussi un constructeur personnalisé EN PLUS de lui.
    x_ = 0;
    y_ = 0;
    color_ = 0;
}

Pixel::Pixel(const int x, const int y, const int color) { //Constructeur complet
    x_ = x;
    y_ = y;
    color_ = color;
}

