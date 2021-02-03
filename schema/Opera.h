#ifndef OPERA_H
#define OPERA_H

#include "QDateTime"
#include "QString"
#include "EnumCollection.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <string>


typedef unsigned int u_int;
using namespace EnumCollection;

class Opera {
private:
  QString name;
  QString imgPath;
  QString author;
  u_int height;
  u_int width;
  double price;
  QDateTime creationDate;
  QDateTime expositionDate;
public:
  // Parlanti
  Opera() = default;
  Opera(const QString &, const QString &, const QString &, u_int, u_int, const QDateTime &, const QDateTime &);
  virtual ~Opera() = default;
  virtual Opera *clone() const = 0;
  // Ritorna il nome della classe
  virtual QString getCategory() const = 0;
  // Opera ha valore se Dipinto fatta di olio/cera/pastelli o Scultura in marmo/terracotta/pietra/avorio
  virtual bool hasValue() const = 0;
  // il prezzo dell' Opera dipende dal valore, se è in vendita, dal suo materiale, dalle dimensioni
  virtual double calcuateRealPrice() const;
  virtual QJsonObject serialize() const;
  virtual void deserialize(const QJsonObject&);
  // Opera è in vendita se importante o realizzata negli utimi 10 anni
  bool isOnSale() const;
  bool operator==(const Opera&) const;
  // Getter
  QString getImgPath() const;
  QString getName() const;
  QString getAuthor() const;
  QDateTime getCreationDate() const;
  QDateTime getExpositionDate() const;
  u_int getHeight() const;
  u_int getWidth() const;
  double getPrice() const;
  // Setter
  void setImgPath(const QString&);
  void setName(const QString&);
  void setAuthor(const QString&);
  void SetCreationDate(const QDateTime&);
  void setExpositionDate(const QDateTime&);
  void setHeight(u_int);
  void setWidth(u_int);
  void setPrice(double);
};

#endif // OPERA_H
