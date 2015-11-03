#include "calendar.hpp"
#include "gregorian.hpp"
#include "julian.hpp"
#include <cxxtest/TestSuite.h>

using namespace lab2;


class CalendarTestSuite : public CxxTest::TestSuite {
    public:
        void test_default_init() {
            time_t tp;
            time(&tp);
            set_k_time(tp);

            const struct tm *t = gmtime(&tp);
            const int g_year   = t->tm_year + 1900;
            const int g_month  = t->tm_mon + 1;
            const int g_day    = t->tm_mday;

            Gregorian g;

            TS_ASSERT_EQUALS((int) g.year(), g_year);
            TS_ASSERT_EQUALS((int) g.month(), g_month);
            TS_ASSERT_EQUALS((int) g.day(), g_day);

            tp = 0;
            set_k_time(tp);

            Julian j;

            TS_ASSERT_EQUALS((int) j.year(), 1969);
            TS_ASSERT_EQUALS((int) j.month(), 12);
            TS_ASSERT_EQUALS((int) j.day(), 19);
        }

        void test_copy_init() {
            time_t tp;
            time(&tp);
            set_k_time(tp);

            Gregorian g1;
            Gregorian g2(g1);
            Gregorian g3 = g1;
            Gregorian g4; g4 = g1;

            TS_ASSERT_EQUALS(g1.year(), g2.year());
            TS_ASSERT_EQUALS(g1.month(), g2.month());
            TS_ASSERT_EQUALS(g1.day(), g2.day());

            TS_ASSERT_EQUALS(g1.year(), g3.year());
            TS_ASSERT_EQUALS(g1.month(), g3.month());
            TS_ASSERT_EQUALS(g1.day(), g3.day());

            TS_ASSERT_EQUALS(g1.year(), g4.year());
            TS_ASSERT_EQUALS(g1.month(), g4.month());
            TS_ASSERT_EQUALS(g1.day(), g4.day());

            Julian j1;
            Julian j2(j1);
            Julian j3 = j1;
            Julian j4; j4 = j1;

            TS_ASSERT_EQUALS(j1.year(), j2.year());
            TS_ASSERT_EQUALS(j1.month(), j2.month());
            TS_ASSERT_EQUALS(j1.day(), j2.day());

            TS_ASSERT_EQUALS(j1.year(), j3.year());
            TS_ASSERT_EQUALS(j1.month(), j3.month());
            TS_ASSERT_EQUALS(j1.day(), j3.day());

            TS_ASSERT_EQUALS(j1.year(), j4.year());
            TS_ASSERT_EQUALS(j1.month(), j4.month());
            TS_ASSERT_EQUALS(j1.day(), j4.day());
        }

        void test_date_constructors() {
            Gregorian g1(1970, 1, 1);
            long mod_jul = 40587;
            TS_ASSERT_EQUALS(g1.mod_julian_day(), mod_jul);
            TS_ASSERT_EQUALS((int) g1.year(), 1970);
            TS_ASSERT_EQUALS((int) g1.month(), 1);
            TS_ASSERT_EQUALS((int) g1.day(), 1);

            Julian j1(1969, 12, 19);
            TS_ASSERT_EQUALS(j1.mod_julian_day(), mod_jul);
            TS_ASSERT_EQUALS((int) j1.year(), 1969);
            TS_ASSERT_EQUALS((int) j1.month(), 12);
            TS_ASSERT_EQUALS((int) j1.day(), 19);

            Gregorian g2(1858, 11, 17);
            TS_ASSERT_EQUALS(g2.mod_julian_day(), 0);

            Julian j2(1858, 11, 5);
            TS_ASSERT_EQUALS(j2.mod_julian_day(), 0);
        }

        void test_valid_date() {
            TS_ASSERT_THROWS(Gregorian(2100, 2, 29), std::invalid_argument);
            TS_ASSERT_THROWS_NOTHING(Julian(2100, 2, 29));
            TS_ASSERT_THROWS_NOTHING(Gregorian(2400, 2, 29));
            TS_ASSERT_THROWS_NOTHING(Julian(2400, 2, 29));
            TS_ASSERT_THROWS(Gregorian(2345, 4, 31), std::invalid_argument);
            TS_ASSERT_THROWS(Julian(2345, 4, 31), std::invalid_argument);
        }

