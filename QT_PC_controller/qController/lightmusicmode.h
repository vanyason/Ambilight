#ifndef LIGHTMUSICMODE_H
#define LIGHTMUSICMODE_H

#include <QColor>

class LightMusicMode
{        
public:
    LightMusicMode();
    virtual ~LightMusicMode();
    virtual QColor handleSoundLevel(qreal level) = 0;

protected:


};

/**
 * @brief Rainbow Mode
 */
class Mode1 : public LightMusicMode
{
    QColor handleSoundLevel(qreal level) override;
};

/**
 * @brief Different color picks
 */
class Mode2 : public LightMusicMode
{
    QColor handleSoundLevel(qreal level) override;
};

#endif // LIGHTMUSICMODE_H
