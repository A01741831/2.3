#ifndef BITACORA_H
#define BITACORA_H
#include <iostream>

using namespace std;

class Bitacora
{
    private:
        int mes;
        string mesS;
        int dia;
        string hora;
        string IP;
        string razon;

    public:
        Bitacora();
        Bitacora(int mes,string mesS,int dia,string hora,string IP,string razon);

        //gets
        int getMes() const;
        string getMesS();
        int getDia() const;
        string getHora();
        string getIP();
        string getRazon();

        bool operator<(Bitacora val);

        ~Bitacora() = default;

};

#endif // BITACORA_H