        void test_mod_julian_day() {
            Gregorian g1(2000, 10, 10);
            long mjd = 51827;
            TS_ASSERT_EQUALS(g1.mod_julian_day(), mjd);

            Julian j1(2000, 10, 10);
            mjd = 51840;
            TS_ASSERT_EQUALS(j1.mod_julian_day(), mjd);

            time_t t; t = 0; set_k_time(t);
            Gregorian g2;
            mjd = 40587;
            TS_ASSERT_EQUALS(g2.mod_julian_day(), mjd);

            set_k_time(t);
            Julian j2;
            TS_ASSERT_EQUALS(j2.mod_julian_day(), mjd);
        }

        void test_add_year() {
            Gregorian g1(2015, 1, 2);
            g1.add_year();
            TS_ASSERT_EQUALS((int) g1.year(), 2016);
            TS_ASSERT_EQUALS((int) g1.month(), 1);
            TS_ASSERT_EQUALS((int) g1.day(), 2);

            Gregorian g2(2010, 10, 20);
            g2.add_year(10);
            TS_ASSERT_EQUALS((int) g2.year(), 2020);
            TS_ASSERT_EQUALS((int) g2.month(), 10);
            TS_ASSERT_EQUALS((int) g2.day(), 20);

            Gregorian g3(2012, 2, 29);
            g3.add_year();
            TS_ASSERT_EQUALS((int) g3.year(), 2013);
            TS_ASSERT_EQUALS((int) g3.month(), 2);
            TS_ASSERT_EQUALS((int) g3.day(), 28);

            Gregorian g4(2012, 2, 29);
            g4.add_year(10);
            TS_ASSERT_EQUALS((int) g4.year(), 2022);
            TS_ASSERT_EQUALS((int) g4.month(), 2);
            TS_ASSERT_EQUALS((int) g4.day(), 28);

            Julian j1(2015, 1, 2);
            j1.add_year();
            TS_ASSERT_EQUALS((int) j1.year(), 2016);
            TS_ASSERT_EQUALS((int) j1.month(), 1);
            TS_ASSERT_EQUALS((int) j1.day(), 2);

            Julian j2(2010, 10, 20);
            j2.add_year(10);
            TS_ASSERT_EQUALS((int) j2.year(), 2020);
            TS_ASSERT_EQUALS((int) j2.month(), 10);
            TS_ASSERT_EQUALS((int) j2.day(), 20);

            Julian j3(2012, 2, 29);
            j3.add_year();
            TS_ASSERT_EQUALS((int) j3.year(), 2013);
            TS_ASSERT_EQUALS((int) j3.month(), 2);
            TS_ASSERT_EQUALS((int) j3.day(), 28);

            Julian j4(2012, 2, 29);
            j4.add_year(10);
            TS_ASSERT_EQUALS((int) j4.year(), 2022);
            TS_ASSERT_EQUALS((int) j4.month(), 2);
            TS_ASSERT_EQUALS((int) j4.day(), 28);
        }

