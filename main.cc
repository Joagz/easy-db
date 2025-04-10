#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <sstream>
#include <algorithm>

#define IDENTIFIER_HEADSTART "<<HEADSTART>>"
#define IDENTIFIER_HEADEND "<<HEADEND>>"
#define IDENTIFIER_DATA "<<DATA>>"
#define IDENTIFIER_EOF "<<EOF>>"
#define ZONE_SEPARATOR '\n'
#define DATA_SEPARATOR ','
#define BUFFER_SIZE 512

typedef struct
{
    std::string name;
    size_t cols;
    size_t rows;
} table_header_t;

typedef struct
{
    int id;
    std::string name;
    float price;
    std::string description;
    int stock;
} table_data_t;

void remove_whitespace(std::string *ptr)
{
    std::string::iterator pos = std::remove(ptr->begin(), ptr->end(), ' ');
    ptr->erase(pos, ptr->end());
}

void remove_first_whitespace(std::string *ptr)
{
    auto it = std::find(ptr->begin(), ptr->end(), ' ');
    if (it != ptr->end())
        ptr->erase(it);
}

// extraemos una lista de tuplas (clave: valor) genéricas, esto sirve para separar
// el header
std::vector<std::tuple<std::string, std::string>> tokenize(std::string str, char separator)
{
    remove_whitespace(&str);

    std::vector<std::tuple<std::string, std::string>> result;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, separator))
    {
        size_t sep = token.find(':');
        if (sep != std::string::npos)
        {
            std::string key = token.substr(0, sep);
            std::string value = token.substr(sep + 1);

            result.push_back({key, value});
        }
    }

    return result;
}

// Parseamos el header en un table_header_t*
void get_header(std::string headstr, table_header_t *head)
{
    std::vector<std::tuple<std::string, std::string>> kvpairs = tokenize(headstr, ZONE_SEPARATOR);

    head->name = std::get<1>(kvpairs.at(0));
    head->cols = std::atoi(std::get<1>(kvpairs.at(1)).c_str());
    head->rows = std::atoi(std::get<1>(kvpairs.at(2)).c_str());

    std::cout << "head->name: " << head->name << "\n";
    std::cout << "head->cols: " << head->cols << "\n";
    std::cout << "head->rows: " << head->rows << "\n";
}

std::vector<std::string> tokenize_table(std::string datastr)
{
    std::vector<std::string> result;
    std::stringstream ss(datastr);
    std::string token;

    while (std::getline(ss, token, DATA_SEPARATOR))
    {
        remove_first_whitespace(&token);
        result.push_back(token);
    }

    return result;
}

int main()
{
    std::ifstream productos("productos.edb");
    std::string buffer;
    table_header_t head;

    // leemos el archivo linea por linea, extraemos cada linea y la colocamos en el buffer
    while (getline(productos, buffer))
    {
        // si encontramos <<HEADSTART>> leemos el head y lo guardamos en un table_header_t
        if (buffer.compare(IDENTIFIER_HEADSTART) == 0)
        {
            std::string headstr;
            while (getline(productos, buffer) && buffer.compare(IDENTIFIER_HEADEND) != 0)
            {
                char str[2] = {0};
                str[0] = ZONE_SEPARATOR;

                headstr.append(buffer);
                headstr.append(str);
            }

            get_header(headstr, &head);
            continue;
        }

        // section: TODO

        if (buffer.compare(IDENTIFIER_HEADEND) == 0)
        {
            continue;
        }
        // Acá se extraerían los datos
        if (buffer.compare(IDENTIFIER_DATA) == 0)
        {
            table_data_t data;
            while (getline(productos, buffer) && buffer.compare(IDENTIFIER_EOF) != 0)
            {
                std::vector<std::string> tokens = tokenize_table(buffer);

               
            }
            continue;
        }

        if (buffer.compare(IDENTIFIER_EOF) == 0)
        {
            break;
        }

        // std::cout << buffer << std::endl;
    }

    productos.close();
}
