#include "Dipinto.h"

Dipinto::Dipinto(const QString &_imgPath, const QString &_name, const QString &_author, u_int _heigth, u_int _width, const QDateTime &_creationDate,
		 const QDateTime &_expositionDate, DipintoType _dipintoType)
    : Opera(_imgPath, _name, _author, _heigth, _width,  _creationDate, _expositionDate), dipintoType(_dipintoType) {
  setPrice(Dipinto::calcuateRealPrice());
}

Dipinto *Dipinto::clone() const { return new Dipinto(*this); }

QString Dipinto::getCategory() const { return "Dipinto"; }

bool Dipinto::hasValue() const {
  const QString pt = getDipintoTypeString();
  return pt == "Olio" || pt == "Cera" || pt == "Pastelli";
}

double Dipinto::calcuateRealPrice() const {
  double realPrice = Opera::calcuateRealPrice();
  const int areaDipinto = getHeight() * getWidth();
  const QString tipoPittura = getDipintoTypeString();
  if (tipoPittura == "Olio") realPrice += 1.3 * areaDipinto;
  if (tipoPittura == "Acquerelli") realPrice += 1.1 * areaDipinto;
  if (tipoPittura == "Pastelli") realPrice += 1.5 * areaDipinto;
  if (tipoPittura == "Cera") realPrice += 1.8 * areaDipinto;
  return realPrice;
}

DipintoType Dipinto::fromStringToEnum(const QString &typeString) {
  if (typeString == "Olio") {
    return DipintoType(olio);
  }
  if (typeString == "Acquerelli") {
    return DipintoType(acquerelli);
  }
  if (typeString == "Pastelli") {
    return DipintoType(pastelli);
  }
  if (typeString == "Cera") {
    return DipintoType(cera);
  }
  return DipintoType(olio);
}

QString Dipinto::getDipintoTypeString() const {
  QString dipintoTypeQString = "Non specificato";
  switch (dipintoType) {
  case olio:
    dipintoTypeQString = "Olio";
    break;
  case acquerelli:
    dipintoTypeQString = "Acquerelli";
    break;
  case pastelli:
    dipintoTypeQString = "Pastelli";
    break;
  case cera:
    dipintoTypeQString = "Cera";
    break;
  }
  return dipintoTypeQString;
}

void Dipinto::setDipintoType(DipintoType newDipintoType) { dipintoType = newDipintoType; }

QJsonObject Dipinto::serialize() const {
  QJsonObject dipintoJson = Opera::serialize();
  dipintoJson["dipintoType"] = getDipintoTypeString();
  return dipintoJson;
}

void Dipinto::deserialize(const QJsonObject& obj) {
    Opera::deserialize(obj);
    if (obj.contains("dipintoType") && obj["dipintoType"].isString())
	setDipintoType(fromStringToEnum(obj["dipintoType"].toString()));
    if (getCategory() == "Dipinto")
    setPrice(calcuateRealPrice());
}
