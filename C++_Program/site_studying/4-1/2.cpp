#include <iostream>

class Date{
    int year_;
    int month_; // 1부터 12까지
    int day_;   // 1부터 31까지

    bool IsValidDate(int year, int month, int day){
        if(year <= 0)
            return false;
        if(month <= 0 || month > 12)
            return false;
        if(day <= 0 || day >GetLastDayOfMonth(year, month))
            return false;
        return true;
    }
    // 월별 마지막 날짜 반환
    int GetLastDayOfMonth(int year, int month){
        const int dayOfMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if(month == 2 && isLeapYear(year))
            return 29;
        return dayOfMonth[month -1];
    }
    // 윤년 체크
    bool isLeapYear(int year){
        return (year%4 == 0 && year%100 != 0) || (year%400 == 0);
    }
    // 현재 일이 해당 월의 마지막 날을 넘어가면 DateClamping
    int DateClamping(int year, int month, int day){
        int lastDayOfMonth = GetLastDayOfMonth(year, month);
        if(day > lastDayOfMonth){
            return (lastDayOfMonth);
        }
        return (day);
    }

    public:
    bool SetDate(int year, int month, int date){
        if(IsValidDate(year, month, date) == false){
            std::cout << "It is not Valid Date Format!!:" << year<< "." <<month<<"."<<date<<std::endl;
            return (false);
        }
        year_ = year;
        month_ = month;
        day_ = date;

        return (true);
    }
    void AddDay(int inc){
        if(inc <= 0)
            return;
        day_ += inc;
        while(true){
            int daysInCurrentMonth = GetLastDayOfMonth(year_, month_);
            if(day_ > daysInCurrentMonth){
                day_ -= daysInCurrentMonth;
                month_++;

                if(month_ > 12){
                    year_++;
                    month_ = 1;
                }
            }
            else{
                break;
            }
        }
    }
    void AddMonth(int inc){
        if(inc <= 0)
            return;
        month_ += inc;

        while(true){
            if(month_ > 12){
                year_++;
                month_ -= 12;
            }
            else{
                break;
            }
        }
        day_ = DateClamping(year_, month_, day_);
    }
    void AddYear(int inc){
        if(inc <= 0)
            return;
        year_ += inc;
        day_ = DateClamping(year_, month_, day_);
    }
    void ShowDate(){
        std::cout << year_ << "." << month_ << "." << day_ << std::endl;
    }
};

int main(void){
    int year;
    int month;
    int day;
    Date date;
    // input
    while(true){
        std::cout << "1.Year?:" ;
        std::cin >> year;

        std::cout << "2.MONTH?:";
        std::cin >> month;

        std::cout << "3.DAY?:";
        std::cin >> day;

        if(date.SetDate(year,month,day))
            break;
    }
    // loops;
    while(true){
        int type;
        int inc;

        std::cout << "What type do you want Add? (1:Year, 2:Month, 3:Day, 4:Done) : ";
        std::cin >> type;

        if(type == 4)
            break;

        std::cout << "How much add? : ";
        std::cin >> inc;

        if(type == 1)
            date.AddYear(inc);
        else if(type == 2)
            date.AddMonth(inc);
        else if(type == 3)
            date.AddDay(inc);
        // show date
        date.ShowDate();
    }
    return (1);
}