        void test_add_month() {
            Gregorian g1(2012, 2, 29);
            g1.add_month();
            TS_ASSERT_EQUALS((int) g1.year(), 2012);
            TS_ASSERT_EQUALS((int) g1.month(), 3);
            TS_ASSERT_EQUALS((int) g1.day(), 29);

            Gregorian g2(2000, 3, 31);
            g2.add_month();
            TS_ASSERT_EQUALS((int) g2.year(), 2000);
            TS_ASSERT_EQUALS((int) g2.month(), 4);
            TS_ASSERT_EQUALS((int) g2.day(), 30);

            Gregorian g3(2000, 7, 31);
            g3.add_month();
            TS_ASSERT_EQUALS((int) g3.year(), 2000);
            TS_ASSERT_EQUALS((int) g3.month(), 8);
            TS_ASSERT_EQUALS((int) g3.day(), 31);

            Gregorian g4(2000, 11, 30);
            g4.add_month();
            TS_ASSERT_EQUALS((int) g4.year(), 2000);
            TS_ASSERT_EQUALS((int) g4.month(), 12);
            TS_ASSERT_EQUALS((int) g4.day(), 30);

            Gregorian g5(2000, 12, 10);
            g5.add_month();
            TS_ASSERT_EQUALS((int) g5.year(), 2001);
            TS_ASSERT_EQUALS((int) g5.month(), 1);
            TS_ASSERT_EQUALS((int) g5.day(), 10);

            Gregorian g6(2000, 5, 10);
            g6.add_month(13);
            TS_ASSERT_EQUALS((int) g6.year(), 2001);
            TS_ASSERT_EQUALS((int) g6.month(), 6);
            TS_ASSERT_EQUALS((int) g6.day(), 10);

            Gregorian g7(2000, 6, 1);
            g7.add_month(4);
            TS_ASSERT_EQUALS((int) g7.year(), 2000);
            TS_ASSERT_EQUALS((int) g7.month(), 10);
            TS_ASSERT_EQUALS((int) g7.day(), 1);

            Julian j1(2012, 2, 29);
            j1.add_month();
            TS_ASSERT_EQUALS((int) j1.year(), 2012);
            TS_ASSERT_EQUALS((int) j1.month(), 3);
            TS_ASSERT_EQUALS((int) j1.day(), 29);

            Julian j2(2000, 3, 31);
            j2.add_month();
            TS_ASSERT_EQUALS((int) j2.year(), 2000);
            TS_ASSERT_EQUALS((int) j2.month(), 4);
            TS_ASSERT_EQUALS((int) j2.day(), 30);

            Julian j3(2000, 7, 31);
            j3.add_month();
            TS_ASSERT_EQUALS((int) j3.year(), 2000);
            TS_ASSERT_EQUALS((int) j3.month(), 8);
            TS_ASSERT_EQUALS((int) j3.day(), 31);

            Julian j4(2000, 11, 30);
            j4.add_month();
            TS_ASSERT_EQUALS((int) j4.year(), 2000);
            TS_ASSERT_EQUALS((int) j4.month(), 12);
            TS_ASSERT_EQUALS((int) j4.day(), 30);

            Julian j5(2000, 12, 10);
            j5.add_month();
            TS_ASSERT_EQUALS((int) j5.year(), 2001);
            TS_ASSERT_EQUALS((int) j5.month(), 1);
            TS_ASSERT_EQUALS((int) j5.day(), 10);

            Julian j6(2000, 5, 10);
            j6.add_month(13);
            TS_ASSERT_EQUALS((int) j6.year(), 2001);
            TS_ASSERT_EQUALS((int) j6.month(), 6);
            TS_ASSERT_EQUALS((int) j6.day(), 10);

            Julian j7(2000, 6, 1);
            j7.add_month(4);
            TS_ASSERT_EQUALS((int) j7.year(), 2000);
            TS_ASSERT_EQUALS((int) j7.month(), 10);
            TS_ASSERT_EQUALS((int) j7.day(), 1);
        }

        void test_calendar_default_init() {
            time_t tp;
            time(&tp);
            set_k_time(tp);

            Calendar<Gregorian> g_cal;

            Calendar<Julian> j_cal;
        }

        void test_calendar_copy_init() {
            time_t tp;
            time(&tp);
            set_k_time(tp);

            Calendar<Gregorian> g1_cal;

            Calendar<Julian> j1_cal;

            Calendar<Gregorian> g2_cal(g1_cal);

            Calendar<Julian> j2_cal(j1_cal);

            // TODO
            //Calendar<Gregorian> g3_cal(j1_cal);

            Calendar<Gregorian> j3_cal(g1_cal);

            //g3_cal = g1_cal;

            j3_cal = g1_cal;
        }

        void test_calendar_set() {
            time_t tp;
            time(&tp);
            set_k_time(tp);

            Calendar<Gregorian> g_cal;

            TS_ASSERT(g_cal.set_date(2000, 10, 10));

            TS_ASSERT_THROWS(g_cal.set_date(2000, 100, 10), std::invalid_argument);

            Calendar<Julian> j_cal;

            TS_ASSERT(j_cal.set_date(2015, 1, 1));

            TS_ASSERT_THROWS(j_cal.set_date(2000, 10, 100), std::invalid_argument);
        }
};
