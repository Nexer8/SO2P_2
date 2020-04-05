//
// Created by mwisniewski on 4/5/20.
//

#include "../Headers/Visualizer.h"

Visualizer::Visualizer(std::vector<std::shared_ptr<Hairdresser> > &hairdressers, Salon &salon) : hairdressers(
        hairdressers), salon(salon) {
    init();
    while (!salon.no_of_ready_hairdressers);
    thread = std::thread(&Visualizer::update, this);
}

void Visualizer::init() {
    initscr();
    noecho(); // no user input is being shown on the screen
    use_default_colors();
    start_color();
    box(stdscr, 0, 0);

    getmaxyx(stdscr, params.y_max, params.x_max);
    params.x_margin = params.x_max / 20;
    params.y_margin = params.y_max / 10;
    params.separator = params.x_max / 2;

    int column_width = (params.separator - params.x_margin) / 2;
    init_pair(9, COLOR_WHITE, -1);

    wattron(stdscr, COLOR_PAIR(9));

    mvwprintw(stdscr, params.y_margin / 2, params.x_max / 2 - 11, "THE HAIRDRESSER'S");
    mvwprintw(stdscr, params.y_max - params.y_margin / 2,
              params.x_max - params.x_margin - 22, "Mariusz Wisniewski 241393");

    wattroff(stdscr, COLOR_PAIR(9));

    refresh();

    window = derwin(stdscr, params.y_max - 2 * params.y_margin,
                    params.separator - params.x_margin, params.y_margin, params.x_margin);
    box(window, 0, 0);

    wprintw(window, "Hairdressers");

    mvwprintw(window, 2, 2, "Id");
    mvwprintw(window, 2, column_width, "State");

    mvwhline(window, 4, 1, 0, params.separator - params.x_margin - 2);
    mvwvline(window, 1, column_width - 2, 0, params.y_max - 2 * params.y_margin - 2);

//    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {
//        mvwprintw(window, 2 * i + 5, 3, "%s", std::to_string(philosophers[i]->get_id()).c_str());
//    }

    touchwin(window);
    wrefresh(window);
}

void Visualizer::update_screen() {
    int column_width = (params.separator - params.x_margin) / 2;

    init_pair(1, COLOR_GREEN, -1);
    init_pair(2, COLOR_BLUE, -1);
    init_pair(3, COLOR_YELLOW, -1);
    init_pair(4, COLOR_CYAN, -1);

//    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {
//        switch (philosophers[i]->get_state()) {
//            case State::EATING:
//                wattron(window, COLOR_PAIR(1));
//                mvwprintw(window, 2 * i + 5, column_width + 1, "eating  ");
//                wattroff(window, COLOR_PAIR(1));
//                break;
//
//            case State::THINKING:
//                wattron(window, COLOR_PAIR(2));
//                mvwprintw(window, 2 * i + 5, column_width + 1, "thinking");
//                wattroff(window, COLOR_PAIR(2));
//                break;
//
//            case State::WAITING_FOR_FORKS:
//                wattron(window, COLOR_PAIR(3));
//                mvwprintw(window, 2 * i + 5, column_width + 1, "waiting ");
//                wattroff(window, COLOR_PAIR(3));
//                break;
//
//            default:
//                wattron(window, COLOR_PAIR(4));
//                mvwprintw(window, 2 * i + 5, column_width + 1, "sleeping");
//                wattroff(window, COLOR_PAIR(4));
//                break;
//        }
//    }
    touchwin(window);
    wrefresh(window);
}

void Visualizer::update() {
    while (salon.no_of_ready_hairdressers) {
        update_screen();
    }
}

Visualizer::~Visualizer() {
    delwin(window);
    endwin();

    hairdressers.clear();
    thread.join();
}
