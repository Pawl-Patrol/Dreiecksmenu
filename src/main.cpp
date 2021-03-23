#include "converters.hpp"
#include "interaction.hpp"
#include "math.hpp"
#include "draw.hpp"
#include "bitmaps.hpp"

#include <fxcg/display.h>
#include <fxcg/keyboard.h>

#define FONT_HEIGHT 18
#define STATUS_AREA_HEIGHT 25

const char degree[1] = {-100};

const char* congruence[5] = {"3 Seiten", "2 Seiten 1 Winkel", "2 Winkel 1 Seite", "3 Punkte"};
const char* angle[3] = {"Alpha", "Beta", "Gamma"};
const char* side[3] = {"Seite a", "Seite b", "Seite c"};
const char* angles[3] = {"Alpha & Beta", "Alpha & Gamma", "Beta & Gamma"};
const char* sides[3] = {"Seite a & b", "Seite a & c", "Seite b & c"};
const char* dimensions[2] = {"2D", "3D"};

bool emptyValue;

void showCredits()
{
    int x = 0;
    int y = 0;
    PrintMini(&x, &y, "Version 1.3", 0x02, LCD_WIDTH_PX, 0, 0, COLOR_BLUE, 0, 1, 0);
    x = 0;
    y += FONT_HEIGHT;
    PrintMini(&x, &y, "Erstellt am 21.03.2021", 0x02, LCD_WIDTH_PX, 0, 0, COLOR_BLUE, 0, 1, 0);
    x = 0;
    y += FONT_HEIGHT + 15;
    PrintMini(&x, &y, "Dieses Programm benutzt Taylor-", 0x02, LCD_WIDTH_PX, 0, 0, COLOR_BLACK, 0, 1, 0);
    x = 0;
    y += FONT_HEIGHT;
    PrintMini(&x, &y, "reihen zur Annaeherung der Wurzel", 0x02, LCD_WIDTH_PX, 0, 0, COLOR_BLACK, 0, 1, 0);
    x = 0;
    y += FONT_HEIGHT;
    PrintMini(&x, &y, "und trigonometrischer Funktionen.", 0x02, LCD_WIDTH_PX, 0, 0, COLOR_BLACK, 0, 1, 0);
    x = 0;
    y += FONT_HEIGHT;
    PrintMini(&x, &y, "Es unterliegt daher Rundungsfehlern.", 0x02, LCD_WIDTH_PX, 0, 0, COLOR_BLACK, 0, 1, 0);
    x = 0;
    y += FONT_HEIGHT;
    PrintMini(&x, &y, "Benutzen auf eigene Gefahr!", 0x02, LCD_WIDTH_PX, 0, 0, COLOR_RED, 0, 1, 0);
    x = 0;
    y += FONT_HEIGHT + 15;
    PrintMini(&x, &y, "https://github.com/Pawl-Patrol", 0x02, LCD_WIDTH_PX, 0, 0, COLOR_BLACK, 0, 1, 0);
    int key;
    GetKey(&key);
    Bdisp_Fill_VRAM(COLOR_WHITE, 1);
}

void printFloat(int *x, int *y, float f, int maxlen)
{
    PrintMini(x, y, ftoa(f, 3), 0x02, maxlen, 0, 0, COLOR_BLACK, 0, 1, 0);
}

float getValue(const char* msg, int y)
{
    PrintXY(1, y, msg, TEXT_MODE_NORMAL, TEXT_COLOR_BLUE);
    char buffer[25] = "";
    int key = getTextLine(buffer, 24, 1, y + 1, 22, INPUT_MODE_FLOAT);
    return atof(buffer);
}

