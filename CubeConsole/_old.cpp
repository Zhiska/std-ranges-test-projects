#include <math.h>
#include <stdio.h>
#include <string.h>
#include <io.h>
#include <thread>
#include <chrono>
#include <ranges>

#include "Timer.cpp"

float A, B, C;

float cubeWidth = 20;
int width = 160, height = 44;
float zBuffer[160 * 44];
char buffer[160 * 44];
int backgroundASCIICode = ' ';
int distanceFromCam = 100;
float horizontalOffset;

float tStep = 0.6;

float x, y, z;
float rz;
int xp, yp;
int idx;

float NewX(int i, int j, int k) {
    return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) +
        j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

float NewY(int i, int j, int k) {
    return j * cos(A) * cos(C) + k * sin(A) * cos(C) -
        j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) -
        i * cos(B) * sin(C);
}

float NewZ(int i, int j, int k) {
    return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}

void GetSide(float cubeX, float cubeY, float cubeZ, int ch) {

    x = NewX(cubeX, cubeY, cubeZ);
    y = NewY(cubeX, cubeY, cubeZ);
    z = NewZ(cubeX, cubeY, cubeZ) + distanceFromCam;  rz = 1 / z;

    // 16 from left
    xp = (int)(width / 2 + horizontalOffset + 60 * rz * x);
    yp = (int)(height / 2 + 30 * rz * y);

    idx = xp + yp * width;
    if (idx >= 0 && idx < width * height) {
        if (rz > zBuffer[idx]) {
            zBuffer[idx] = rz;
            buffer[idx] = ch;
        }
    }
}

int main() {
    printf("\x1b[2J");  // console mode

    unsigned loop{};

    {
        Timer timer;
        while (loop < 20) {
            system("cls");
            memset(buffer, backgroundASCIICode, width * height);
            memset(zBuffer, 0, width * height * 4);

            cubeWidth = 24;
            horizontalOffset = -2 * cubeWidth;

            for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += tStep) {
                for (float cubeY = -cubeWidth; cubeY < cubeWidth;
                    cubeY += tStep) {
                    GetSide(cubeX, cubeY, -cubeWidth, '@');
                    GetSide(cubeWidth, cubeY, cubeX, '$');
                    GetSide(-cubeWidth, cubeY, -cubeX, '~');
                    GetSide(-cubeX, cubeY, cubeWidth, '#');
                    GetSide(cubeX, -cubeWidth, -cubeY, ';');
                    GetSide(cubeX, cubeWidth, cubeY, '+');
                }
            }
            cubeWidth = 32;
            horizontalOffset = 6 * cubeWidth;
            // second cube
            for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += tStep) {
                for (float cubeY = -cubeWidth; cubeY < cubeWidth;
                    cubeY += tStep) {
                    GetSide(cubeX, cubeY, -cubeWidth, '@');
                    GetSide(cubeWidth, cubeY, cubeX, '$');
                    GetSide(-cubeWidth, cubeY, -cubeX, '~');
                    GetSide(-cubeX, cubeY, cubeWidth, '#');
                    GetSide(cubeX, -cubeWidth, -cubeY, ';');
                    GetSide(cubeX, cubeWidth, cubeY, '+');
                }
            }

            printf("\x1b[H");
            for (int k{}; k < width * height; k++)
                putchar(k % width ? buffer[k] : 10);

            A += 0.0625;
            B += 0.125;
            C += 0.03125;

            loop++;
        }
    }
    return 0;
}
