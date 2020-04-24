//
// Created by mwisniewski on 4/5/20.
//

#include "../Headers/Visualizer.h"

#define COLUMNS_PER_SALON 2
#define NUMBER_OF_COLUMNS (NUMBER_OF_SALONS * COLUMNS_PER_SALON)

Visualizer::Visualizer(City &city, std::vector<std::shared_ptr<Hairdresser> > &hairdressers) :
        city(city), hairdressers(hairdressers) {
    init();

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

    int column_width = (params.separator - params.x_margin) / NUMBER_OF_COLUMNS;
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

    for (int i = 0; i < NUMBER_OF_SALONS; i++) {
        mvwprintw(window, 0, i * (COLUMNS_PER_SALON * column_width - 2), city.salons[i]->name.c_str());
    }

    int mul = 0;
    for (int i = 0; i < NUMBER_OF_SALONS; i++) {
        if (i == 0) {
            mvwprintw(window, 2, 2, "Hairdresser's state");
            mvwhline(window, 4, 1, 0, params.separator - params.x_margin - 2);
        } else {
            mvwprintw(window, 2, (mul * column_width), "Hairdresser's state");
        }
        mul++;

        mvwvline(window, 1, mul * column_width - 2, 0, params.y_max - 2 * params.y_margin - 2);
        mvwprintw(window, 2, mul * column_width, "Customer's state");
        mul++;
        if (i != NUMBER_OF_SALONS - 1) {
            mvwvline(window, 1, mul * column_width - 2, 0, params.y_max - 2 * params.y_margin - 2);
        }
    }

//    mul = 0;
//    for (int idx = 0; idx < NUMBER_OF_SALONS; idx++) {
//        for (int i = 0; i < NUMBER_OF_HAIRDRESSERS_PER_SALON; i++) {
//            if (idx == 0) {
//                mvwprintw(window, 2 * i + 5, 2, "%s",
//                          std::to_string(hairdressers[i + idx * NUMBER_OF_HAIRDRESSERS_PER_SALON]->get_id()).c_str());
//            } else {
//                mvwprintw(window, 2 * mul + 5, (COLUMNS_PER_SALON * column_width) + 1, "%s",
//                          std::to_string(hairdressers[i + idx * NUMBER_OF_HAIRDRESSERS_PER_SALON]->get_id()).c_str());
//                mul++;
//            }
//        }
//    }

//    TODO: It's client who should have a field salon!!!
//    mul = 0;
//    int idx = 0;
//    for (const auto& customer: hairdressers[0].get()->get_customers()) {
//        if (customer->salon->get_id() == 0) {
//            mvwprintw(window, 2 * idx + 5, column_width + 1, "%s",
//                      std::to_string(customer->get_id()).c_str());
//        }
//        else {
//            mvwprintw(window, 2 * mul + 5, (COLUMNS_PER_SALON + 1) * column_width + 1, "%s",
//                      std::to_string(customer->get_id()).c_str());
//            mul++;
//        }
//
//        idx++;
//    }

    touchwin(window);
    wrefresh(window);
}

