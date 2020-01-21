//
// Created by coolh on 1/8/2020.
//

#include "acrylic_random.h"

    std::random_device generator; // how generates the random number
    std::uniform_int_distribution <int> distribution(0,256); // range for RGB
    std::uniform_int_distribution <int> distribute(0,99); // range for SV
    std::uniform_int_distribution <int> distrib(0,360); // range for H

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
        float hue = hsv.x;
        float saturation = hsv.y;
        float brightness = hsv.z;
        float red;
        float green;
        float blue;
        float colorIntensity = brightness * saturation;
        float RemainderHue =  fmod(hue / 60.0, 6); // remainder of (hue/60)/6
        float Intensity2 = colorIntensity * (1 - fabs(fmod(RemainderHue, 2) - 1)); // intensity*(1-|remainder(remain/2)-1|)
        float IntensityOffset = brightness - colorIntensity; // added to red green and blue to complete conversion

        if(0 <= RemainderHue && RemainderHue < 1) { // checks the remainder of hue
            red = colorIntensity; // sets red,green, blue colors
            green = Intensity2;
            blue = 0;
        }
        else if(1 <= RemainderHue && RemainderHue < 2) {
            red = Intensity2;
            green = colorIntensity;
            blue = 0;
        }
        else if(2 <= RemainderHue && RemainderHue < 3) {
            red = 0;
            green = colorIntensity;
            blue = Intensity2;
        }
        else if(3 <= RemainderHue && RemainderHue < 4) {
            red = 0;
            green = Intensity2;
            blue = colorIntensity;
        }
        else if(4 <= RemainderHue && RemainderHue < 5) {
            red = Intensity2;
            green = 0;
            blue = colorIntensity;
        }
        else if(5 <= RemainderHue && RemainderHue < 6) {
            red = colorIntensity;
            green = 0;
            blue = Intensity2;
        }
        else {
            red = 0;
            green = 0;
            blue = 0;
        }

        red += IntensityOffset;
        green += IntensityOffset;
        blue += IntensityOffset;
        return glm::vec3(red, green, blue); // returns converted RGB
    }




