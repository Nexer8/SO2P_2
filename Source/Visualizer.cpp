//
// Created by mwisniewski on 4/5/20.
//

#include "../Headers/Visualizer.h"

Visualizer::Visualizer(std::vector<std::shared_ptr<Hairdresser> > &hairdressers, Salon &salon) :
        hairdressers(hairdressers), salon(salon) {
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

    int column_width = (params.separator - params.x_margin) / 4;
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

    mvwprintw(window, 2, 2, "Hairdresser's Id");
    mvwprintw(window, 2, column_width, "Hairdresser's state");
    mvwprintw(window, 2, 2 * column_width, "Customer's id");
    mvwprintw(window, 2, 3 * column_width, "Customer's state");

    mvwhline(window, 4, 1, 0, params.separator - params.x_margin - 2);
    mvwvline(window, 1, column_width - 2, 0, params.y_max - 2 * params.y_margin - 2);
    mvwvline(window, 1, 2 * column_width - 2, 0, params.y_max - 2 * params.y_margin - 2);
    mvwvline(window, 1, 3 * column_width - 2, 0, params.y_max - 2 * params.y_margin - 2);

    for (int i = 0; i < NUMBER_OF_HAIRDRESSERS; i++) {
        mvwprintw(window, 2 * i + 5, 3, "%s", std::to_string(hairdressers[i]->get_id()).c_str());
    }

    for (int i = 0; i < NUMBER_OF_CLIENTS; i++) {
        mvwprintw(window, 2 * i + 5, 2 * column_width + 1, "%s", std::to_string(salon.customers[i]->get_id()).c_str());
    }

    touchwin(window);
    wrefresh(window);
}

void Visualizer::update_screen() {
    int column_width = (params.separator - params.x_margin) / 4;

    init_pair(1, COLOR_GREEN, -1);
    init_pair(2, COLOR_BLUE, -1);
    init_pair(3, COLOR_YELLOW, -1);
    init_pair(4, COLOR_CYAN, -1);
    init_pair(5, COLOR_MAGENTA, -1);

    for (int i = 0; i < NUMBER_OF_HAIRDRESSERS; i++) {
        switch (hairdressers[i]->get_state()) {
            case Hairdressers_state::WAITING_FOR_A_CLIENT:
                wattron(window, COLOR_PAIR(1));
                mvwprintw(window, 2 * i + 5, column_width + 1, "Waiting for a client");
                wattroff(window, COLOR_PAIR(1));
                break;

            case Hairdressers_state::WAITING_FOR_SCISSORS:
                wattron(window, COLOR_PAIR(2));
                mvwprintw(window, 2 * i + 5, column_width + 1, "Waiting for scissors");
                wattroff(window, COLOR_PAIR(2));
                break;

            case Hairdressers_state::TAKING_A_BREAK:
                wattron(window, COLOR_PAIR(3));
                mvwprintw(window, 2 * i + 5, column_width + 1, "Taking a break      ");
                wattroff(window, COLOR_PAIR(3));
                break;

            case Hairdressers_state::CUTTING_HAIR:
                wattron(window, COLOR_PAIR(4));
                mvwprintw(window, 2 * i + 5, column_width + 1, "Cutting hair        ");
                wattroff(window, COLOR_PAIR(4));
                break;

            default:
                wattron(window, COLOR_PAIR(5));
                mvwprintw(window, 2 * i + 5, column_width + 1, "End of work         ");
                wattroff(window, COLOR_PAIR(5));
                break;
        }
    }

    for (const auto &customer : salon.customers) {
        switch (customer->get_state()) {
            case Customers_state::WAITING_FOR_A_CUT:
                wattron(window, COLOR_PAIR(1));
                mvwprintw(window, 2 * customer->get_id() + 5, 3 * column_width + 1, "Waiting for a cut");
                wattroff(window, COLOR_PAIR(1));
                break;

            case Customers_state::HAVING_A_HAIRCUT:
                wattron(window, COLOR_PAIR(4));
                mvwprintw(window, 2 * customer->get_id() + 5, 3 * column_width + 1, "Having a haircut ");
                wattroff(window, COLOR_PAIR(4));
                break;

            default:
                wattron(window, COLOR_PAIR(5));
                mvwprintw(window, 2 * customer->get_id() + 5, 3 * column_width + 1, "Done             ");
                wattroff(window, COLOR_PAIR(5));
                break;
        }
    }
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
