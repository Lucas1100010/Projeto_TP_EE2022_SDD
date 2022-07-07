#ifndef DOENCA_H
#define DOENCA_H

#include <QString>
#include <set>

class Doenca
{
private:
    int id;
    QString nomeDoenca;
    QString causador;
    std::set<QString> sintomas;


public:
    Doenca();
    Doenca(int id, QString nome, QString causador, std::set<QString>sintomas);
    const std::set<QString> &getSintomas() const;
    void setSintomas(const std::set<QString> &newSintomas);
    const QString &getCausador() const;
    void setCausador(const QString &newCausador);
    const QString &getNomeDoenca() const;
    void setNomeDoenca(const QString &newNomeDoenca);
    int getId() const;
    void setId(int newId);
};

#endif // DOENCA_H
