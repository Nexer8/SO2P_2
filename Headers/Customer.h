//
// Created by mwisniewski on 4/1/20.
//

#ifndef SO2P_2_CUSTOMER_H
#define SO2P_2_CUSTOMER_H


#include <memory>
#include <mutex>

static int current_customer_id = 0;

enum class Customers_state {
    WAITING_FOR_A_CUT,
    HAVING_A_HAIRCUT
};

class Customer {
private:
    int id;
    Customers_state state;

public:
    std::mutex mutex;

    int get_id() { return id; }

    Customers_state get_state() { return state; }

    void set_state(Customers_state state) { state = state; }

    Customer();
};


#endif //SO2P_2_CUSTOMER_H
