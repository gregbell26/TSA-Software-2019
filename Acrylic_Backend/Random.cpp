//
// Created by coolh on 1/8/2020.
//

#include "Random.h"
static glm::vec3 ranRGB()
{
    return glm::vec3(std::rand()%257, std::rand()%257, std::rand()%257);
}
    static glm::vec3 ranHSV()
    {
        return glm::vec3(std::rand()%360, std::rand()%100, std::rand()%100);
    }

    glm::vec3 RGBtoHSV(glm::vec3 rgb) {
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



