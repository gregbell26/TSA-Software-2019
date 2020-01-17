//
// Created by coolh on 1/8/2020.
//

#include "Random.h"

    std::default_random_engine generator;

    glm::vec3 A2D::Random::Random::ranRGB()
    {
        return glm::vec3(std::uniform_int_distribution(0,256), std::uniform_int_distribution(0,256), std::uniform_int_distribution(0,256));
    }

    glm::vec3 A2D::Random::Random::ranHSV()
    {
        return glm::vec3(std::uniform_int_distribution(0,359), std::uniform_int_distribution(0,99), std::uniform_int_distribution(0,99));
    }

glm::vec3 A2D::Random::Random::RGBtoHSV(glm::vec3 rgb) {
        float fH;
        float fS;
        float fV;
        float fR = rgb.x;
        float fG = rgb.y;
        float fB = rgb.z;
        float fCMax = std::fmax(std::fmax(fR, fG), fB);
        float fCMin = std::fmin(std::fmin(fR, fG), fB);
        float fDelta = fCMax - fCMin;

        if(fDelta > 0) {
            if(fCMax == fR) {
                fH = 60 * (fmod(((fG - fB) / fDelta), 6));
            } else if(fCMax == fG) {
                fH = 60 * (((fB - fR) / fDelta) + 2);
            } else if(fCMax == fB) {
                fH = 60 * (((fR - fG) / fDelta) + 4);
            }

            if(fCMax > 0) {
                fS = fDelta / fCMax;
            } else {
                fS = 0;
            }

            fV = fCMax;
        } else {
            fH = 0;
            fS = 0;
            fV = fCMax;
        }

        if(fH < 0) {
            fH = 360 + fH;
        }
        return glm::vec3(fH, fS, fV);
    }
    glm::vec3 A2D::Random::Random::HSVtoRGB( glm::vec3 hsv){
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




