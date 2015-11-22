#include "echo.pb.h"
#include <fstream>
#include <iostream>
using namespace std;

void ListMsg(const trpc::EchoRequest &request) { 
    cout << request.request() << endl; 
} 
 
int main(int argc, char* argv[]) { 
    trpc::EchoRequest request;
    fstream input("./log", ios::in | ios::binary); 
    if (!request.ParseFromIstream(&input)) { 
        cerr << "Failed to parse address book." << endl; 
        return -1; 
    } 
 
    ListMsg(request); 
}
