//
// Created by mwisniewski on 4/5/20.
//

#ifndef SO2P_2_VISUALIZER_H
#define SO2P_2_VISUALIZER_H


#include <thread>
#include <ncurses.h>
#include <vector>
#include "Hairdresser.h"


/*! \class Visualizer
    \brief A class that is responsible for the visual part happening on the screen.

    Visualizer that runs ncurses.
*/
class Visualizer {
private:
    std::thread thread;
    WINDOW *window;
    std::vector<std::shared_ptr<Hairdresser>> &hairdressers;
    Salon &salon;

    struct Window_params {
        int x_max;
        int y_max;
        int x_margin;
        int y_margin;
        int separator;
    } params;

    void init();

    void update_screen();

    void update();

public:
    Visualizer(std::vector<std::shared_ptr<Hairdresser> > &hairdressers, Salon &salon);

    ~Visualizer();
};


#endif //SO2P_2_VISUALIZER_H
