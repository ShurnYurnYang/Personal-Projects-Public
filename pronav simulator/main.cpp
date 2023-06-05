#include <string>
#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
using namespace std;

/*
to do

basically

find absolute vectors of the target and the missile

tail to tip the missile vector to the target vector -> set pos of m to tip of t (1 time unit)

use the missile vector as the radius of a cricle and find the intersection of said circle to the LOS vector -> create eq of circle x^2 + y^2 = r^2 with r as speed -> find intersection of LOS vector and circle by paramterizing the LOS vector then sub the x, y of circle with parameterized LOS -> produces position

draw the missile vector from the intercept back to the tip of the target vector -> gives us a new vector

orient the missile towards said new vector -> find the bearing of the new vector and change the bearing of the missile by x degrees until it matches the correct vector

to calculate impact point find the ratio of the LOS portion of the intersect triangle and the real triangle

use the ratio to calculate the POI by simply mulipying the real missile vector by the ratio

seems simple enough :)

TECHNICALLY ALL VALUES SHOULD BE RELATIVE TO THE MISSILE POS
*/

class Vector
{
public:
    int posX;
    int posY;

    int magX;
    int magY;

    Vector()
    {
        posX = 0;
        posY = 0;

        magX = 1;
        magY = 1;
    }

    Vector(int x, int y, int mx, int my)
    {
        posX = x;
        posY = y;

        magX = mx;
        magY = my;
    }
};

double getBearing(Vector vector);

double getBearing(Vector vector) // should probably switch these to cases
{
    cout << "\n vectorX " << vector.magX;
    cout << "\n vectorY " << vector.magY;
    double raw = (atan2(vector.magX, vector.magY) * (180 / M_PI));
    cout << "\n raw: " << raw;
    if (vector.magX < 0)
    {
        if (vector.magY < 0)
        {
            return raw + 180;
        }
        else if (vector.magY > 0)
        {
            return 180 + raw;
        }
        else
        {
            return 90;
        }
    }
    else if (vector.magX > 0)
    {
        if (vector.magY < 0)
        {
            return 180 + raw;
        }
        else if (vector.magY > 0)
        {
            return 180 - raw;
        }
        else
        {
            return 270;
        }
    }
    else
    {
        if (vector.magY < 0)
        {
            return 0;
        }
        else
        {
            return 180;
        }
    }

    return raw;
}

int getMagCX(double speed, double bearing);

int getMagCX(double speed, double bearing) // should probably switch these to cases
{
    bearing = bearing * (M_PI) / 180;
    if (bearing >= 0 && bearing <= 90)
    {
        return -1 * round(speed * sin(bearing));
    }
    if (bearing > 90 && bearing <= 180)
    {
        return -1 * round(speed * cos(bearing - 90));
    }
    if (bearing > 180 && bearing <= 270)
    {
        return round(speed * sin(bearing - 180));
    }
    else
    {
        return round(speed * cos(bearing - 270));
    }
}

int getMagCY(double speed, double bearing);

int getMagCY(double speed, double bearing) // should probably switch these to cases
{
    bearing = bearing * (M_PI) / 180;
    if (bearing >= 0 && bearing <= 90)
    {
        return -1 * round(speed * cos(bearing));
    }
    if (bearing > 90 && bearing <= 180)
    {
        return round(speed * sin(bearing - 90));
    }
    if (bearing > 180 && bearing <= 270)
    {
        return round(speed * cos(bearing - 180));
    }
    else
    {
        return -1 * round(speed * sin(bearing - 270));
    }
}

double getSpeed(Vector vector);

double getSpeed(Vector vector)
{
    return sqrt(pow(vector.magX, 2) + pow(vector.magY, 2));
}

Vector missileGuideV(Vector targetV, Vector missileV, int maxTurn);

