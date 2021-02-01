#ifndef MOSAICO_H
#define MOSAICO_H

#include "Opera.h"

class Mosaico : public Opera {

public:
  enum MosaicoMaterial { oro, argento, marmo, pietra, vetro, conchiglia};
  Mosaico() = default;
  Mosaico(const QString &, const QString &, const QString &, u_int, u_int, const QDateTime &, const QDateTime &, MosaicoMaterial);
  // Implementazioni
  Mosaico *clone() const override;
  QString getCategory() const override;
  // Dipinto ha valore se fatta di olio/cera/pastelli
  bool hasValue() const override;
  // Il prezzo del Dipinto è calcolato al prezzo dell' opera + il materiale * le dimensioni
  double calcuateRealPrice() const override;

  QJsonObject serialize() const override;
  void deserialize(const QJsonObject& obj) override ;

  static MosaicoMaterial fromStringToEnum(const QString &);
  // Getter
  QString getMosaicoMaterialString() const;
  // Setter
  void setMosaicoMaterial(MosaicoMaterial);
private:
  MosaicoMaterial mosaicoMaterial;

};

#endif // MOSAICO_H
