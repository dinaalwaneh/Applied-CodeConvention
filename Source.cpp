#include<stdio.h>
#include<conio.h>
#include<windows.h>
#pragma warning(disable : 4996)


int XPosetion = 0 , YPosetion = 0;
const int MIN_YEAR = 1600 , MAX_MONTH = 12 , MIN_MONTH = 1 , SIZE_OF_NOTE = 50 , DISPLACEMENT = 4;
const char QUIT = 'q', NEXT = 'n', SEE = 's', PREVIOUS = 'p';


struct Date {
    int Day;
    int Month;
    int Year;
}Date;
 
struct Remainder {
    int  day;
    int  month;
    char note[SIZE_OF_NOTE];
}Remainder;
 

class Posetion {
    public:
    void GoToXYPosetion(int xPosetion, int yPosetion)
    {    
        COORD XYPosetion = { XPosetion , YPosetion };
        XYPosetion.X = xPosetion; XYPosetion.Y = yPosetion; // X and Y coordinates
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), XYPosetion);
       
    }
};

class Color {
    public :

     //This will set the forground color for printing in a console window.
        void SetColor(int forgConsole)
        {
            WORD wordColor;
            //We will need this handle to get the current background attribute
            HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            //We use csbi for the wAttributes word.
            if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
            {
                //Mask out all but the background attribute, and add in the forgournd color
                int firstCilor = 0xF0, secoundColor = 0x0F;
                wordColor = (csbi.wAttributes & firstCilor) + (forgConsole & secoundColor);
                SetConsoleTextAttribute(hStdOut, wordColor);
            }

            
            return;
        }
        void ClearConsoleToColors(int forgConsole, int backConsole)
        {
            //Set fint color
            int firstCilor = 0xF0, secoundColor = 0x0F;
            WORD wordColor = ((backConsole & firstCilor) << DISPLACEMENT) + (forgConsole & secoundColor);
            //Get the handle to the current output buffer...
            HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
            //This is used to reset the carat/cursor to the top left.
            COORD coord = { XPosetion , YPosetion };
            //A return value... indicating how many chars were written
            //   not used but we need to capture this since it will be
            //   written anyway (passing NULL causes an access violation).
            DWORD count;
            //This is a structure containing all of the console info
            // it is used here to find the size of the console.
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            //Here we will set the current color
            SetConsoleTextAttribute(hStdOut, wordColor);
            if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
            {
                //This fills the buffer with a given character (in this case 32=space).
                FillConsoleOutputCharacter(hStdOut, (TCHAR)32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
                FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
                //This will set our cursor position for the next print statement.
                SetConsoleCursorPosition(hStdOut, coord);
            }
            return;
        }

        void SetColorAndBackground(int forgConsole, int backConsole)
        {
            WORD wColor = ((backConsole & 0x0F) << 4) + (forgConsole & 0x0F);;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
            return;
        }
};


class Year {

public:

    int checkLeapYear(int year) {
        /*
         * checks whether the year passed is leap year or not
         */
        if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
            return 1;  

        return 0;   
    }
};

class Day : public Year{
    public : 

        int getNumberOfDays(int month, int year) { //returns the number of days in given month

            switch (month) {
            case 1: return(31);
            case 2: if (checkLeapYear(year) == 1) return(29); else return(28);
            case 3: return(31);
            case 4: return(30);
            case 5: return(31);
            case 6: return(30);
            case 7: return(31);
            case 8: return(31);
            case 9: return(30);
            case 10: return(31);
            case 11: return(30);
            case 12: return(31);
            default: return(-1);
            }
        }
        const char* getDayName(int day) { //returns the name of the day
            switch (day) {

            case 0: return("Sunday");
            case 1: return("Monday");
            case 2: return("Tuesday");
            case 3: return("Wednesday");
            case 4: return("Thursday");
            case 5: return("Friday");
            case 6: return("Saturday");
            default: return("Error in getName() module.Invalid argument passed");

            }
        }

        int getDayNumber(int day, int month, int year) { //retuns the day number

            int dayPosetion = 0, temp1, temp2, year_ = year;

            /*
             *    calender is Designed for year's after 1600
             */

            year = year - MIN_YEAR;
            while (year >= 100) {
                dayPosetion = dayPosetion + 5;
                year = year - 100;
            }
            dayPosetion = (dayPosetion % 7);
            temp1 = ((year - 1) / 4);
            temp2 = (year - 1) - temp1;
            temp1 = (temp1 * 2) + temp2;
            temp1 = (temp1 % 7);
            dayPosetion = dayPosetion + temp1;
            dayPosetion = dayPosetion % 7;
            temp2 = 0;
            for (temp1 = 1; temp1 < month; temp1++) {
                temp2 += getNumberOfDays(temp1, year_);
            }
            temp2 = temp2 + day;
            temp2 = temp2 % 7;
            dayPosetion = dayPosetion + temp2;
            dayPosetion = dayPosetion % 7;

            if (year_ > 2000) {
                dayPosetion = dayPosetion + 1;
            }

            dayPosetion = dayPosetion % 7;
            return dayPosetion;
        }

