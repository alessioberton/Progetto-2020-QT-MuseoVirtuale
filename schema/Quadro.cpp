#include "Quadro.h"

Quadro::Quadro(const QString &_imgPath, const QString &_name, const QString &_author,  u_int _heigth, u_int _width, const QDateTime &_creationDate, const QDateTime &_expositionDate, DipintoType _dipintoType ,QuadroMaterial _quadroMaterial)
  : Dipinto(_imgPath, _name, _author, _heigth, _width, _creationDate, _expositionDate, _dipintoType), quadroMaterial(_quadroMaterial) {
  setPrice(Quadro::calcuateRealPrice());
}

Quadro *Quadro::clone() const { return new Quadro(*this); }

QString Quadro::getCategory() const { return "Quadro"; }

bool Quadro::hasValue() const {
  const bool value = Dipinto::hasValue();
  QString qm = getQuadroMaterialString();
  return value && (qm == "Oro" || qm == "Ceramica" || qm == "Rame");
}

double Quadro::calcuateRealPrice() const {
    double realPrice = Dipinto::calcuateRealPrice();
    const QString tipoQuadro = getQuadroMaterialString();
    if (tipoQuadro == "Metallo") realPrice += 1234.5;
    if (tipoQuadro == "Ceramica") realPrice += 4321.5;
    if (tipoQuadro == "Legno") realPrice += 1111.5;
    if (tipoQuadro == "Rame") realPrice += 5555.5;
    if (tipoQuadro == "Oro") realPrice += 7777.5;
    if (tipoQuadro == "Argento") realPrice += 4777.5;
    return realPrice;
}

QuadroMaterial Quadro::fromStringToEnum(const QString &typeString) {
  if (typeString == "Legno") {
    return QuadroMaterial(legno);
  }
  if (typeString == "Oro") {
    return QuadroMaterial(oro);
  }
  if (typeString == "Ceramica") {
    return QuadroMaterial(ceramica);
  }
  if (typeString == "Rame") {
    return QuadroMaterial(rame);
  }
  if (typeString == "Metallo") {
    return QuadroMaterial(metallo);
  }
  if (typeString == "Argento") {
    return QuadroMaterial(argento);
  }
  return QuadroMaterial(legno);
}

QString Quadro::getQuadroMaterialString() const {
  QString quadroMaterialString = "Non specificato";
  switch (quadroMaterial) {
  case ceramica:
    quadroMaterialString = "Ceramica";
    break;
  case legno:
    quadroMaterialString = "Legno";
    break;
  case rame:
    quadroMaterialString = "Rame";
    break;
  case oro:
    quadroMaterialString = "Oro";
    break;
  case metallo:
    quadroMaterialString = "Metallo";
    break;
  case argento:
    quadroMaterialString = "Argento";
    break;
  }
  return quadroMaterialString;
}

void Quadro::setQuadroMaterial(QuadroMaterial newQuadroMaterial) { quadroMaterial = newQuadroMaterial; }

QJsonObject Quadro::serialize() const {
  QJsonObject quadroJson = Dipinto::serialize();
  quadroJson["quadroMaterial"] = getQuadroMaterialString();
  return quadroJson;
}

void Quadro::deserialize(const QJsonObject& obj) {
    Dipinto::deserialize(obj);
    if (obj.contains("quadroMaterial") && obj["quadroMaterial"].isString())
	setQuadroMaterial(fromStringToEnum(obj["quadroMaterial"].toString()));
    setPrice(calcuateRealPrice());

}
