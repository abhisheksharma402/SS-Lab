#include<bits/stdc++.h>
#include <fstream>
#include <unistd.h>

int main() {
    // Create five new files
    for (int i = 1; i <= 5; ++i) {
        std::string filename = "file_" + std::to_string(i) + ".txt";
        std::ofstream file(filename);
    }

    // Fork and run infinite loop in the background
    //pid_t pid = fork();
    
    //if (pid == 0) {
        // Child process: Run infinite loop
        while (true) {
		sleep(20);
           //std::cout << "Looping..." << std::endl;
            //sleep(1);
        }

   // }

    return 0;
}
