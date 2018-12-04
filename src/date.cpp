/*** Developed by Polina Shlepakova ***/

#include "date.h"
#include <iomanip>

Date::Date(int day, Month month, int year): _day(day), _month(month), _year(year) {
	if (!validate(_day, Month(_month), _year)) {
		_day = 1;
		_month = 1;
		_year = 0;
	}
}

Date::Date(int day, int month, int year): _day(day), _month(month), _year(year) {
	if (!validate(_day, Month(_month), _year)) {
		_day = 1;
		_month = 1;
		_year = 0;
	}
}

Date::Date(const Date& date): 
	_day(date.day()), _month(date.month()), _year(date.year())
{}

Date::~Date() {}

int Date::day() const {return _day;}
Date::Month Date::month() const {return Month(_month);}
int Date::year() const {return _year;}

// set day if valid, if not - leave untouched
void Date::setDay(int day) {
	if (validate(day, month(), year())) {
		_day = day;
	}
}

// set month if valid, if not - leave untouched
void Date::setMonth(int month) {
	if (validate(day(), Month(month), year())) {
		_month = Month(month);
	}
}

void Date::setYear(int year) {
	if (validate(day(), month(), year)) {
		_year = year;
	}
}

// check if the year is a leap year
bool Date::leapYear(int y) const {
	if (y % 4 == 0) {
		if (y % 100 == 0) {
			if (y % 400 == 0) {
				return true;
            } else {
				// not divisible by 400
				return false;
			}
		} else {
			// not divisible by 100
            return true;
		}
	} else {
		// not divisible by 4
		return false;
	}
}

bool Date::validate(int day, Month month, int year) {
	return  day >= 1 && day <= numberOfDays() && 
			month >= 1 && month <= 12 && year >= 0;
}

int Date::numberOfDays(int month) const {
	if (month == 0) {
		month = _month;
	}
	switch(Month(month)) {
   		// in february check for leap year
		case feb:
			return 28 + leapYear(year()); // true will convert to 1, false to 0
			break;
		case apr: case jun: case sep: case nov:
			return 30;
			break;
		case jan: case mar: case may: case jul: case aug: case oct: case dec:
			return 31;
			break;
		// invalid month
		default:
			return -1;
	}
}

// returns number of days passed from 00/00/0000
Date::operator int() const {
	// initialize result using years and days
	unsigned int res = year() * 365 + day();
 
	// add days for previous months in given year
	for (int i = 1; i < month() - 1; i++) {
		res += numberOfDays(i);
	}
 
	// every leap year has 366 days, so add 1 day for every leap year
	// current year is not considered, because if it's a leap year
	// and feb has alredy passed, 1 day was already added while adding days for months
	int years = year() - 1;
    // year is a leap year if it is a multiple of 4,
    // multiple of 400 and not a multiple of 100
    res += years / 4 + years / 400 - years / 100;

	return res;
}

// returns the difference in days
int operator-(const Date& d1, const Date& d2) {
	return static_cast<int>(d1) - static_cast<int>(d2);
}

bool operator<(const Date& d1, const Date& d2) {
	if (d1.year() != d2.year()) {
		return d1.year() < d2.year();
	}
	if (d1.month() != d2.month()) {
		return d1.month() < d2.month();
	}
	// at this point, year and month are equal, so just compare days
	return d1.day() < d2.day();
}

bool operator>(const Date& d1, const Date& d2) {
	return d2 < d1;
}

bool operator<=(const Date& d1, const Date& d2) {
	return d1 == d2 ? true : d1 < d2;
}

bool operator>=(const Date& d1, const Date& d2) {
	return d2 <= d1;
}

bool operator==(const Date& d1, const Date& d2) {
	return	d1.year() == d2.year() && 
			d1.month() == d2.month() && 
			d1.day() == d2.day();
}

bool operator!=(const Date& d1, const Date& d2) {
	return !(d1 == d2);
}

