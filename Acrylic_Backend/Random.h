//
// Created by coolh on 1/8/2020.
//
// Copyright (c) 2014, Jan Winkler <winkler@cs.uni-bremen.de>
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Universität Bremen nor the names of its
//       contributors may be used to endorse or promote products derived from
//       this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

/* Author: Jan Winkler */

#ifndef ACRYLIC2D_RANDOM_H
#define ACRYLIC2D_RANDOM_H
#include <iostream>
#include <cstdlib>
#include <tuple>
#include <glm/glm.hpp>


class Random {
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

    glm::vec3 HSVtoRGB( glm::vec3 hsv){
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

};

#endif