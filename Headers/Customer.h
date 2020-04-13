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
    HAVING_A_HAIRCUT,
    DONE
};

class Customer {
private:
    int id;
public:

    std::mutex mutex;
    volatile Customers_state state;

    int get_id() { return id; }

    volatile Customers_state get_state() { return state; }

//    void set_state(Customers_state state) { state = state; }

    Customer();
};


#endif //SO2P_2_CUSTOMER_H
