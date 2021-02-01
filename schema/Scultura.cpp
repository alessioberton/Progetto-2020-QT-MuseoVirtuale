#include "Scultura.h"

Scultura::Scultura(const QString &_imgPath, const QString &_name, const QString &_author,  u_int _heigth, u_int _width, const QDateTime &_creationDate, const QDateTime &_expositionDate, SculturaMaterial _sculturaMaterial)
    : Opera(_imgPath, _name, _author, _heigth, _width, _creationDate, _expositionDate), sculturaMaterial(_sculturaMaterial) {
  setPrice(Scultura::calcuateRealPrice());
}

Scultura *Scultura::clone() const { return new Scultura(*this); }

QString Scultura::getCategory() const { return "Scultura"; }

bool Scultura::hasValue() const {
  const QString st = getSculturaMaterialString();
  return st == "Marmo" || st == "Terracotta" || st == "Pietra" || st == "Avorio";
}

double Scultura::calcuateRealPrice() const {
    double realPrice = Opera::calcuateRealPrice();
    const double volumeSculturaSpannometrica = ((getHeight()/100) * (getWidth()/100) * 3);
    const QString tipoScultura = getSculturaMaterialString();
    if (tipoScultura == "Marmo") realPrice += 2.5 * volumeSculturaSpannometrica;
    if (tipoScultura == "Pietra") realPrice += 1.8 * volumeSculturaSpannometrica;
    if (tipoScultura == "Terracotta") realPrice += 2.2 * volumeSculturaSpannometrica;
    if (tipoScultura == "Avorio") realPrice += 1.5 * volumeSculturaSpannometrica;
    if (tipoScultura == "Argilla") realPrice += 1.2 * volumeSculturaSpannometrica;
    return realPrice;
}

SculturaMaterial Scultura::fromStringToEnum(const QString &typeString) {
  if (typeString == "Marmo") {
    return SculturaMaterial(marmo);
  }
  if (typeString == "Pietra") {
    return SculturaMaterial(pietra);
  }
  if (typeString == "Terracotta") {
    return SculturaMaterial(terracotta);
  }
  if (typeString == "Avorio") {
    return SculturaMaterial(avorio);
  }
  if (typeString == "Argilla") {
    return SculturaMaterial(argilla);
  }
  return SculturaMaterial(marmo);
}

QString Scultura::getSculturaMaterialString() const {
  QString sculturaMaterialQString = "Non specificato";
  switch (sculturaMaterial) {
  case marmo:
    sculturaMaterialQString = "Marmo";
    break;
  case pietra:
    sculturaMaterialQString = "Pietra";
    break;
  case terracotta:
    sculturaMaterialQString = "Terracotta";
    break;
  case avorio:
    sculturaMaterialQString = "Avorio";
    break;
  case argilla:
    sculturaMaterialQString = "Argilla";
    break;
  }
  return sculturaMaterialQString;
}

void Scultura::setSculturaMaterial(SculturaMaterial newSculturaMaterial) { sculturaMaterial = newSculturaMaterial; }

QJsonObject Scultura::serialize() const {
  QJsonObject sculturaJson = Opera::serialize();
  sculturaJson["sculturaMaterial"] = getSculturaMaterialString();
  return sculturaJson;
}

void Scultura::deserialize(const QJsonObject& obj) {
    Opera::deserialize(obj);
    if (obj.contains("sculturaMaterial") && obj["sculturaMaterial"].isString())
	setSculturaMaterial(fromStringToEnum(obj["sculturaMaterial"].toString()));
    setPrice(calcuateRealPrice());
}

