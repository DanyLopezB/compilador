#include <iostream>
#include <fstream>
#include "sintactico.h"

using namespace std;

    int main()
    {
        try {
            sintactico sin;
        }
        catch (std::runtime_error err) {
            cout << err.what()<<endl;
        }

        system("pause");

        return EXIT_SUCCESS;
}


