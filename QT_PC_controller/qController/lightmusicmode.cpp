#include "lightmusicmode.h"

LightMusicMode::LightMusicMode() {}
LightMusicMode::~LightMusicMode() {}

//  ----    Mode 1   -----
//
//  Rainbow -   color smoothly changes
QColor Mode1::handleSoundLevel(qreal level)
{
    QColor color;
    static int r = 255, g = 0, b = 0;

    if (r == 255 && g < 255 && b == 0)
        g++;
    else if (g == 255 && r > 0 && b == 0)
        r--;
    else if (g == 255 && b < 255 && r == 0)
        b++;
    else if (b == 255 && g > 0 && r == 0)
        g--;
    else if (b == 255 && r < 255 && g == 0)
        r++;
    else if (r == 255 && b > 0 && g == 0)
        b--;

    color.setRgb(r * level, g * level, b * level);
    //color.setRgb(r, g, b);
    return color;
}

//  -----   Mode 2  ---------------
QColor Mode2::handleSoundLevel(qreal level)
{
    QColor color = QColor::fromRgb(0);

    if (level > 0 && level <= 0.3)
        color.setRgb(255 - 850 * level, 0, 255);
    else if (level > 0.3 && level <= 0.5)
        color.setRgb(0, 1275 * -(0.3 - level), 255);
    else if (level > 0.5 && level <= 0.7)
        color.setRgb(0, 255, 255 - (1275 * -(0.5 - level)));
    else if (level > 0.7 && level <= 0.9)
        color.setRgb(1275 * -(0.7 - level), 255, 0);
    else if (level > 0.9 && level <= 1)
        color.setRgb(level * 255, 0, 0);

    return color;
}
