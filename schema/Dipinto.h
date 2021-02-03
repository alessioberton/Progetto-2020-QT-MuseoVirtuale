#ifndef DIPINTO_H
#define DIPINTO_H

#include "Opera.h"

class Dipinto : public Opera {
private:
  DipintoType dipintoType;
public:
  Dipinto() = default;
  Dipinto(const QString &, const QString &, const QString &, u_int, u_int, const QDateTime &, const QDateTime &, DipintoType);
  // Implementazioni
  Dipinto *clone() const override;
  QString getCategory() const override;
  // Dipinto ha valore se fatta di olio/cera/pastelli
  bool hasValue() const override;
  // Il prezzo del Dipinto è calcolato al prezzo dell' opera + il materiale * le dimensioni
  double calcuateRealPrice() const override;
  QJsonObject serialize() const override;
  void deserialize(const QJsonObject&) override ;
  static DipintoType fromStringToEnum(const QString &);
  // Getter
  QString getDipintoTypeString() const;
  // Setter
  void setDipintoType(DipintoType);
};

#endif // DIPINTO_H
