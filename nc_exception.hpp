/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   nc_exception.hpp
 * Author: Jan Pazdera
 *
 * Created on 5. června 2016, 14:39
 */

#ifndef NC_EXCEPTION_HPP
#define NC_EXCEPTION_HPP

#include <exception>
#include <string>

class nc_exception : public std::exception {
    public:
        nc_exception() = delete;
        explicit nc_exception(std::string msg) : msg(msg) {}
        nc_exception(const nc_exception& orig) = default;
        nc_exception(nc_exception&& move) = default;
        virtual ~nc_exception() = default;
        const char* what() const noexcept override { return msg.c_str(); }
        const std::string swhat() const noexcept { return msg; }
    private:
        std::string msg;
};

#endif /* NC_EXCEPTION_HPP */