std::istream& operator>>(std::istream& is, Date& date) {
	for (int i = 0; i < nFormats; ++i) {
		std::cout << (i + 1) << ":\t" << formatStrings[i] << std::endl;
	}
	std::cout << "Choose date format (default 1): ";
	int tmp = -1;
	is >> tmp;
	tmp = tmp >= 1 && tmp <= nFormats ? tmp : 1;
	Date::Format format = Date::Format(tmp - 1);

	std::cout << "Enter date in " << formatStrings[format] << ": ";
	int d = 0, m = 0, y = 0;
	switch (format) {
	case Date::dmy_space: case Date::dmy_period: 
	case Date::dmy_hyphen: case Date::dmy_slash:
		is >> d; is.get();
		is >> m; is.get();
		is >> y;
		break;
	case Date::ymd_space: case Date::ymd_period: 
	case Date::ymd_hyphen: case Date::ymd_slash:
		is >> y; is.get();
		is >> m; is.get();
		is >> d;
		break;
	case Date::mdy_space: case Date::mdy_period: 
	case Date::mdy_hyphen: case Date::mdy_slash:
		is >> m; is.get();
		is >> d; is.get();
		is >> y;
		break;
	default:
		return is;
	}
	date.setDay(d);
	date.setMonth(m);
	date.setYear(y);

	return is;
}

void Date::setFormat(std::ios_base& s, Date::Format f) {
	flag(s) = f;
}

Date::Format Date::getFormat(std::ios_base& s) {
	return (Date::Format) flag(s);
}

long& Date::flag(std::ios_base& s) {
	static int n = std::ios_base::xalloc();
	return s.iword(n);
}

std::ostream& dmy_space(std::ostream& os) {
	Date::setFormat(os, Date::dmy_space);
	return os;
}

std::ostream& dmy_period(std::ostream& os) {
	Date::setFormat(os, Date::dmy_period);
	return os;
}

std::ostream& dmy_hyphen(std::ostream& os) {
	Date::setFormat(os, Date::dmy_hyphen);
	return os;
}

std::ostream& dmy_slash(std::ostream& os) {
	Date::setFormat(os, Date::dmy_slash);
	return os;
}

std::ostream& ymd_space(std::ostream& os) {
	Date::setFormat(os, Date::ymd_space);
	return os;
}

std::ostream& ymd_period(std::ostream& os) {
	Date::setFormat(os, Date::ymd_period);
	return os;
}

std::ostream& ymd_hyphen(std::ostream& os) {
	Date::setFormat(os, Date::ymd_hyphen);
	return os;
}

std::ostream& ymd_slash(std::ostream& os) {
	Date::setFormat(os, Date::ymd_slash);
	return os;
}

std::ostream& mdy_space(std::ostream& os) {
	Date::setFormat(os, Date::mdy_space);
	return os;
}

std::ostream& mdy_period(std::ostream& os) {
	Date::setFormat(os, Date::mdy_period);
	return os;
}

std::ostream& mdy_hyphen(std::ostream& os) {
	Date::setFormat(os, Date::mdy_hyphen);
	return os;
}

std::ostream& mdy_slash(std::ostream& os) {
	Date::setFormat(os, Date::mdy_slash);
	return os;
}

std::ostream& operator<<(std::ostream& os, const Date& d) {
	Date::Format format = Date::getFormat(os);
	char separator = ' ';
	switch (format) {
	case Date::dmy_space: case Date::ymd_space: case Date::mdy_space:
		separator = ' ';
		break;
	case Date::dmy_period: case Date::ymd_period: case Date::mdy_period:
		separator = '.';
		break;
	case Date::dmy_hyphen: case Date::ymd_hyphen: case Date::mdy_hyphen:
		separator = '-';
		break;
	case Date::dmy_slash: case Date::ymd_slash: case Date::mdy_slash:
		separator = '/';
		break;
	default:
		format = Date::dmy_space;
		separator = ' ';
		break;
	}

	os << std::setfill('0');
	switch (format) {
	case Date::dmy_space: case Date::dmy_period: 
	case Date::dmy_hyphen: case Date::dmy_slash:
		os	<< std::setw(2) << d.day() << separator 
			<< std::setw(2) << d.month() << separator 
			<< std::setw(4) << d.year();
		break;
	case Date::ymd_space: case Date::ymd_period: 
	case Date::ymd_hyphen: case Date::ymd_slash:
		os  << std::setw(4) << d.year() << separator 
			<< std::setw(2) << d.month() << separator 
			<< std::setw(2) << d.day();
		break;
	case Date::mdy_space: case Date::mdy_period: 
	case Date::mdy_hyphen: case Date::mdy_slash:
		os	<< std::setw(2) << d.month() << separator 
			<< std::setw(2) << d.day() << separator 
			<< std::setw(4) << d.year();
		break;
	}
	return os;
}