        const char* getDay(int day, int month, int year) {

            int day_;
            //check min and max allowed month value
            if (!(month >= MIN_MONTH && month <= MAX_MONTH)) {
                return("Invalid month value");
            }
            //check min and max allowed day value
            if ((day >= 1 && day <= getNumberOfDays(month, year)) == 0) {
                return("Invalid date");
            }
            //check min and max allowed year value
            if (year >= MIN_YEAR) {
                day_ = getDayNumber(day, month, year);
                day_ = day_ % 7;
                return(getDayName(day_));
            }
            else {
                return("Please give year more than 1600");
            }
        }
};

class Note {

    Color* color = new Color();
    Posetion* posetion = new Posetion();

    public:

        int checkNote(int day, int month) {
            FILE* file;
            file = fopen("note.dat", "rb");
            if (file == NULL) {
                printf("Error in Opening the file");
            }
            while (fread(&Remainder, sizeof(Remainder), 1, file) == 1) {
                if (Remainder.day == day && Remainder.month == month) {
                    fclose(file);
                    return 1;
                }
            }
            fclose(file);
            return 0;
        }

        void addNote() {
            FILE* file;
            file = fopen("note.dat", "ab+");
            system("cls");
            posetion->GoToXYPosetion(5, 7);
            printf("Enter the date(DD MM): ");
            scanf_s("%d %d", &Remainder.day, &Remainder.month);
            posetion->GoToXYPosetion(5, 8);
            printf("Enter the Note(50 character max): ");
            fflush(stdin);
            scanf(" %[^\n]", Remainder.note);
            if (fwrite(&Remainder, sizeof(Remainder), 1, file)) {
                posetion->GoToXYPosetion(5, 12);
                puts("Note is saved sucessfully");
                fclose(file);
            }
            else {
                posetion->GoToXYPosetion(5, 12);
                color->SetColor(12);
                puts("\aFail to save!!\a");
                //Clear color
                color->SetColor(15);
            }
            posetion->GoToXYPosetion(5, 15);
            printf("Press any key............");
            _getch();
            fclose(file);
        }

        void showNote(int month) {
            FILE* file;
            int count = 0, isFound = 0;
            system("cls");
            file = fopen("note.dat", "rb");
            if (file == NULL) {
                printf("Error in opening the file");
            }
            while (fread(&Remainder, sizeof(Remainder), 1, file) == 1) {
                if (Remainder.month == month) {
                    posetion->GoToXYPosetion(10, 5 + count);
                    printf("Note %d Day = %d: %s", count + 1, Remainder.day, Remainder.note);
                    isFound = 1;
                    count++;
                }
            }
            if (isFound == 0) {
                posetion->GoToXYPosetion(10, 5);
                printf("This Month contains no note");
            }
            posetion->GoToXYPosetion(10, 7 + count);
            printf("Press any key to back.......");
            _getch();
        }
};

class Month {

    public:
        Color* color = new Color();
        Day* _day = new Day();
        Note *note = new Note();
        Posetion* posetion = new Posetion();

        void increaseMonth(int* month, int* year) {
            /*
             * increase the month by one
             */
            ++* month;

            if (*month > MAX_MONTH) {
                ++* year;
                *month = *month - MAX_MONTH;
            }
        }
        void decreaseMonth(int* month, int* year) {
            /*
             * decrease the month by one
             */

            --* month;

            if (*month < MIN_MONTH) {
                --* year;
                /*
                 * calender is Designed for year's after 1600
                 */
                if (*year < MIN_YEAR) {
                    printf("No record available");
                    return;
                }
                *month = *month + MAX_MONTH;
            }
        }

