#pragma once

#include "date.hpp"


namespace lab2 {
    class WesternDate : public Date {
        protected:
            unsigned int _year;
            unsigned int _month;
            unsigned int _day;

        public:
            ~WesternDate() override {};

            int year();
            unsigned int month();
            unsigned int day();
            unsigned int week_day();
            unsigned int days_per_week();
            std::string week_day_name();
            std::string month_name();

            virtual unsigned int days_this_month() = 0;
            virtual void add_year(int n = 1) = 0; // TODO: Unspecified return type
            virtual void add_month(int n = 1) = 0; // TODO: Unspecified return type
            virtual int mod_julian_day() = 0;
    };
}