Vector missileGuideV(Vector targetV, Vector missileV, int maxTurn)
{

    // create the LOS vector
    Vector losV(missileV.posX, missileV.posY, targetV.posX - missileV.posX, targetV.posY - missileV.posY);

    // calculate the "t" that leads to the intersect coordinate
    // does this by parameterizing the LOS vector and using it to solve the equation of circle quadratically
    int a = pow(losV.magX, 2) + pow(losV.magY, 2);

    int b = (2 * (losV.magX) * (losV.posX - targetV.posX)) + (2 * (losV.magY) * (losV.posY - targetV.posY));

    int c = pow((losV.posX - targetV.posX), 2) + pow((losV.posY - targetV.posY), 2) - pow(sqrt(pow(missileV.magX, 2) + pow(missileV.magY, 2)), 2);

    double t = (2 * c) / ((-1 * b) + sqrt(pow(b, 2) - (4 * a * c))); // muller's method ignoring the larger case

    // use said "t" to create a new vector from the intersect to the target vector tip
    Vector guideV(round(losV.posX + (losV.magX * t)), round(losV.posY + (losV.magY * t)), (targetV.posX + targetV.magX) - round(losV.posX + losV.magX * t), (targetV.posY + targetV.magY) - round(losV.posY + losV.magY * t));

    // get the bearing of the guide vector
    double guideBr = getBearing(guideV);

    // get the bearing of the missile vector
    double missileBr = getBearing(missileV);

    // subtract the bearings to get the differential
    double diff = guideBr - missileBr;

    cout << "\n magX: " << guideV.magX;
    cout << "\n magY: " << guideV.magY;
    cout << "\n guide bearing: " << guideBr;
    cout << "\n bearing: " << missileBr;
    cout << "\n diff: " << diff;

    // determine which way to turn and set the bearing of the missile vector as such
    if (diff <= 180)
    { // turn right (add degrees) to bearing
        if (diff >= maxTurn)
        {
            missileBr += maxTurn;
        }
        else
        {
            missileBr += diff;
        }
    }
    else
    { // turn left (subtract degrees to bearing)
        if (diff >= maxTurn)
        {
            missileBr -= maxTurn;
        }
        else
        {
            missileBr -= diff;
        }
    } // now missileV has the proper bearing in the form of missileBr which must be then translated back into vector coords

    cout << "\n new bearing: " << missileBr;

    double speed = getSpeed(missileV); // this gives the absolute speed of the missille which can be translated into coords using the baering to maintain constant speed

    if (missileBr < 0)
    {
        missileBr = 360 + missileBr;
    }
    else if (missileBr > 360)
    {
        missileBr = missileBr - 360;
    }

    Vector returnV(missileV.posX, missileV.posY, getMagCX(speed, missileBr), getMagCY(speed, missileBr)); // gives the new EXACT vector of the missile
    cout << "\n new magX: " << returnV.magX;
    cout << "\n new magY: " << returnV.magY;
    cout << "\n";
    return returnV;
}

Vector posUpdate(Vector vector)
{
    vector.posX += vector.magX;
    vector.posY += vector.magY;

    return vector;
}

int main()
{

    Vector targetV(10, 10, 6, 1);
    Vector missileV(1200, 1000, -1, -20);

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "ProNav Simulation");
    window.setPosition(sf::Vector2i(0, 0));
    window.setFramerateLimit(60);

    sf::RectangleShape rect; // target
    rect.setSize(sf::Vector2f(30, 10));
    rect.setFillColor(sf::Color::Red);

    sf::CircleShape circle; // missile
    circle.setRadius(5);
    circle.setFillColor(sf::Color::Blue);

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

        int rectX = targetV.posX;
        int rectY = targetV.posY;
        rect.setPosition(rectX, rectY);
        window.draw(rect);

        targetV.posX = posUpdate(targetV).posX;
        targetV.posY = posUpdate(targetV).posY;

        int circleX = missileV.posX;
        int circleY = missileV.posY;
        circle.setPosition(circleX, circleY);
        window.draw(circle);

        Vector absoluteV = missileGuideV(targetV, missileV, 80);

        missileV.posX = posUpdate(absoluteV).posX;
        missileV.posY = posUpdate(absoluteV).posY;

        // missileV.posX = posUpdate(missileGuideV(targetV, missileV, 1)).posX;
        // missileV.posY = posUpdate(missileGuideV(targetV, missileV, 1)).posY;

        window.display();
    }

    return 0;
}