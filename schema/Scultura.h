#ifndef SCULTURA_H
#define SCULTURA_H

#include "Opera.h"
#include "QDateTime"

class Scultura : public Opera {
private:
  SculturaMaterial sculturaMaterial;
public:
  Scultura() = default;
  Scultura(const QString &, const QString &, const QString &,u_int, u_int, const QDateTime &, const QDateTime &, enum SculturaMaterial);
  // Implementazioni
  Scultura *clone() const override;
  QString getCategory() const override;
  // Scultura ha valore se fatta di marmo/terracotta/pietra/avorio
  bool hasValue() const override;
  // Il prezzo della Scultura è calcolato al prezzo dell' opera + il materiale * le dimensioni
  double calcuateRealPrice() const override;
  QJsonObject serialize() const override;
  void deserialize(const QJsonObject& obj) override ;
  static SculturaMaterial fromStringToEnum(const QString &);
  // Getter
  QString getSculturaMaterialString() const;
  // Setter
  void setSculturaMaterial(SculturaMaterial);
};

#endif // DIPINTO_H