        void  printMonth(int month, int year, int xPosetion, int yPosetion) { //prints the month with all days
            int numberOfDays, day, count, day_ = 1, xPosetion_ = xPosetion, yPosetion_ = yPosetion, isNote = 0;
            if ((month >= MIN_MONTH && month <= MAX_MONTH) == 0) {
                printf("INVALID MONTH");
                _getch();
                return;
            }

            if ((year >= MIN_YEAR) == 0) {
                printf("INVALID YEAR");
                _getch();
                return;
            }

            posetion->GoToXYPosetion(xPosetion, yPosetion);
            // Print date 
            printf("---------------------------\n");
            XPosetion = 25;
            YPosetion = 6;
            posetion->GoToXYPosetion(XPosetion, YPosetion);
            switch (month) {
            case 1: printf("January");  break;
            case 2: printf("February"); break;
            case 3: printf("March");    break;
            case 4: printf("April");    break;
            case 5: printf("May");      break;
            case 6: printf("June");     break;
            case 7: printf("July");     break;
            case 8: printf("August");   break;
            case 9: printf("September");break;
            case 10: printf("October");  break;
            case 11: printf("November"); break;
            case 12: printf("December"); break;
            }
            printf(" , %d", year);
            XPosetion = 20;
            YPosetion = 7;
            posetion->GoToXYPosetion(XPosetion, YPosetion);
            printf("---------------------------");
            yPosetion += 3;
            posetion->GoToXYPosetion(xPosetion, yPosetion);
            printf("S   M   T   W   T   F   S   ");
            yPosetion++;
            numberOfDays = _day->getNumberOfDays(month, year);
            day = _day->getDayNumber(day_, month, year);
            switch (day) { //locates the starting day in calender
            case 0:
                xPosetion = xPosetion;
                count = 1;
                break;
            case 1:
                xPosetion = xPosetion + 4;
                count = 2;
                break;
            case 2:
                xPosetion = xPosetion + 8;
                count = 3;
                break;
            case 3:
                xPosetion = xPosetion + 12;
                count = 4;
                break;
            case 4:
                xPosetion = xPosetion + 16;
                count = 5;
                break;
            case 5:
                xPosetion = xPosetion + 20;
                count = 6;
                break;
            case 6:
                xPosetion = xPosetion + 24;
                count = 7;
                break;
            default:
                printf("INVALID DATA FROM THE getOddNumber()MODULE");
                return;
            }
            posetion->GoToXYPosetion(xPosetion, yPosetion);
            if (count == 1) {
                color->SetColor(12);
            }
            if (note->checkNote(day_, month) == 1) {
                XPosetion = 15;
                YPosetion = 12;
                color->SetColorAndBackground(XPosetion, YPosetion);
            }
            printf("%02d", day_);
            XPosetion = 15;
            YPosetion = 1;
            color->SetColorAndBackground(XPosetion, YPosetion);
            for (day_ = 2; day_ <= numberOfDays; day_++) {
                if (count % 7 == 0) {
                    yPosetion++;
                    count = 0;
                    xPosetion = xPosetion_ - 4;
                }
                xPosetion = xPosetion + 4;
                count++;
                posetion->GoToXYPosetion(xPosetion, yPosetion);
                if (count == 1) {
                    color->SetColor(12);
                }
                else {
                    //Clear color
                    color->SetColor(15);
                }
                if (note->checkNote(day_, month) == 1) {
                    XPosetion = 15;
                    YPosetion = 12;
                    color->SetColorAndBackground(XPosetion, YPosetion);
                }
                printf("%02d", day_);
                XPosetion = 15;
                YPosetion = 1;
                color->SetColorAndBackground(XPosetion, YPosetion);
            }
            XPosetion = 8;
            YPosetion = yPosetion + 2;
            posetion->GoToXYPosetion(XPosetion, YPosetion);
            color->SetColor(14);
            printf("Press 'n'  to Next, Press 'p' to Previous and 'q' to Quit");
            XPosetion = 8;
            YPosetion = yPosetion + 3;
            posetion->GoToXYPosetion(XPosetion, YPosetion);
            printf("Red Background indicates the NOTE, Press 's' to see note: ");
            //Clear color
            color->SetColor(15);
        }
};


class Calender : public Month , public Day , public Note {
public:
    Color* color = new Color();
    Posetion* posetion = new Posetion();

};

int main() {
    
    Calender * calender =new Calender();
    int forgConsole = 15 , backConsole = 1 , choice;
    char action = 'a';

    calender->color->ClearConsoleToColors(forgConsole, backConsole);
    SetConsoleTitleA("Calender Project - Programming-technique.blogspot.com");
    while (1) {
        system("Cls");
        printf("1. Find Out the Day\n");
        printf("2. Print all the day of month\n");
        printf("3. Add Note\n");
        printf("4. EXIT\n");
        printf("ENTER YOUR CHOICE : ");
        scanf_s("%d", &choice);
        system("Calender System");
        switch (choice) {
        case 1:
            system("Cls");
            printf("Enter date (DD MM YYYY) : ");
            scanf_s("%d %d %d", &Date.Day, &Date.Month, &Date.Year);
            printf("Day is : %s", calender->getDay(Date.Day, Date.Month, Date.Year));
            printf("\nPress any key to continue......");
            _getch();
            break;
        case 2:
            system("Cls");
            printf("Enter month and year (MM YYYY) : ");
            scanf_s("%d %d", &Date.Month, &Date.Year);
            system("Cls");
            while (action != QUIT) {

                XPosetion = 20;
                YPosetion = 5 ;
                calender->printMonth(Date.Month, Date.Year, XPosetion, YPosetion);
                action = _getch();
                if (action == NEXT) {
                    system("Cls");
                    calender->increaseMonth(&Date.Month, &Date.Year); 
                }
                else if (action == PREVIOUS) {
                    system("Cls");
                    calender->decreaseMonth(&Date.Month, &Date.Year); 
                }
                else if (action == SEE) {
                    calender->showNote(Date.Month);
                    system("Cls");
                }
            }
            break;
        case 3:
            calender->addNote();
            break;
        case 4:
            exit(0);
        }
    }
    return 0;
}