void Visualizer::update_screen() {
    int column_width = (params.separator - params.x_margin) / NUMBER_OF_COLUMNS;

    init_pair(1, COLOR_GREEN, -1);
    init_pair(2, COLOR_BLUE, -1);
    init_pair(3, COLOR_YELLOW, -1);
    init_pair(4, COLOR_CYAN, -1);
    init_pair(5, COLOR_MAGENTA, -1);

    int mul;
    for (int idx = 0; idx < NUMBER_OF_SALONS; idx++) {
        if (idx == 0) {
            mul = 0;
        } else {
            mul = COLUMNS_PER_SALON;
        }
        for (int i = 0; i < NUMBER_OF_HAIRDRESSERS_PER_SALON; i++) {
            switch (hairdressers[i + idx * NUMBER_OF_HAIRDRESSERS_PER_SALON]->get_state()) {
                case Hairdressers_state::WAITING_FOR_A_CLIENT:
                    wattron(window, COLOR_PAIR(1));
                    mvwprintw(window, 2 * i + 5, (mul * column_width) + 1,
                              (to_string(hairdressers[i + idx * NUMBER_OF_HAIRDRESSERS_PER_SALON]->get_id()) +
                               " Waiting for a client").c_str());
                    wattroff(window, COLOR_PAIR(1));
                    break;

                case Hairdressers_state::WAITING_FOR_SCISSORS:
                    wattron(window, COLOR_PAIR(2));
                    mvwprintw(window, 2 * i + 5, (mul * column_width) + 1,
                              (to_string(hairdressers[i + idx * NUMBER_OF_HAIRDRESSERS_PER_SALON]->get_id()) +
                               " Waiting for scissors").c_str());
                    wattroff(window, COLOR_PAIR(2));
                    break;

                case Hairdressers_state::TAKING_A_BREAK:
                    wattron(window, COLOR_PAIR(3));
                    mvwprintw(window, 2 * i + 5, (mul * column_width) + 1,
                              (to_string(hairdressers[i + idx * NUMBER_OF_HAIRDRESSERS_PER_SALON]->get_id()) +
                               " Taking a break      ").c_str());
                    wattroff(window, COLOR_PAIR(3));
                    break;

                case Hairdressers_state::CUTTING_HAIR:
                    wattron(window, COLOR_PAIR(4));
                    mvwprintw(window, 2 * i + 5, (mul * column_width) + 1,
                              (to_string(hairdressers[i + idx * NUMBER_OF_HAIRDRESSERS_PER_SALON]->get_id()) +
                               " Cutting hair        ").c_str());
                    wattroff(window, COLOR_PAIR(4));
                    break;

                default:
                    wattron(window, COLOR_PAIR(5));
                    mvwprintw(window, 2 * i + 5, (mul * column_width) + 1,
                              (to_string(hairdressers[i + idx * NUMBER_OF_HAIRDRESSERS_PER_SALON]->get_id()) +
                               " End of work         ").c_str());
                    wattroff(window, COLOR_PAIR(5));
                    break;
            }
        }
    }

    int first_salon_capacity = 0;
    int second_salon_capacity = 0;
    int y_axis_alignment;
    for (const auto &customer : hairdressers[0]->get_customers()) {
        if (customer->salon == nullptr) break;

        if (customer->salon->get_id() == 0) {
            y_axis_alignment = first_salon_capacity;
            first_salon_capacity++;
            mul = 1;
        } else {
            y_axis_alignment = second_salon_capacity;
            second_salon_capacity++;
            mul = 1 + COLUMNS_PER_SALON;
        }

        switch (customer->get_state()) {
            case Customers_state::WAITING_FOR_A_CUT:
                wattron(window, COLOR_PAIR(1));
                mvwprintw(window, 2 * y_axis_alignment + 5, mul * column_width + 1,
                          (to_string(customer->get_id()) + " Waiting for a cut").c_str());
                wattroff(window, COLOR_PAIR(1));
                break;

            case Customers_state::HAVING_A_HAIRCUT:
                wattron(window, COLOR_PAIR(4));
                mvwprintw(window, 2 * y_axis_alignment + 5, mul * column_width + 1,
                          (to_string(customer->get_id()) + " Having a haircut ").c_str());
                wattroff(window, COLOR_PAIR(4));
                break;

            default:
                wattron(window, COLOR_PAIR(5));
                mvwprintw(window, 2 * y_axis_alignment + 5, mul * column_width + 1,
                          (to_string(customer->get_id()) + " Done             ").c_str());
                wattroff(window, COLOR_PAIR(5));
                break;
        }
    }

    touchwin(window);
    wrefresh(window);
}

void Visualizer::update() {
    while (city.no_of_ready_salons) {
        update_screen();
    }
}

Visualizer::~Visualizer() {
    delwin(window);
    endwin();

    hairdressers.clear();
    thread.join();
}
