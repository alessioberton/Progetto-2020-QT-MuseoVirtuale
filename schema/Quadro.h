#ifndef QUADRO_H
#define QUADRO_H

#include "Dipinto.h"

class Quadro : public Dipinto {
public:
private:
  QuadroMaterial quadroMaterial;
public:
  Quadro() = default;
  Quadro(const QString &, const QString &, const QString &, u_int, u_int, const QDateTime &, const QDateTime &, enum DipintoType, enum QuadroMaterial);
  // Implementazioni
  Quadro *clone() const override;
  QString getCategory() const override;
  // Opera ha valore se fatta di olio/cera/pastelli
  bool hasValue() const override;
  // Il prezzo del Quadro è calcolato al prezzo dell' Dipinto + un sovrapprezzo in base al soggetto pittorico
  double calcuateRealPrice() const override;

  static QuadroMaterial fromStringToEnum(const QString &);
  // Getter
  QString getQuadroMaterialString() const;
  // Setter
  void setQuadroMaterial(QuadroMaterial);

  // Methods
  QJsonObject serialize() const override;
  void deserialize(const QJsonObject& obj) override ;
};

#endif // QUADRO_H
