#include <string>
#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <list>
using namespace std;

class Vector
{
public:
    double posX;
    double posY;

    double magX;
    double magY;

    Vector()
    {
        posX = 0;
        posY = 0;

        magX = 1;
        magY = 1;
    }

    Vector(double x, double y, double mx, double my)
    {
        posX = x;
        posY = y;

        magX = mx;
        magY = my;
    }
};

int getQuad(Vector vector)
{

    if (vector.magX >= 0)
    {
        if (vector.magY <= 0)
        { // QI
            return 1;
        }
        else
        { // QIV
            return 4;
        }
    }
    else
    {
        if (vector.magY <= 0)
        { // QII
            return 2;
        }
        else
        { // QIII
            return 3;
        }
    }
}

double secondToFrame(double in)
{
    double returnVal = in / 60;
    return returnVal;
}

double getSpeed(Vector vector)
{
    return sqrt(pow(vector.magX, 2) + pow(vector.magY, 2));
}

double getAngle(Vector v1, Vector v2)
{
    double dotP = (v1.magX * v2.magX) + (v1.magY * v2.magY);
    double magA = getSpeed(v1);
    double magB = getSpeed(v2);

    return acos(dotP / (magA * magB)) * (180 / M_PI);
}

Vector rotate(Vector missileV, Vector guideV, double maxTurn, double angleDiff)
{
    Vector invertV(missileV.posX, missileV.posY, -1 * missileV.posX, -1 * missileV.posY);
    switch (getQuad(missileV))
    {
    case 1: // QI
        if (missileV.magX == 0)
        { // verticle edge case
            if (getQuad(guideV) == 1 || getQuad(guideV) == 4)
            { // turn clockwise
                if (angleDiff >= maxTurn)
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(maxTurn) - missileV.magY * sin(maxTurn), missileV.magX * sin(maxTurn) + missileV.magY * cos(maxTurn));
                    return newV;
                }
                else
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(angleDiff) - missileV.magY * sin(angleDiff), missileV.magX * sin(angleDiff) + missileV.magY * cos(angleDiff));
                    return newV;
                }
            }
            else
            { // turn c-clockwise
                if (angleDiff >= maxTurn)
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * maxTurn) - missileV.magY * sin(-1 * maxTurn), missileV.magX * sin(-1 * maxTurn) + missileV.magY * cos(-1 * maxTurn));
                    return newV;
                }
                else
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * angleDiff) - missileV.magY * sin(-1 * angleDiff), missileV.magX * sin(-1 * angleDiff) + missileV.magY * cos(-1 * angleDiff));
                    return newV;
                }
            }
        }
        else if (missileV.magY == 0)
        { // horizontal edge case
            if (getQuad(guideV) == 3 || getQuad(guideV) == 4)
            { // turn clockwise
                if (angleDiff >= maxTurn)
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(maxTurn) - missileV.magY * sin(maxTurn), missileV.magX * sin(maxTurn) + missileV.magY * cos(maxTurn));
                    return newV;
                }
                else
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(angleDiff) - missileV.magY * sin(angleDiff), missileV.magX * sin(angleDiff) + missileV.magY * cos(angleDiff));
                    return newV;
                }
            }
            else
            { // turn c-clockwise
                if (angleDiff >= maxTurn)
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * maxTurn) - missileV.magY * sin(-1 * maxTurn), missileV.magX * sin(-1 * maxTurn) + missileV.magY * cos(-1 * maxTurn));
                    return newV;
                }
                else
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * angleDiff) - missileV.magY * sin(-1 * angleDiff), missileV.magX * sin(-1 * angleDiff) + missileV.magY * cos(-1 * angleDiff));
                    return newV;
                }
            }
        }
        else
        { // QI
            switch (getQuad(guideV))
            {
            case 1:
                if (guideV.magX > missileV.magX)
                { // clock
                    if (angleDiff >= maxTurn)
                    {
                        Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(maxTurn) - missileV.magY * sin(maxTurn), missileV.magX * sin(maxTurn) + missileV.magY * cos(maxTurn));
                        return newV;
                    }
                    else
                    {
                        Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(angleDiff) - missileV.magY * sin(angleDiff), missileV.magX * sin(angleDiff) + missileV.magY * cos(angleDiff));
                        return newV;
                    }
                }
                else
                { // counter clock
                    if (angleDiff >= maxTurn)
                    {
                        Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * maxTurn) - missileV.magY * sin(-1 * maxTurn), missileV.magX * sin(-1 * maxTurn) + missileV.magY * cos(-1 * maxTurn));
                        return newV;
                    }
                    else
                    {
                        Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * angleDiff) - missileV.magY * sin(-1 * angleDiff), missileV.magX * sin(-1 * angleDiff) + missileV.magY * cos(-1 * angleDiff));
                        return newV;
                    }
                }
                break;
            case 2:
                if (angleDiff >= maxTurn) // counterclock
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * maxTurn) - missileV.magY * sin(-1 * maxTurn), missileV.magX * sin(-1 * maxTurn) + missileV.magY * cos(-1 * maxTurn));
                    return newV;
                }
                else
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * angleDiff) - missileV.magY * sin(-1 * angleDiff), missileV.magX * sin(-1 * angleDiff) + missileV.magY * cos(-1 * angleDiff));
                    return newV;
                }
                break;
            case 3:
                // Vector invertV(missileV.posX, missileV.posY, -1 * missileV.posX, -1 * missileV.posY);
                if (guideV.magX < invertV.magX)
                { // clock
                    if (angleDiff >= maxTurn)
                    {
                        Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(maxTurn) - missileV.magY * sin(maxTurn), missileV.magX * sin(maxTurn) + missileV.magY * cos(maxTurn));
                        return newV;
                    }
                    else
                    {
                        Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(angleDiff) - missileV.magY * sin(angleDiff), missileV.magX * sin(angleDiff) + missileV.magY * cos(angleDiff));
                        return newV;
                    }
                }
                else
                { // counter clock
                    if (angleDiff >= maxTurn)
                    {
                        Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * maxTurn) - missileV.magY * sin(-1 * maxTurn), missileV.magX * sin(-1 * maxTurn) + missileV.magY * cos(-1 * maxTurn));
                        return newV;
                    }
                    else
                    {
                        Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * angleDiff) - missileV.magY * sin(-1 * angleDiff), missileV.magX * sin(-1 * angleDiff) + missileV.magY * cos(-1 * angleDiff));
                        return newV;
                    }
                }
                break;
            case 4:
                if (angleDiff >= maxTurn) // clockwise
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(maxTurn) - missileV.magY * sin(maxTurn), missileV.magX * sin(maxTurn) + missileV.magY * cos(maxTurn));
                    return newV;
                }
                else
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(angleDiff) - missileV.magY * sin(angleDiff), missileV.magX * sin(angleDiff) + missileV.magY * cos(angleDiff));
                    return newV;
                }
                break;
            }
        }
        break;
    case 2: // QII
        if (missileV.magY == 0)
        { // horizontal edge case
            if (getQuad(guideV) == 2 || getQuad(guideV) == 1)
            { // turn clockwise
                if (angleDiff >= maxTurn)
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(maxTurn) - missileV.magY * sin(maxTurn), missileV.magX * sin(maxTurn) + missileV.magY * cos(maxTurn));
                    return newV;
                }
                else
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(angleDiff) - missileV.magY * sin(angleDiff), missileV.magX * sin(angleDiff) + missileV.magY * cos(angleDiff));
                    return newV;
                }
            }
            else
            { // turn c-clockwise
                if (angleDiff >= maxTurn)
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * maxTurn) - missileV.magY * sin(-1 * maxTurn), missileV.magX * sin(-1 * maxTurn) + missileV.magY * cos(-1 * maxTurn));
                    return newV;
                }
                else
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * angleDiff) - missileV.magY * sin(-1 * angleDiff), missileV.magX * sin(-1 * angleDiff) + missileV.magY * cos(-1 * angleDiff));
                    return newV;
                }
            }
        }
        else
        {
            switch (getQuad(guideV))
            {
            case 1:
                if (angleDiff >= maxTurn) // clockwsie
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(maxTurn) - missileV.magY * sin(maxTurn), missileV.magX * sin(maxTurn) + missileV.magY * cos(maxTurn));
                    return newV;
                }
                else
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(angleDiff) - missileV.magY * sin(angleDiff), missileV.magX * sin(angleDiff) + missileV.magY * cos(angleDiff));
                    return newV;
                }
                break;
            case 2:
                if (guideV.magX > missileV.magX)
                { // clock
                    if (angleDiff >= maxTurn)
                    {
                        Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(maxTurn) - missileV.magY * sin(maxTurn), missileV.magX * sin(maxTurn) + missileV.magY * cos(maxTurn));
                        return newV;
                    }
                    else
                    {
                        Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(angleDiff) - missileV.magY * sin(angleDiff), missileV.magX * sin(angleDiff) + missileV.magY * cos(angleDiff));
                        return newV;
                    }
                }
                else
                { // counter clock
                    if (angleDiff >= maxTurn)
                    {
                        Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * maxTurn) - missileV.magY * sin(-1 * maxTurn), missileV.magX * sin(-1 * maxTurn) + missileV.magY * cos(-1 * maxTurn));
                        return newV;
                    }
                    else
                    {
                        Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * angleDiff) - missileV.magY * sin(-1 * angleDiff), missileV.magX * sin(-1 * angleDiff) + missileV.magY * cos(-1 * angleDiff));
                        return newV;
                    }
                }
                break;
            case 3:
                if (angleDiff >= maxTurn) // counterclock
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * maxTurn) - missileV.magY * sin(-1 * maxTurn), missileV.magX * sin(-1 * maxTurn) + missileV.magY * cos(-1 * maxTurn));
                    return newV;
                }
                else
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * angleDiff) - missileV.magY * sin(-1 * angleDiff), missileV.magX * sin(-1 * angleDiff) + missileV.magY * cos(-1 * angleDiff));
                    return newV;
                }
                break;
            case 4:
                // Vector invertV(missileV.posX, missileV.posY, -1 * missileV.posX, -1 * missileV.posY);
                if (guideV.magX < invertV.magX)
                { // clock
                    if (angleDiff >= maxTurn)
                    {
                        Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(maxTurn) - missileV.magY * sin(maxTurn), missileV.magX * sin(maxTurn) + missileV.magY * cos(maxTurn));
                        return newV;
                    }
                    else
                    {
                        Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(angleDiff) - missileV.magY * sin(angleDiff), missileV.magX * sin(angleDiff) + missileV.magY * cos(angleDiff));
                        return newV;
                    }
                }
                else
                { // counter clock
                    if (angleDiff >= maxTurn)
                    {
                        Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * maxTurn) - missileV.magY * sin(-1 * maxTurn), missileV.magX * sin(-1 * maxTurn) + missileV.magY * cos(-1 * maxTurn));
                        return newV;
                    }
                    else
                    {
                        Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * angleDiff) - missileV.magY * sin(-1 * angleDiff), missileV.magX * sin(-1 * angleDiff) + missileV.magY * cos(-1 * angleDiff));
                        return newV;
                    }
                }
                break;
            }
        }
        break;
    case 3: // QIII
        if (missileV.magX == 0)
        { // vertical edge case
            if (getQuad(guideV) == 2 || getQuad(guideV) == 3)
            { // turn clockwise
                if (angleDiff >= maxTurn)
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(maxTurn) - missileV.magY * sin(maxTurn), missileV.magX * sin(maxTurn) + missileV.magY * cos(maxTurn));
                    return newV;
                }
                else
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(angleDiff) - missileV.magY * sin(angleDiff), missileV.magX * sin(angleDiff) + missileV.magY * cos(angleDiff));
                    return newV;
                }
            }
            else
            { // turn c-clockwise
                if (angleDiff >= maxTurn)
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * maxTurn) - missileV.magY * sin(-1 * maxTurn), missileV.magX * sin(-1 * maxTurn) + missileV.magY * cos(-1 * maxTurn));
                    return newV;
                }
                else
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * angleDiff) - missileV.magY * sin(-1 * angleDiff), missileV.magX * sin(-1 * angleDiff) + missileV.magY * cos(-1 * angleDiff));
                    return newV;
                }
            }
        }
        else
        {
            switch (getQuad(guideV))
            {
            case 1:
                // Vector invertV(missileV.posX, missileV.posY, -1 * missileV.posX, -1 * missileV.posY);
                if (guideV.magX > invertV.magX)
                { // clock
                    if (angleDiff >= maxTurn)
                    {
                        Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(maxTurn) - missileV.magY * sin(maxTurn), missileV.magX * sin(maxTurn) + missileV.magY * cos(maxTurn));
                        return newV;
                    }
                    else
                    {
                        Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(angleDiff) - missileV.magY * sin(angleDiff), missileV.magX * sin(angleDiff) + missileV.magY * cos(angleDiff));
                        return newV;
                    }
                }
                else
                { // counter clock
                    if (angleDiff >= maxTurn)
                    {
                        Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * maxTurn) - missileV.magY * sin(-1 * maxTurn), missileV.magX * sin(-1 * maxTurn) + missileV.magY * cos(-1 * maxTurn));
                        return newV;
                    }
                    else
                    {
                        Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * angleDiff) - missileV.magY * sin(-1 * angleDiff), missileV.magX * sin(-1 * angleDiff) + missileV.magY * cos(-1 * angleDiff));
                        return newV;
                    }
                }
                break;
            case 2:
                if (angleDiff >= maxTurn) // clockwsie
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(maxTurn) - missileV.magY * sin(maxTurn), missileV.magX * sin(maxTurn) + missileV.magY * cos(maxTurn));
                    return newV;
                }
                else
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(angleDiff) - missileV.magY * sin(angleDiff), missileV.magX * sin(angleDiff) + missileV.magY * cos(angleDiff));
                    return newV;
                }
                break;
            case 3:
                if (guideV.magX < missileV.magX)
                { // clock
                    if (angleDiff >= maxTurn)
                    {
                        Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(maxTurn) - missileV.magY * sin(maxTurn), missileV.magX * sin(maxTurn) + missileV.magY * cos(maxTurn));
                        return newV;
                    }
                    else
                    {
                        Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(angleDiff) - missileV.magY * sin(angleDiff), missileV.magX * sin(angleDiff) + missileV.magY * cos(angleDiff));
                        return newV;
                    }
                }
                else
                { // counter clock
                    if (angleDiff >= maxTurn)
                    {
                        Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * maxTurn) - missileV.magY * sin(-1 * maxTurn), missileV.magX * sin(-1 * maxTurn) + missileV.magY * cos(-1 * maxTurn));
                        return newV;
                    }
                    else
                    {
                        Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * angleDiff) - missileV.magY * sin(-1 * angleDiff), missileV.magX * sin(-1 * angleDiff) + missileV.magY * cos(-1 * angleDiff));
                        return newV;
                    }
                }
                break;
            case 4:
                if (angleDiff >= maxTurn) // counterclock
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * maxTurn) - missileV.magY * sin(-1 * maxTurn), missileV.magX * sin(-1 * maxTurn) + missileV.magY * cos(-1 * maxTurn));
                    return newV;
                }
                else
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * angleDiff) - missileV.magY * sin(-1 * angleDiff), missileV.magX * sin(-1 * angleDiff) + missileV.magY * cos(-1 * angleDiff));
                    return newV;
                }
                break;
            }
        }
        break;
    case 4: // QIV
        switch (getQuad(guideV))
        {
        case 1:
            if (angleDiff >= maxTurn) // counterclock
            {
                Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * maxTurn) - missileV.magY * sin(-1 * maxTurn), missileV.magX * sin(-1 * maxTurn) + missileV.magY * cos(-1 * maxTurn));
                return newV;
            }
            else
            {
                Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * angleDiff) - missileV.magY * sin(-1 * angleDiff), missileV.magX * sin(-1 * angleDiff) + missileV.magY * cos(-1 * angleDiff));
                return newV;
            }
            break;
        case 2:
            // Vector invertV(missileV.posX, missileV.posY, -1 * missileV.posX, -1 * missileV.posY);
            if (guideV.magX > invertV.magX)
            { // clock
                if (angleDiff >= maxTurn)
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(maxTurn) - missileV.magY * sin(maxTurn), missileV.magX * sin(maxTurn) + missileV.magY * cos(maxTurn));
                    return newV;
                }
                else
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(angleDiff) - missileV.magY * sin(angleDiff), missileV.magX * sin(angleDiff) + missileV.magY * cos(angleDiff));
                    return newV;
                }
            }
            else
            { // counter clock
                if (angleDiff >= maxTurn)
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * maxTurn) - missileV.magY * sin(-1 * maxTurn), missileV.magX * sin(-1 * maxTurn) + missileV.magY * cos(-1 * maxTurn));
                    return newV;
                }
                else
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * angleDiff) - missileV.magY * sin(-1 * angleDiff), missileV.magX * sin(-1 * angleDiff) + missileV.magY * cos(-1 * angleDiff));
                    return newV;
                }
            }
            break;
        case 3:
            if (angleDiff >= maxTurn) // clockwsie
            {
                Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(maxTurn) - missileV.magY * sin(maxTurn), missileV.magX * sin(maxTurn) + missileV.magY * cos(maxTurn));
                return newV;
            }
            else
            {
                Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(angleDiff) - missileV.magY * sin(angleDiff), missileV.magX * sin(angleDiff) + missileV.magY * cos(angleDiff));
                return newV;
            }
            break;
        case 4:
            if (guideV.magX < missileV.magX)
            { // clock
                if (angleDiff >= maxTurn)
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(maxTurn) - missileV.magY * sin(maxTurn), missileV.magX * sin(maxTurn) + missileV.magY * cos(maxTurn));
                    return newV;
                }
                else
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(angleDiff) - missileV.magY * sin(angleDiff), missileV.magX * sin(angleDiff) + missileV.magY * cos(angleDiff));
                    return newV;
                }
            }
            else
            { // counter clock
                if (angleDiff >= maxTurn)
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * maxTurn) - missileV.magY * sin(-1 * maxTurn), missileV.magX * sin(-1 * maxTurn) + missileV.magY * cos(-1 * maxTurn));
                    return newV;
                }
                else
                {
                    Vector newV(missileV.posX, missileV.posY, missileV.magX * cos(-1 * angleDiff) - missileV.magY * sin(-1 * angleDiff), missileV.magX * sin(-1 * angleDiff) + missileV.magY * cos(-1 * angleDiff));
                    return newV;
                }
            }
            break;
        }
        break;
    }
    return missileV;
}

