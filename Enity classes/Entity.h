//
// Created by jimmy on 9/18/2019.
//

#ifndef GITHUB_ENTITY_H
#define GITHUB_ENTITY_H
struct sheetLocation{
    int xStart, xEnd;
    int yStart, yEnd;
};

class Entity {
    private:
        //going to be array if multiple sprites are needed
        sheetLocation* sheetPositions;
        int activeSprite;
        double xPosition;
        double yPosition;
    public:
        int getActiveSprite(){
            return activeSprite;
        }

        sheetLocation* getSheetLocation(){
            return sheetPositions;
        }

        double getXPosition(){
            return xPosition;
        }

        double getYPosition(){
            return yPosition;
        }

        void setActiveSprite(int sprite){
            activeSprite = sprite;
        }

        void setXPosition(int xCoord){
            xPosition = xCoord;
        }

        void setYPosition(int yCoord){
            yPosition = yCoord;
        }

        Entity(){

        }
};


#endif //GITHUB_ENTITY_H
