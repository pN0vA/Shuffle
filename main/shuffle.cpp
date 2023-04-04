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
    cout << "\nWhat do you want to do:\n 1.Shellcode Injector\n 2.Shellcode Generator\n 3.Shellcode Decoder\n 4.Shellcode Template\n 5.Exit Program\n\n :";
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
        system("g++ Injector/inject.cpp -o inject");
        system(("./inject " + ipz).c_str());
      }else if (choice == 2){
        string ipz;
        cout << "WARNING: you will need a windows computer to use and exploit this.\n\n";
        cout << "What is the ip to inject: ";
        cin >> ipz;
        system("i686-w64-mingw32-g++ -o inject.exe Injector/windowsinject.cpp -lws2_32");
        system(("./inject " + ipz).c_str());
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
      string stringz;
      cout << "\nWhat is the string you want: ";
      cin >> stringz;
      system("g++ shellcode/shellgen.c -o shel");
      system(("./shel " + stringz).c_str());
      return 0;

    }else if (choice == 3) {
      const string DEC = R"(
    ____                      __         
   / __ \___  _________  ____/ /__  _____
  / / / / _ \/ ___/ __ \/ __  / _ \/ ___/
 / /_/ /  __/ /__/ /_/ / /_/ /  __/ /    
/_____/\___/\___/\____/\__,_/\___/_/     
      )";
      cout << DEC;
      system("g++ shellcode/dec3.cpp -lcapstone -o dec");
      system("./dec");
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
      system("g++ templates/open.c -o open");
      system("./open");
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
          system("g++ misc/games/48.cpp -o 48");
          system("./48");
          return 0;
        }else if (games == 2){
          system("g++ misc/games/tetris.c -lncurses -o tet");
          system("./tet");
        }else if (games == 3){
          system("g++ misc/games/snake.c -lncurses -o snake");
          system("./snake");
        }

      }else if (choi == 2){
        int mik;
        cout << "\nWelcome to My Misc Dump. What would you like to choose:\n 1. Ip Finder\n 2. PortScanner\n 3. Keylogger Script\n 4. Exit\n\n :";
        cin >> mik;
        if (mik == 1) {
          system("g++ misc/misc/network.cpp -o net");
          system("./net");
        }else if (mik == 2) {
          string ipz;
          cout << "What is the ip: ";
          cin >> ipz;
          system("g++ misc/misc/nethelp.cpp -o nethelp");
          system(("./nethelp " + ipz).c_str());
        }else if (mik == 3) {
          system("g++ misc/misc/keylo.c -o keyl");
          system("./keyl");
        }else if (mik == 4){
          exit(3);
        }
      }
    }
}