#include "2.1.h"

int Pixel::GetX() {
    return x_;
}

int Pixel::GetY() {
    return y_;
}

int Pixel::GetColor() {
    return color_;
}

void Pixel::SetX(int x) {
    x_ = x;
}

void Pixel::SetY(int y) {
    y_ = y;
}

Pixel::Pixel() { //Constructeur par défaut, que l'on est obligé de recoder si on veut aussi un constructeur personnalisé EN PLUS de lui.
    x_ = 0;
    y_ = 0;
    color_ = 0;
}

Pixel::Pixel(int x, int y, int color) { //Constructeur complet
    x_ = x;
    y_ = y;
    color_ = color;
}

