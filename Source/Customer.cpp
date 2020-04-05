//
// Created by mwisniewski on 4/1/20.
//

#include "../Headers/Customer.h"

Customer::Customer() :id(current_customer_id++), state(Customers_state::WAITING_FOR_A_CUT) {}
