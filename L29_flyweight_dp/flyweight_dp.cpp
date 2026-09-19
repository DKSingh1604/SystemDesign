#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Asteroid {
private:
  // Intrinsic properties - Duplicated for each object
  int length;
  int width;
  int weight;
  string color;
  string texture;
  string material;

  // Extrisic properties - unique for each asteroid
  int posX, posY;
  int velocityX, velocityY;

public:
  Asteroid(int l, int w, int wt, string col, string tex, string mat, int posX,
           int posY, int velX, int velY) {
    this->length = l;
    this->width = w;
    this->weight = wt;
    this->color = col;
    this->texture = tex;
    this->material = mat;
    this->posX = posX;
    this->posY = posY;
    this->velocityX = velX;
    this->velocityY = velY;
  }

  void render() {
    cout << "The details are: " << endl;
    cout << "Length: " << length << endl;
    cout << "Width: " << width << endl;
    cout << "Weight: " << weight << endl;
    cout << "Color: " << color << endl; // etc...
  }

  static size_t getMemoryUsage() {
    return sizeof(int) * 7 + sizeof(string) * 3 + 32 * 3;
  }
};

int main() { return 0; }