Vector missileGuideV(Vector targetV, Vector missileV, double maxTurn)
{
    // create the LOS vector
    Vector losV(missileV.posX, missileV.posY, targetV.posX - missileV.posX, targetV.posY - missileV.posY);

    // calculate the "t" that leads to the intersect coordinate
    // does this by parameterizing the LOS vector and using it to solve the equation of circle quadratically
    double a = pow(losV.magX, 2) + pow(losV.magY, 2);

    double b = (2 * (losV.magX) * (losV.posX - targetV.posX)) + (2 * (losV.magY) * (losV.posY - targetV.posY));

    double c = pow((losV.posX - targetV.posX), 2) + pow((losV.posY - targetV.posY), 2) - pow(sqrt(pow(missileV.magX, 2) + pow(missileV.magY, 2)), 2);

    double t = (2 * c) / ((-1 * b) + sqrt(pow(b, 2) - (4 * a * c))); // muller's method ignoring the larger case

    // use said "t" to create a new vector from the tail of the missile vector with magnitude that intercepts the head of the target
    Vector guideV(missileV.magX, missileV.magY, (targetV.posX + targetV.magX) - (losV.posX + (losV.magX * t)), (targetV.posY + targetV.magY) - (losV.posY + (losV.magY * t)));

    return guideV;
}

