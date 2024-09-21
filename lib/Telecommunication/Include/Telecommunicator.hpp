/**
 ********************************************************************************
 * @file    Telecommunicator.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Telecommunication Manager for CORALS
 * @version 1.0
 * @date    2024-09-11
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __TELECOMMUNICATOR_HPP__
#define __TELECOMMUNICATOR_HPP__

#include "List.tpp"

#include "MessageBase.tpp"

namespace Telecommunication {

class Telecommunicator {
    public:
        Telecommunicator();
        ~Telecommunicator();

        void Register_Handle(MessageHandler *handle);

        void run();

    private:
        DataStructures::List::List<MessageHandler *> mHandles;
};



} // namespace Telecommunication

#endif // __TELECOMMUNICATOR_HPP__