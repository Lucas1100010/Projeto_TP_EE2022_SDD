#include "paciente.h"

const QString &Paciente::getNome() const
{
    return nome;
}

void Paciente::setNome(const QString &newNome)
{
    nome = newNome;
}

int Paciente::getIdade() const
{
    return idade;
}

void Paciente::setIdade(int newIdade)
{
    idade = newIdade;
}

QString Paciente::getSexo() const
{
    return sexo;
}

void Paciente::setSexo(QString newSexo)
{
    sexo = newSexo;
}

float Paciente::getPeso() const
{
    return peso;
}

void Paciente::setPeso(float newPeso)
{
    peso = newPeso;
}

const QString &Paciente::getTipoSanguineo() const
{
    return tipoSanguineo;
}

void Paciente::setTipoSanguineo(const QString &newTipoSanguineo)
{
    tipoSanguineo = newTipoSanguineo;
}



Paciente::Paciente(int id,QString nome, int idade, QString sexo, float peso, QString tipoSanguineo, std::set<QString> sintomas){
    this->setIdPaciente(id);
    this->setNome(nome);
    this->setIdade(idade);
    this->setSexo(sexo);
    this->setPeso(peso);
    this->setTipoSanguineo(tipoSanguineo);
    this->setSintomas(sintomas);
}

int Paciente::getIdPaciente() const
{
    return idPaciente;
}

void Paciente::setIdPaciente(int newIdPaciente)
{
    idPaciente = newIdPaciente;
}

const std::set<QString> &Paciente::getSintomas() const
{
    return sintomas;
}

void Paciente::setSintomas(const std::set<QString> &newSintomas)
{
    sintomas = newSintomas;
}

Paciente::Paciente()
{

}
