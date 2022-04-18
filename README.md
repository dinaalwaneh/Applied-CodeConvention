# Applied-CodeConvention


First :
I made on convert the old code to code that any developer can read and change easily .
Via :
1. Source File Structure : I put specific order or structure for the project to significantly improve code .
    elements in a source file look like:

         - include statement .
         - constant variables and globale variables .
         - class :
             - Class variables .
             - Constructors .
             - Methods .
         - main methode .
2. Naming Convention :

         - to making the code readable , I made renaming variables name , class name and methods name from : 
            1.  int x to int xPosetion .
            2.  struct Date.dd to Date.Day . 
            3.  struct Date.mm to Date.Month . 
            4.  struct Date.yy to Date.Year . 
            5.  struct Remainder R to struct Remainder Remainder .
            6.  int ForgC to int forgConsole .
            7.  WORD wColor to WORD wordColor .
            8.   wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
                     SetConsoleTextAttribute(hStdOut, wColor);
                     TO :
                     int firstCilor = 0xF0, secoundColor = 0x0F;
                     wordColor = (csbi.wAttributes & firstCilor) + (forgConsole & secoundColor);
                     SetConsoleTextAttribute(hStdOut, wordColor);
            9. int BackC to int backConsole .
            10. int res to int dayPosetion .
            11. int t1 to int temp1  .
            12. int t2 to int temp2  .
            13. int y to year_
            14. method DayNumber to GetDayNumber .
            15. FILE* fp to FILE* file .
            16. int cnt to int count .
            17. int nod to int numberOfDays .
            18. int d to int day .
            19. int x1 to int xPosetion .
            20. int y1 to yPosetion .
            21. int mon to month .
            22. int i to int count .
            23. char ch to char action .
            24. if (action == 'n') to  if (action == NEXT) // const char NEXT = 'n';
            25. if (action == 'q') to  if (action == QUIT) // const char QUIT = 'q';
            26. if (action == 's') to  if (action == SEE) // const char SEE = 's';
            27. if (action == 'p') to  if (action == PREVIOUS) // const char PREVIOUS = 'p';
            28. COORD xy = {0 , 0} to COORD XYPosetion = { XPosetion , YPosetion } // int XPosetion = 0 , YPosetion = 0;  "Global variables" .
    
   //code Refactory :     
 3. Magic Numbers : to make made code easier to understand and maintain , I convert :
 

         1. WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F); To WORD wordColor = ((backConsole & firstCilor) << DISPLACEMENT) + (forgConsole & secoundColor); //const int DISPLACEMENT = 4 ;
         2. from char note[50]; to char note[SIZE_OF_NOTE]; // const int SIZE_OF_NOTE = 50 .
         3. from if (*yy < 1600) to  if (*year < MIN_YEAR) // const int MIN_YEAR = 1600 .
         4. from  if (*mm < 1)  to  if (*month < MIN_MONTH) // const int  MIN_MONTH = 1 .
         5. from if (*mm > 12)  to if (*month > MAX_MONTH) // const int  MIN_MONTH = 12 .
         6. from SetColorAndBackground(15, 1) 
            TO : 
              XPosetion = 15;
              YPosetion = 1;
              color->SetColorAndBackground(XPosetion,YPosetion); // int XPosetion = 0 , YPosetion = 0; "Global variables"
        
 4.I'm using oop to capsulate methods so i'm doing thees and order the code :

          1. I had created a 6 classes :
              a. class Posetion with GoToXYPosetion method .
              b. class Color with SetColor , ClearConsoleToColors , SetColorAndBackground method's .
              c. class Year with checkLeapYear method .
              d. class Day with getNumberOfDays , getDayNumber , getDayName , getDay methods .
              e. class Note checkNote , addNote , showNote methods and  I had created Color* color , posetion* posetion objects .
              f. class Calender that inheretance from Year ,Month , Day , Note and  I had created Color* color , posetion* posetion objects .

        
