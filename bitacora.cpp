#include "bitacora.h"
#include <iostream>

Bitacora::Bitacora()
{
    mes=0;
    mesS="";
    dia=0;
    hora="";
    IP="";
    razon="";

}

Bitacora::Bitacora(int mes,string mesS,int dia,string hora,string IP,string razon)
{
    this->mes=mes;
    this->mesS=mesS;
    this->dia=dia;
    this->hora=hora;
    this->IP=IP;
    this->razon=razon;
}

int Bitacora::getMes() const
{
    return mes;
}

string Bitacora::getMesS()
{
    return mesS;
}

int Bitacora::getDia() const
{
    return dia;
}

string Bitacora::getHora()
{
    return hora;
}

string Bitacora::getIP()
{
    return IP;
}

string Bitacora::getRazon()
{
    return razon;
}

/* Sobrecarga del operador para comparar dos objetos de tipo Bitacora por el mes
 y, si este es igual, despues por el dia. Su funcion es ordenar las entradas de la bitocora por fecha */
bool Bitacora::operator<(Bitacora val) {
    if (mes == val.mes) {
        if (dia == val.dia) {
            return hora < val.hora;
        }
        return dia < val.dia;
    }
    return mes < val.mes;
}
