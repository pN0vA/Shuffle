#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

int main() {
    //ART
    const string ART = R"(                                                                                                                                    
    _____ __          __________   
  / ___// /_  __  __/ __/ __/ /__ 
  \__ \/ __ \/ / / / /_/ /_/ / _ \
 ___/ / / / / /_/ / __/ __/ /  __/
/____/_/ /_/\__,_/_/ /_/ /_/\___/ 
                                 
       By: n0vA                                                                                                                                                                                                                                                                                                                                                                   
    )";

    cout << ART;
    //choice number 1337 is a secret mode
    int choice;
    cout << "\nWhat do you want to do:\n 1.Shellcode Injector\n 2.Shellcode Generator\n 3.Shellcode Decoder\n 4.Shellcode Template\n 5.Metasploit Generator\n 6.File Compiler\n 7.Exit Program\n\n :";
    cin >> choice;
    if (choice == 1){
      const string BO = R"(
        
    ____        _           __            
   /  _/___    (_)__  _____/ /_____  _____
   / // __ \  / / _ \/ ___/ __/ __ \/ ___/
 _/ // / / / / /  __/ /__/ /_/ /_/ / /    
/___/_/ /_/_/ /\___/\___/\__/\____/_/     
         /___/                            
                                                                               
      )";
      cout << BO;
      int choice;
      cout << "\nchoose an option:\n 1. Linux\n 2. Windows\n 3. Exit\n\n :";
      cin >> choice;
      if (choice == 1){
        string ipz;
        cout << "\nWhat is the ip to inject: ";
        cin >> ipz;
        system("g++ Injector/inject.cpp -o .run/inject");
        system(("./.run/inject " + ipz).c_str());
      }else if (choice == 2){
        string ipz;
        cout << "WARNING: you will need a windows computer to use and exploit this.\n\n";
        cout << "What is the ip to inject: ";
        cin >> ipz;
        system("i686-w64-mingw32-g++ -o .run/inject.exe Injector/windowsinject.cpp -lws2_32");
        system(("./.run/inject " + ipz).c_str());
      }else if (choice == 3){
        exit(3);
      }
    }else if (choice == 2) {
      const string SH = R"(
   _____ __         ____               __        ______                           __            
  / ___// /_  ___  / / /________  ____/ /__     / ____/__  ____  ___  _________ _/ /_____  _____
  \__ \/ __ \/ _ \/ / / ___/ __ \/ __  / _ \   / / __/ _ \/ __ \/ _ \/ ___/ __ `/ __/ __ \/ ___/
 ___/ / / / /  __/ / / /__/ /_/ / /_/ /  __/  / /_/ /  __/ / / /  __/ /  / /_/ / /_/ /_/ / /    
/____/_/ /_/\___/_/_/\___/\____/\__,_/\___/   \____/\___/_/ /_/\___/_/   \__,_/\__/\____/_/     
                                                                                              
      )";
      cout << SH;
      int choice;
      cout << "\nWhat One Do You Need Shellcode For:\n 1. Unix/Linux\n 2. Arm\n 3. Windows\n 4. Exit\n\n :";
      cin >> choice;

      if (choice == 1) {
        string stringz;
        cout << "\nWhat is the string you want: ";
        cin >> stringz;
        system("g++ shellcode/shellgen.cpp -o .run/shel");
        system(("./.run/shel " + stringz).c_str());
        return 0;
      } else if (choice == 2){
        string stringz;
        cout << "\nWhat is the string you want: ";
        cin >> stringz;
        system("g++ -no-pie -Wall -Wextra -pedantic -std=c++11 -O3 -o .run/shel shellcode/armgen.cpp");
        system(("./.run/shel " + stringz).c_str());
        return 0;
      } else if (choice == 3){
        string stringz;
        cout << "\nWhat is the string you want: ";
        cin >> stringz;
        system("g++ shellcode/wingen.cpp -o .run/shel");
        system(("./.run/shel " + stringz).c_str());
        return 0;
      }else if (choice == 4){
        exit(3);
      }
      

    }else if (choice == 3) {
      const string DEC = R"(
    ____                      __         
   / __ \___  _________  ____/ /__  _____
  / / / / _ \/ ___/ __ \/ __  / _ \/ ___/
 / /_/ /  __/ /__/ /_/ / /_/ /  __/ /    
/_____/\___/\___/\____/\__,_/\___/_/     
      )";
      cout << DEC;
      system("g++ shellcode/dec3.cpp -lcapstone -o .run/dec");
      system("./.run/dec");
      return 0;

    }else if (choice == 4) {
      const string TEMP = R"(
  ______                     __      __           
 /_  __/__  ____ ___  ____  / /___ _/ /____  _____
  / / / _ \/ __ `__ \/ __ \/ / __ `/ __/ _ \/ ___/
 / / /  __/ / / / / / /_/ / / /_/ / /_/  __(__  ) 
/_/  \___/_/ /_/ /_/ .___/_/\__,_/\__/\___/____/  
                  /_/                             
      )";
      cout << TEMP;
      system("g++ templates/open.cpp -o .run/open");
      system("./.run/open");
    }else if (choice == 5){
      const string MET = R"(
    __  ___     __                   __      _ __     ______                           __            
   /  |/  /__  / /_____ __________  / /___  (_) /_   / ____/__  ____  ___  _________ _/ /_____  _____
  / /|_/ / _ \/ __/ __ `/ ___/ __ \/ / __ \/ / __/  / / __/ _ \/ __ \/ _ \/ ___/ __ `/ __/ __ \/ ___/
 / /  / /  __/ /_/ /_/ (__  ) /_/ / / /_/ / / /_   / /_/ /  __/ / / /  __/ /  / /_/ / /_/ /_/ / /    
/_/  /_/\___/\__/\__,_/____/ .___/_/\____/_/\__/   \____/\___/_/ /_/\___/_/   \__,_/\__/\____/_/     
                          /_/                                                                       
      )";     
      cout << MET;
      cout << "\nPut 'options' in the format selection bar to see the selection.\n";
      string format;
      cout << "\nWhich would you like the shellcode to format to:\n\n :";
      cin >> format;
      if (format == "options"){
        cout << "\nYour options:\n 1. c\n 2.rust\n 3.python\n 4.java\n 5.golang\n 6.bash\n 7.hex\n 8.vbscript\n 9.exe\n 10.dll\n 11.msi\n 12.ducky-script-psh\n 13.elf\n 14.asp\n 15.psh\n 16.psh-cmd\n 17.vba\n 18.csharp\n 19.axis2\n 20.jar\n 21.jsp\n 22.js_be (big endian)\n 23.js_le (little endian)\n 24.ruby\n";
        return 0;
      }
      string payload;
      cout << "\nWhat is the metasploit payload: \n\n:";
      cin >> payload;
      
      system(("sudo msfvenom -p" + payload + " --format " + format).c_str());
      return 0;
      
      }else if (choice == 6){
        const string FC = R"(
    _______ __        ______                      _ __         
   / ____(_) /__     / ____/___  ____ ___  ____  (_) /__  _____
  / /_  / / / _ \   / /   / __ \/ __ `__ \/ __ \/ / / _ \/ ___/
 / __/ / / /  __/  / /___/ /_/ / / / / / / /_/ / / /  __/ /    
/_/   /_/_/\___/   \____/\____/_/ /_/ /_/ .___/_/_/\___/_/     
                                       /_/                     
        )";

        cout << FC;
        string file;
        cout << "\n\n What is the name of the File: \n\n:";
        cin >> file;
        string name;
        cout << "What would you like to name the executable: \n:";
        cin >> name;
        system(("g++ " + file + " -o " + name).c_str());
        string elsa;
        cout << "Would you like to run the file(y/n): ";
        cin >> elsa;
        if (elsa == "y"){
          system(("./"+ name).c_str());
        }else if (elsa == "n"){
          exit(3);
        }
      }else if (choice == 1337) {
      const string leet = R"(
  ________            _____                     __ 
 /_  __/ /_  ___     / ___/___  _____________  / /_
  / / / __ \/ _ \    \__ \/ _ \/ ___/ ___/ _ \/ __/
 / / / / / /  __/   ___/ /  __/ /__/ /  /  __/ /_  
/_/ /_/ /_/\___/   /____/\___/\___/_/   \___/\__/  
                                                 
      )";
      cout << leet;
      cout << "You found the secret mode. Enjoy! Remember we all do a little trolling.";
      int choi;
      cout << "\nWhat is your choice:\n 1. Games\n 2. Misc\n\n : ";
      cin >> choi;
      if (choi == 1){
        int games;
        cout << "\nWhat game would you like to play:\n 1. 2048\n 2. Tetris\n 3. Snake \n\n :";
        cin >> games;
        if (games == 1){
          system("g++ misc/games/48.cpp -o .run/48");
          system("./.run/48");
          return 0;
        }else if (games == 2){
          system("g++ misc/games/tetris.c -lncurses -o .run/tet");
          system("./.run/tet");
        }else if (games == 3){
          system("g++ misc/games/snake.c -lncurses -o .run/snake");
          system("./.run/snake");
        }

      }else if (choi == 2){
        int mik;
        cout << "\nWelcome to My Misc Dump. What would you like to choose:\n 1. Ip Finder\n 2. PortScanner\n 3. Keylogger Script\n 4. Exit\n\n :";
        cin >> mik;
        if (mik == 1) {
          system("g++ misc/misc/network.cpp -o .run/net");
          system("./.run/net");
        }else if (mik == 2) {
          string ipz;
          cout << "What is the ip: ";
          cin >> ipz;
          system("g++ misc/misc/nethelp.cpp -o .run/nethelp");
          system(("./.run/nethelp " + ipz).c_str());
        }else if (mik == 3) {
          system("g++ misc/misc/keylo.cpp -o .run/keyl");
          system("./.run/keyl");
        }else if (mik == 4){
          exit(3);
        }
      }
    }else if (choice == 6){
      exit(3);
    }
}