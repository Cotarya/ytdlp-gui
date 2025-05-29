#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
//made with help of chatgpt and made in Visual Studio 2022 Professional
using namespace std;

enum MenuOption { DOWNLOAD = 0, UPDATE = 1 };

bool fileExists(const string& filename) {
    DWORD attribs = GetFileAttributesA(filename.c_str());
    return (attribs != INVALID_FILE_ATTRIBUTES && !(attribs & FILE_ATTRIBUTE_DIRECTORY));
}

void printMenu(int selected) {
    system("cls");
    cout << "Use arrow keys to navigate and press Enter to select:\n\n";

    string options[2] = { "Download video", "Update yt-dlp" };
    for (int i = 0; i < 2; ++i) {
        if (i == selected)
            cout << " > " << options[i] << endl;
        else
            cout << "   " << options[i] << endl;
    }
}

void downloadVideo() {
    if (!fileExists("yt-dlp.exe")) {
        cout << "Error: yt-dlp.exe not found in the current folder!" << endl;
        system("pause");
        return;
    }

    string url;
    cout << "\nEnter video URL: ";
    getline(cin, url);

    if (url.empty()) {
        cout << "No URL provided. Returning to menu\n";
        system("pause");
        return;
    }

    cout << "Use cookies.txt? (Y/n): ";
    string useCookies;
    getline(cin, useCookies);

    bool addCookies = (useCookies.empty() || useCookies == "Y" || useCookies == "y");

    string command = "powershell -Command \"./yt-dlp.exe " + url;
    if (addCookies)
        command += " --cookies cookies.txt";
    command += "\"";

    system(command.c_str());
    system("pause");
}

void updateYTDLP() {
    if (!fileExists("yt-dlp.exe")) {
        cout << "Error: yt-dlp.exe not found in the current folder!" << endl;
        system("pause");
        return;
    }

    string command = "powershell -Command \"./yt-dlp.exe -U\"";
    system(command.c_str());
    system("pause");
}

int main() {
    int selected = 0;
    bool running = true;

    while (running) {
        printMenu(selected);

        int key = _getch();
        if (key == 224) { // стрелка
            key = _getch();
            if (key == 72) selected = (selected - 1 + 2) % 2; // up
            if (key == 80) selected = (selected + 1) % 2;     // down
        }
        else if (key == 13) { // Enter
            system("cls");
            if (selected == DOWNLOAD)
                downloadVideo();
            else if (selected == UPDATE)
                updateYTDLP();
        }
    }

    return 0;
}