double LOSRatio(Vector targetV, Vector missileV)
{
    Vector losV(missileV.posX, missileV.posY, targetV.posX - missileV.posX, targetV.posY - missileV.posY);

    double a = pow(losV.magX, 2) + pow(losV.magY, 2);

    double b = (2 * (losV.magX) * (losV.posX - targetV.posX)) + (2 * (losV.magY) * (losV.posY - targetV.posY));

    double c = pow((losV.posX - targetV.posX), 2) + pow((losV.posY - targetV.posY), 2) - pow(sqrt(pow(missileV.magX, 2) + pow(missileV.magY, 2)), 2);

    double t = (2 * c) / ((-1 * b) + sqrt(pow(b, 2) - (4 * a * c))); // muller's method ignoring the larger case

    Vector tVector(0, 0, targetV.posX - (losV.posX + (losV.magX * t)), targetV.posY - (losV.posY + (losV.magY * t)));

    double losVLength = sqrt(pow(losV.magX, 2) + pow(losV.magY, 2));
    double TVecLength = sqrt(pow(tVector.magX, 2) + pow(tVector.magY, 2));

    return losVLength / TVecLength;
}

Vector posUpdate(Vector vector)
{
    vector.posX += secondToFrame(vector.magX);
    vector.posY += secondToFrame(vector.magY);

    return vector;
}