int triangle(int choice)
{
    double a, b, c, alpha, beta, gamma, buf, ax, ay, az, bx, by, bz, cx, cy, cz;
    int key, sel1, sel2;
    switch (choice)
    {
    case 0:
        a = getValue("  Seite a?", 1);
        b = getValue("  Seite b?", 3);
        c = getValue("  Seite c?", 5);
        three_sides(a, b, c, &alpha, &beta, &gamma);
        break;
    case 1:
        sel1 = getChoice("  Welche Seiten?", sides, 3);
        sel2 = getChoice("  Welcher Winkel?", angle, 3);
        if (sel1 == -1 || sel2 == -1)
        {
            return 57;
        }
        if (sel1 == 0)
        {
            a = getValue("  Seite a?", 1);
            b = getValue("  Seite b?", 3);
        }
        else if (sel1 == 1)
        {
            a = getValue("  Seite a?", 1);
            c = getValue("  Seite c?", 3);
        }
        else if (sel1 == 2)
        {
            b = getValue("  Seite b?", 1);
            c = getValue("  Seite c?", 3);
        }
        if (sel2 == 0)
        {
            alpha = getValue("  Alpha?", 5);
        }
        else if (sel2 == 1)
        {
            beta = getValue("  Beta?", 5);
        }
        else if (sel2 == 2)
        {
            gamma = getValue("  Gamma?", 5);
        }
        if (sel1 == 0)
        {
            if (sel2 == 0)
            {
                beta = sin_angle(alpha, a, b);
                gamma = 180 - alpha - beta;
                c = sin_side(a, alpha, gamma);
            }
            else if (sel2 == 1)
            {
                alpha = sin_angle(beta, b, a);
                gamma = 180 - alpha - beta;
                c = sin_side(b, beta, gamma);
            }
            else if (sel2 == 2)
            {
                c = cos_side(a, b, gamma);
                if (a < b)
                {
                    alpha = sin_angle(gamma, c, a);
                    beta = 180 - alpha - gamma;
                }
                else
                {
                    beta = sin_angle(gamma, c, b);
                    alpha = 180 - beta - gamma;
                }
            }
        }
        else if (sel1 == 1)
        {
            if (sel2 == 0)
            {
                gamma = sin_angle(alpha, a, c);
                beta = 180 - alpha - gamma;
                b = sin_side(a, alpha, beta);
            }
            else if (sel2 == 1)
            {
                b = cos_side(a, c, beta);
                if (a < c)
                {
                    alpha = sin_angle(beta, b, a);
                    gamma = 180 - alpha - beta;
                }
                else
                {
                    gamma = sin_angle(beta, b, c);
                    alpha = 180 - beta - gamma;
                }
            }
            else if (sel2 == 2)
            {
                alpha = sin_angle(gamma, c, a);
                beta = 180 - alpha - gamma;
                b = sin_side(c, gamma, beta);
            }
        }
        else if (sel1 == 2)
        {
            if (sel2 == 0)
            {
                a = cos_side(b, c, alpha);
                if (b < c)
                {
                    beta = sin_angle(alpha, a, b);
                    gamma = 180 - alpha - beta;
                }
                else
                {
                    gamma = sin_angle(alpha, a, c);
                    beta = 180 - alpha - gamma;
                }
            }
            else if (sel2 == 1)
            {
                gamma = sin_angle(beta, b, c);
                alpha = 180 - beta - gamma;
                a = sin_side(b, beta, alpha);
            }
            else if (sel2 == 2)
            {
                alpha = sin_angle(gamma, c, a);
                beta = 180 - alpha - gamma;
                a = sin_side(c, gamma, alpha);
            }
        }
        break;
    case 2:
        sel1 = getChoice("  Welche Winkel?", angles, 3);
        sel2 = getChoice("  Welche Seite?", side, 3);
        if (sel1 == -1 || sel2 == -1)
        {
            return 57;
        }
        if (sel1 == 0)
        {
            alpha = getValue("  Alpha?", 1);
            beta = getValue("  Beta?", 3);
            gamma = 180 - alpha - beta;
        }
        else if (sel1 == 1)
        {
            alpha = getValue("  Alpha?", 1);
            gamma = getValue("  Gamma?", 3);
            beta = 180 - alpha - gamma;
        }
        else if (sel1 == 2)
        {
            beta = getValue("  Beta?", 1);
            gamma = getValue("  Gamma?", 3);
            alpha = 180 - beta - gamma;
        }
        if (sel2 == 0)
        {
            a = getValue("  Seite a?", 5);
        }
        else if (sel2 == 1)
        {
            b = getValue("  Seite b?", 5);
        }
        else if (sel2 == 2)
        {
            c = getValue("  Seite c?", 5);
        }
        if (sel2 == 0)
        {
            b = sin_side(a, alpha, beta);
            c = sin_side(a, alpha, gamma);
        }
        else if (sel2 == 1)
        {
            a = sin_side(b, beta, alpha);
            c = sin_side(b, beta, gamma);
        }
        else if (sel2 == 2)
        {
            a = sin_side(c, gamma, alpha);
            b = sin_side(c, gamma, beta);
        }
        break;
    case 3:
        sel1 = getChoice("  Dimensionen?", dimensions, 2);
        if (sel1 == -1)
        {
            return 57;
        }
        ax = getValue("  x von A?", 1);
        ay = getValue("  y von A?", 3);
        if (sel1)
        {
            az = getValue("  z von A?", 5);
        }
        Bdisp_Fill_VRAM(COLOR_WHITE, 1);
        bx = getValue("  x von B?", 1);
        by = getValue("  y von B?", 3);
        if (sel1)
        {
            bz = getValue("  z von B?", 5);
        }
        Bdisp_Fill_VRAM(COLOR_WHITE, 1);
        cx = getValue("  x von C?", 1);
        cy = getValue("  y von C?", 3);
        if (sel1)
        {
            cz = getValue("  z von C?", 5);
        }
        a = bx - cx;
        a *= a;
        buf = by - cy;
        buf *= buf;
        a += buf;
        if (sel1)
        {
            buf = bz - cz;
            buf *= buf;
            a += buf;
        }
        a = sqrt(a);
        b = ax - cx;
        b *= b;
        buf = ay - cy;
        buf *= buf;
        b += buf;
        if (sel1)
        {
            buf = az - cz;
            buf *= buf;
            b += buf;
        }
        b = sqrt(b);
        c = ax - bx;
        c *= c;
        buf = ay - by;
        buf *= buf;
        c += buf;
        if (sel1)
        {
            buf = az - bz;
            buf *= buf;
            c += buf;
        }
        c = sqrt(c);
        three_sides(a, b, c, &alpha, &beta, &gamma);
        break;
    default:
        showCredits();
        return 0;
    }
    Bdisp_Fill_VRAM(COLOR_WHITE, 1);
    if (a <= 0 | b <= 0 | c <= 0 | alpha <= 0 | beta <= 0 | gamma <= 0)
    {
        return 80;
    }
    double u = a + b + c;
    double s = u / 2;
    double area = s;
    area *= s - a;
    area *= s - b; // Prevent integer overflow
    area *= s - c;
    area = sqrt(area);
    double ha = b * sin(rad(gamma));
    double hb = c * sin(rad(alpha));
    double hc = a * sin(rad(beta));
    double ir = (s-a) * sin(rad(alpha / 2)) / cos(rad(alpha/2));
    double ur = a / (2 * sin(rad(alpha)));
    Bdisp_EnableColor(1);
    int w2 = LCD_WIDTH_PX / 2;
    int x = 0, y = 0;
    PrintMini(&x, &y, "Seite a: ", 0x02, w2, 0, 0, COLOR_RED, 0, 1, 0);
    printFloat(&x, &y, a, w2);
    x = 0;
    y += FONT_HEIGHT;
    PrintMini(&x, &y, "Seite b: ", 0x02, w2, 0, 0, COLOR_BLUE, 0, 1, 0);
    printFloat(&x, &y, b, w2);
    x = 0;
    y += FONT_HEIGHT;
    PrintMini(&x, &y, "Seite c: ", 0x02, w2, 0, 0, COLOR_GREEN, 0, 1, 0);
    printFloat(&x, &y, c, w2);
    x = 0;
    y += FONT_HEIGHT +  5;
    PrintMini(&x, &y, "Hoehe a: ", 0x02, w2, 0, 0, COLOR_MAROON, 0, 1, 0);
    printFloat(&x, &y, ha, w2);
    x = 0;
    y += FONT_HEIGHT;
    PrintMini(&x, &y, "Hoehe b: ", 0x02, w2, 0, 0, COLOR_MAROON, 0, 1, 0);
    printFloat(&x, &y, hb, w2);
    x = 0;
    y += FONT_HEIGHT;
    PrintMini(&x, &y, "Hoehe c: ", 0x02, w2, 0, 0, COLOR_MAROON, 0, 1, 0);
    printFloat(&x, &y, hc, w2);
    x = 0;
    y += FONT_HEIGHT + 5;
    PrintMini(&x, &y, "Umfang: ", 0x02, w2, 0, 0, COLOR_DARKCYAN, 0, 1, 0);
    printFloat(&x, &y, u, w2);
    x = 0;
    y += FONT_HEIGHT;
    PrintMini(&x, &y, "Flaeche: ", 0x02, w2, 0, 0, COLOR_DARKCYAN, 0, 1, 0);
    printFloat(&x, &y, area, w2);
    x = 0;
    y += FONT_HEIGHT;
    PrintMini(&x, &y, "Inkreis: ", 0x02, w2, 0, 0, COLOR_DARKCYAN, 0, 1, 0);
    printFloat(&x, &y, ir, w2);
    x = 0;
    y += FONT_HEIGHT;
    PrintMini(&x, &y, "Umkreis: ", 0x02, w2, 0, 0, COLOR_DARKCYAN, 0, 1, 0);
    printFloat(&x, &y, ur, w2);
    x = w2;
    y = 0;
    PrintMini(&x, &y, "Alpha: ", 0x02, LCD_WIDTH_PX, 0, 0, COLOR_INDIGO, 0, 1, 0);
    printFloat(&x, &y, alpha, LCD_WIDTH_PX);
    PrintMini(&x, &y, degree, 0x02, LCD_WIDTH_PX, 0, 0, COLOR_BLACK, 0, 1, 0);
    x = w2;
    y += FONT_HEIGHT;
    PrintMini(&x, &y, "Beta: ", 0x02, LCD_WIDTH_PX, 0, 0, COLOR_INDIGO, 0, 1, 0);
    printFloat(&x, &y, beta, LCD_WIDTH_PX);
    PrintMini(&x, &y, degree, 0x02, LCD_WIDTH_PX, 0, 0, COLOR_BLACK, 0, 1, 0);
    x = w2;
    y += FONT_HEIGHT;
    PrintMini(&x, &y, "Gamma: ", 0x02, LCD_WIDTH_PX, 0, 0, COLOR_INDIGO, 0, 1, 0);
    printFloat(&x, &y, gamma, LCD_WIDTH_PX);
    PrintMini(&x, &y, degree, 0x02, LCD_WIDTH_PX, 0, 0, COLOR_BLACK, 0, 1, 0);
    x = w2;
    y += FONT_HEIGHT;
    int h = LCD_HEIGHT_PX - STATUS_AREA_HEIGHT - y;
    double rel = h / (ur * 2.0);
    double crel = rel * c;
    double hrel = rel * hc;
    double dx = cos(rad(alpha)) * b * rel;
    x += (w2 - crel) / 2.0;
    y = LCD_HEIGHT_PX - (h - hrel) / 2.0;
    drawLine(x, y, x+crel, y, COLOR_GREEN);
    drawLine(x, y, x+dx, y-hrel, COLOR_BLUE);
    drawLine(x+crel, y, x+dx, y-hrel, COLOR_RED);
    GetKey(&key);
    Bdisp_EnableColor(0);
    Bdisp_Fill_VRAM(COLOR_WHITE, 1);
    return 0;
}

int main()
{
    int choice, error;
    while (true)
    {
        drawFKey(0, sss);
        drawFKey(1, ssw);
        drawFKey(2, wws);
        drawFKey(3, ppp);
        choice = getChoice("  Dreiecksberechnung", congruence, 4);
        error = triangle(choice);
        if (error)
        {
            PrintXY_2(TEXT_MODE_NORMAL, 2, 6, error, TEXT_COLOR_RED);
        }
    }
    return 0;
}
