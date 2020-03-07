//
// Created by coolh on 1/8/2020.
//

#include "acrylic_random.h"

    std::random_device generator; // how generates the random number
    std::uniform_int_distribution <int> distribution(0,255); // range for R,G,B
    std::uniform_int_distribution <int> distribute(0,100); // range for S,V
    std::uniform_int_distribution <int> distrib(0,360); // range for H


    int A2D::Random::Random::WeightedRandom(int Weights[])
    {
        int length = sizeof(Weights) / sizeof(Weights[0]);
        int total = 0;
        for(int i = 0; i < length; i++)
        {
            total += Weights[i];
        }
        std::uniform_int_distribution <int> w(0,total); // generates a number for weighted
        int value = w(generator); // sets it to value
        total = 0;
        for(int i = 0; i < length; i++)
        {
            total += Weights[i];
            if(value < total)
            {
                return i; // prints the random number
            }
        }
        return -1; //failure
    }

    glm::vec3 A2D::Random::Random::ranRGB()
    {
        return glm::vec3(distribution(generator), distribution(generator), distribution(generator));
    } // generates the RGB

    glm::vec3 A2D::Random::Random::ranHSV()
    {
        return glm::vec3(distrib(generator), distribute(generator), distribute(generator));
    } // generates the HSV

    glm::vec3 A2D::Random::Random::RGBtoHSV(glm::vec3 rgb) {
        float Hue; // hue
        float Saturation; // saturation
        float Brightness; // value
        float red = rgb.x; // red %
        float green = rgb.y; // green %
        float blue = rgb.z; // blue %
        float maxValue = std::fmax(std::fmax(red, green), blue); // max value
        float minValue = std::fmin(std::fmin(red, green), blue); // min value
        float delta = maxValue - minValue; // the difference in the max and min

        if(delta > 0) { // checks if delta is positive
            if(maxValue == red) {  //checks the max against red color value
                Hue = 60 * (fmod(((green - blue) / delta), 6)); // calculates the hue value
            }
            else if(maxValue == green) { //checks the max against green color value if not red
                Hue = 60 * (((blue - red) / delta) + 2); // calculates the hue value
            }
            else if(maxValue == blue) {  //checks the max against blue color value if not red or green
                Hue = 60 * (((red - green) / delta) + 4);// calculates the hue value
            }

            if(maxValue > 0) { // checks that maxValue is positive
                Saturation = delta / maxValue; // if it is S is the difference divided by the max
            }
            else {
                Saturation = 0; // S becomes 0
            }

            Brightness = maxValue; // Brightness is maxValue if delta is positive
        }
        else {
            Hue = 0; // if delta is 0 then Hue and Saturation are 0
            Saturation = 0;
            Brightness = maxValue;
        }

        if(Hue < 0) {
            Hue = 360 + Hue; // if Hue is negative add 360
        }
        return glm::vec3(Hue, Saturation, Brightness); // returns the conversion
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