int main()
{

    double maxTurn = secondToFrame(22); // degrees per second

    Vector targetV(0, 0, 45, 45);
    Vector missileV(500, 800, 0, -100);

    sf::RenderWindow window(sf::VideoMode(1000, 800), "ProNav Simulation");
    window.setPosition(sf::Vector2i(0, 0));
    window.setFramerateLimit(60);

    sf::CircleShape target; // target
    target.setRadius(14);
    target.setFillColor(sf::Color::Red);
    target.setOrigin(7, 7);

    sf::CircleShape circle; // missile
    circle.setRadius(6);
    circle.setFillColor(sf::Color::Blue);
    circle.setOrigin(3, 3);

    sf::CircleShape interceptTarget; // intercept point according to target
    interceptTarget.setRadius(2);
    interceptTarget.setFillColor(sf::Color::White);
    interceptTarget.setOrigin(1, 1);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();

        double targetX = targetV.posX;
        double targetY = targetV.posY;
        target.setPosition(targetX, targetY);
        window.draw(target);

        double missileX = missileV.posX;
        double missileY = missileV.posY;
        circle.setPosition(missileX, missileY);
        window.draw(circle);

        double interceptRatio = LOSRatio(targetV, missileV);
        // cout << "\n" << "intercept ratio: " << interceptRatio;

        // intercept according to target
        double interceptTx = targetV.posX + (targetV.magX * interceptRatio);
        double interceptTy = targetV.posY + (targetV.magY * interceptRatio);
        interceptTarget.setPosition(interceptTx, interceptTy);
        window.draw(interceptTarget);
        
        window.display();

        //updates
        targetV = posUpdate(targetV);
        Vector guideV = missileGuideV(targetV, missileV, maxTurn);
        missileV = posUpdate(rotate(missileV, guideV, maxTurn, getAngle(guideV, missileV)));
    }
    return 0;
}