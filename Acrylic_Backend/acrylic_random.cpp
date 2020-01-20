//
// Created by coolh on 1/8/2020.
//

#include "acrylic_random.h"

    std::random_device generator; // how generates the random number
    std::uniform_int_distribution <int> distribution(0,256); // range for RGB
    std::uniform_int_distribution <int> distribute(0,99); // range for SV
    std::uniform_int_distribution <int> distrib(0,359); // range for H

    glm::vec3 A2D::Random::Random::ranRGB()
    {
        return glm::vec3(distribution(generator), distribution(generator), distribution(generator));
    } // generates the RGB

    glm::vec3 A2D::Random::Random::ranHSV()
    {
        return glm::vec3(distrib(generator), distribute(generator), distribute(generator));
    } // generates the HSV

    glm::vec3 A2D::Random::Random::RGBtoHSV(glm::vec3 rgb) {
        float fH; // hue
        float fS; // saturation
        float fV; // value
        float fR = rgb.x; // red %
        float fG = rgb.y; // green %
        float fB = rgb.z; // blue %
        float fCMax = std::fmax(std::fmax(fR, fG), fB); // max value
        float fCMin = std::fmin(std::fmin(fR, fG), fB); // min value
        float fDelta = fCMax - fCMin; // the difference in the max and min

        if(fDelta > 0) { // checks if fDelta is positive
            if(fCMax == fR) {  //checks the max against red color value
                fH = 60 * (fmod(((fG - fB) / fDelta), 6)); // calculates the hue value
            }
            else if(fCMax == fG) { //checks the max against green color value if not red
                fH = 60 * (((fB - fR) / fDelta) + 2); // calculates the hue value
            }
            else if(fCMax == fB) {  //checks the max against blue color value if not red or green
                fH = 60 * (((fR - fG) / fDelta) + 4);// calculates the hue value
            }

            if(fCMax > 0) { // checks that fCMax is positive
                fS = fDelta / fCMax; // if it is S is the difference divided by the max
            }
            else {
                fS = 0; // S becomes 0
            }

            fV = fCMax; // fV is fCMax if fDelta is positive
        }
        else {
            fH = 0; // if fDelta is 0 then fH and fS are 0
            fS = 0;
            fV = fCMax;
        }

        if(fH < 0) {
            fH = 360 + fH; // if fH is negative add 360 
        }
        return glm::vec3(fH, fS, fV); // returns the conversion
    }
    glm::vec3 A2D::Random::Random::HSVtoRGB(glm::vec3 hsv){
        float fH = hsv.x;
        float fS = hsv.y;
        float fV = hsv.z;
        float fR;
        float fG;
        float fB;
        float fC = fV * fS; // Chroma
        float fHPrime = fmod(fH / 60.0, 6);
        float fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
        float fM = fV - fC;

        if(0 <= fHPrime && fHPrime < 1) {
            fR = fC;
            fG = fX;
            fB = 0;
        } else if(1 <= fHPrime && fHPrime < 2) {
            fR = fX;
            fG = fC;
            fB = 0;
        } else if(2 <= fHPrime && fHPrime < 3) {
            fR = 0;
            fG = fC;
            fB = fX;
        } else if(3 <= fHPrime && fHPrime < 4) {
            fR = 0;
            fG = fX;
            fB = fC;
        } else if(4 <= fHPrime && fHPrime < 5) {
            fR = fX;
            fG = 0;
            fB = fC;
        } else if(5 <= fHPrime && fHPrime < 6) {
            fR = fC;
            fG = 0;
            fB = fX;
        } else {
            fR = 0;
            fG = 0;
            fB = 0;
        }

        fR += fM;
        fG += fM;
        fB += fM;
        return glm::vec3(fR, fG,fB);
    }




