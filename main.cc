#include <iostream>
#include <fstream>

#define IDENTIFIER_HEADSTART "<<HEADSTART>>"
#define IDENTIFIER_HEADEND "<<HEADEND>>"
#define IDENTIFIER_DATA "<<DATA>>"
#define IDENTIFIER_EOF "<<EOF>>"

int main()
{
    std::ifstream productos("productos.edb");
    std::string buffer;

    while (getline(productos, buffer))
    {
        if(buffer.compare(IDENTIFIER_HEADSTART) == 0) {
            std::cout << "HEADER: " << std::endl;
            continue;
        }
        if(buffer.compare(IDENTIFIER_HEADEND) == 0) {
            continue;
        }

        if(buffer.compare(IDENTIFIER_DATA) == 0) {
            std::cout << "DATA: " << std::endl;
            continue;
        }

        if(buffer.compare(IDENTIFIER_EOF) == 0) {
            break;
        }

        std::cout << buffer << std::endl;
    }

    productos.close();
}
