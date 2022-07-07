#include "doenca.h"

const std::set<QString> &Doenca::getSintomas() const
{
    return sintomas;
}

void Doenca::setSintomas(const std::set<QString> &newSintomas)
{
    sintomas = newSintomas;
}

const QString &Doenca::getCausador() const
{
    return causador;
}

void Doenca::setCausador(const QString &newCausador)
{
    causador = newCausador;
}

const QString &Doenca::getNomeDoenca() const
{
    return nomeDoenca;
}

void Doenca::setNomeDoenca(const QString &newNomeDoenca)
{
    nomeDoenca = newNomeDoenca;
}

int Doenca::getId() const
{
    return id;
}

void Doenca::setId(int newId)
{
    id = newId;
}

Doenca::Doenca(){

}

Doenca::Doenca(int id, QString nome, QString causador, std::set<QString> sintomas)
{
    this->setId(id);
    this->setNomeDoenca(nome);
    this->setCausador(causador);
    this->setSintomas(sintomas);
}
