#include "echo.pb.h"
#include <fstream>
#include <iostream>
using namespace std;

int main(void) 
{ 
  
    trpc::EchoRequest request; 
    request.set_request("test");
    
    // Write the new address book back to disk. 
    fstream output("./log", ios::out | ios::trunc | ios::binary); 
        
    if (!request.SerializeToOstream(&output)) { 
        cout << "Failed to write msg." << endl; 
        return -1; 
    }
    return 0; 
}
