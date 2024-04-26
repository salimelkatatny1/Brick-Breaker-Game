#include "collectables.h"
#include "paddle.h"
#include "gameConfig.h"
#include "game.h"
#include <random>
#include <ctime> // Include this header for time functions
using namespace std;
#include <iostream>

collectable::collectable(point r_uprleft, int r_width, int r_height, game* r_pGame, string type, int dur) :
    collidable(r_uprleft, r_width, r_height, r_pGame), powerUpType(type), duration(dur) {
	speedX = 0;
	speedY = 1;
	moving = false;
}
void collectable::clear() {
    window* pWind = pGame->getWind();
    // Clear the entire area of the collectable
    pWind->SetPen(LAVENDER);
    pWind->SetBrush(LAVENDER);
    pWind->DrawRectangle(uprLft.x, uprLft.y, uprLft.x + width, uprLft.y + height);
}
void collectable::draw() const {
    // Drawing logic for the paddle without an image
    window* pWind = pGame->getWind();
    pWind->SetPen(BLUE, 30);
    pWind->SetBrush(BLUE);
    pWind->DrawRectangle(uprLft.x, uprLft.y, uprLft.x + width, uprLft.y + height);
}

void collectable::moveDown() {
    // Set the collectable to moving
    moving = true;

    while (moving) {
        pGame->getBall()->collisionAction();
        pGame->getBall()->launchBall();
        pGame->getPaddle()->movePaddle();
        speedY = 1;
        // Clear the collectable's previous position
        clear();
        updateCollecCenter();
        draw();
        // Example: Stop the collectable after reaching a certain point
        if (uprLft.y >= 600) {
            pGame->getBall()->collisionAction();
            moving = false;
            clear();
        }
        if (pGame->getPaddle()->isCollectableCollision(*this)) {
            collisionAction();
        }
        // Update the collectable's position for downward movement
        updateCollecCenter();
    }
}



void collectable::updateCollecCenter()
{
	uprLft.x += speedX;
	uprLft.y += speedY;
}
void collectable::collisionAction()
{
    collectType randomType = getRandomCollectType();

    switch (randomType) {
    case REVERSE_PADDLE:
        std::cout << "Selected: REVERSE_PADDLE" << std::endl;
        pGame->getPaddle()->reversePaddle();
        break;
    case WINDGLIDE:
        std::cout << "Selected: WINDGLIDE" << std::endl;
        pGame->getPaddle()->incSpeedPaddle();
        break;
    case FIREBALLS:
        std::cout << "Selected: FIREBALLS" << std::endl;
        pGame->getBall()->setBallType(FIREBALL); // Set ball to fireball type
        break;
        // Add cases for other collectable types if needed
    }

    return ;
}


