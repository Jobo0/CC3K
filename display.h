#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include "observer.h"
#include <vector>
#include <memory>

class Level;

class Display : public Observer {
    int width;
    int height;
    public:
    Display(int width, int height);
    void notify(Level &level) override;

};
#endif
