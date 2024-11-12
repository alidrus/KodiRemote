// vim: syntax=arduino autoindent expandtab tabstop=4 shiftwidth=4 softtabstop=4:

#ifndef MOVEMENT_H

#define MOVEMENT_H

#ifndef MOVEMENT_CPP

static const int selectPin = 32;
static const int backPin = 33;
static const int upPin = 27;
static const int downPin = 14;
static const int leftPin = 12;
static const int rightPin = 13;

bool touchingSelect = false;
bool touchingBack = false;
bool touchingUp = false;
bool touchingDown = false;
bool touchingLeft = false;
bool touchingRight = false;

bool isBusy = false;

void sendMovement(int direction);

#endif // MOVEMENT_CPP

#define MOVEMENT_SELECT 0
#define MOVEMENT_BACK 1
#define MOVEMENT_UP 2
#define MOVEMENT_DOWN 3
#define MOVEMENT_LEFT 4
#define MOVEMENT_RIGHT 5

#endif // MOVEMENT_H
