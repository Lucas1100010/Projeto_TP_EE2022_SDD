#ifndef PACIENTE_H
#define PACIENTE_H

#include <limits>
#include <QString>
#include <vector>
#include <set>


class Paciente
{
private:
    QString nome;
    int idade;
    QString sexo;
    float peso;
    QString tipoSanguineo;
    std::set<QString> sintomas;
    int idPaciente;

public:
    Paciente();
    Paciente(int idPaciente,QString nome, int idade, QString sexo, float peso, QString tipoSanguineo, std::set<QString> sintomas);
    const QString &getNome() const;
    void setNome(const QString &newNome);
    int getIdade() const;
    void setIdade(int newIdade);
    QString getSexo() const;
    void setSexo(QString newSexo);
    float getPeso() const;
    void setPeso(float newPeso);
    const QString &getTipoSanguineo() const;
    void setTipoSanguineo(const QString &newTipoSanguineo);

    int getIdPaciente() const;
    void setIdPaciente(int newIdPaciente);
    const std::set<QString> &getSintomas() const;
    void setSintomas(const std::set<QString> &newSintomas);
};

#endif // PACIENTE_H
