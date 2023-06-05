class Vector{
    public:

    int posX;
    int posY;

    int magX;
    int magY;

    Vector(){
        posX = 0;
        posY = 0;

        magX = 1;
        magY = 1; 
    }

    Vector(int x, int y, int mx, int my){
        posX = x;
        posY = y;

        magX = mx;
        magY = my;
    }
};