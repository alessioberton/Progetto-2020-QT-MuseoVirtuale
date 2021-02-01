#include "Mosaico.h"

Mosaico::Mosaico(const QString &_imgPath, const QString &_name, const QString &_author, u_int _heigth, u_int _width, const QDateTime &_creationDate, const QDateTime &_expositionDate, MosaicoMaterial _mosaicoMaterial)
    : Opera(_imgPath, _name, _author, _heigth, _width,  _creationDate, _expositionDate), mosaicoMaterial(_mosaicoMaterial) {
  setPrice(Mosaico::calcuateRealPrice());
}

Mosaico *Mosaico::clone() const { return new Mosaico(*this); }

QString Mosaico::getCategory() const { return "Mosaico"; }

bool Mosaico::hasValue() const {
  const QString mm = getMosaicoMaterialString();
  return mm == "Argento" || mm == "Pietra" || mm == "Marmo" || mm == "Vetro";
}

double Mosaico::calcuateRealPrice() const {
  double realPrice = Opera::calcuateRealPrice();
  const int areaMosaico = getHeight() * getWidth();
  const QString tipoMosaico = getMosaicoMaterialString();
  if (tipoMosaico == "Oro") realPrice += 1.7 * areaMosaico;
  if (tipoMosaico == "Argento") realPrice += 2.1 * areaMosaico;
  if (tipoMosaico == "Marmo") realPrice += 2.5 * areaMosaico;
  if (tipoMosaico == "Pietra") realPrice += 2.8 * areaMosaico;
  if (tipoMosaico == "Vetro") realPrice += 3.1 * areaMosaico;
  if (tipoMosaico == "conchiglia") realPrice += 1.3 * areaMosaico;
  return realPrice;
}

Mosaico::MosaicoMaterial Mosaico::fromStringToEnum(const QString &typeString) {
  if (typeString == "Oro") {
    return MosaicoMaterial(oro);
  }
  if (typeString == "Argento") {
    return MosaicoMaterial(argento);
  }
  if (typeString == "Marmo") {
    return MosaicoMaterial(marmo);
  }
  if (typeString == "Pietra") {
    return MosaicoMaterial(pietra);
  }
  if (typeString == "Vetro") {
    return MosaicoMaterial(vetro);
  }
  if (typeString == "conchiglia") {
    return MosaicoMaterial(conchiglia);
  }
  return MosaicoMaterial(oro);
}

QString Mosaico::getMosaicoMaterialString() const {
  QString mosaicoMaterialQString = "Non specificato";
  switch (mosaicoMaterial) {
  case oro:
    mosaicoMaterialQString = "Oro";
    break;
  case argento:
    mosaicoMaterialQString = "Argento";
    break;
  case marmo:
    mosaicoMaterialQString = "Marmo";
    break;
  case pietra:
    mosaicoMaterialQString = "Pietra";
    break;
   case vetro:
    mosaicoMaterialQString = "Vetro";
    break;
   case conchiglia:
    mosaicoMaterialQString = "Conchiglia";
    break;
  }
  return mosaicoMaterialQString;
}

void Mosaico::setMosaicoMaterial(MosaicoMaterial newMosaicoMaterial) { mosaicoMaterial = newMosaicoMaterial; }

QJsonObject Mosaico::serialize() const {
  QJsonObject mosaicoJson = Opera::serialize();
  mosaicoJson["mosaicoMaterial"] = getMosaicoMaterialString();
  return mosaicoJson;
}

void Mosaico::deserialize(const QJsonObject& obj) {
    Opera::deserialize(obj);
    if (obj.contains("mosaicoMaterial") && obj["mosaicoMaterial"].isString())
	setMosaicoMaterial(fromStringToEnum(obj["mosaicoMaterial"].toString()));
    setPrice(calcuateRealPrice());
}

