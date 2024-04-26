#pragma once
#include "collidable.h"
#include <random>
enum collectType	//add more collectables types
{
    REVERSE_PADDLE,
    WINDGLIDE,
    FIREBALLS,
   // WIDEPADDLE,  //bouns
   // NARROWPADDLE,
   // MAGNET,        //bouns
   // QUICKSAND,       //bouns
   // MULITBALLS,       //bouns
  // NEWACTION       //bouns
};
class collectable : public collidable {
protected:
    string powerUpType;
    int duration; // in milliseconds
    int speedX;
   int speedY;
   bool moving;
   collectType getRandomCollectType() {
       srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator with current time
       return static_cast<collectType>(rand() % FIREBALLS);
   }
public:
    collectable(point r_uprleft, int r_width, int r_height, game* r_pGame, string type, int dur);
    void draw()const;
    void clear();
    void updateCollecCenter();
    void moveDown();  // Move the collectable down
    virtual void collisionAction(); // Define action upon collision with paddle
    point getPosition() const {
        return uprLft;
    }

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }
};
