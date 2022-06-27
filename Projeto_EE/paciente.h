#ifndef PACIENTE_H
#define PACIENTE_H

#include <limits>
#include <QString>
#include <vector>


class paciente
{
private:
    QString nome;
    int idade;
    char sexo;
    float peso;
    QString tipoSanguineo;
    std::vector<QString> sintomas;

public:
    paciente();
    paciente(QString nome, int idade, char sexo, float peso, QString tipoSanguineo, std::vector<QString> sintomas);
};

#endif // PACIENTE_H
