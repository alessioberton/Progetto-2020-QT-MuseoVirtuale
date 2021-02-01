#include "Opera.h"

Opera::Opera(const QString &_imgPath, const QString &_name, const QString &_author,u_int _height, u_int _width, const QDateTime & _creationDate, const QDateTime & _expositionDate) : imgPath(_imgPath),
  name(_name) , author(_author), height(_height), width(_width), price(0.0),
  creationDate(_creationDate), expositionDate(_expositionDate) {}

double Opera::calcuateRealPrice() const {
  double realPrice = 0.0;
  bool bonus = false;
  if (hasValue()) {realPrice += 4300.7; bonus = true; }
  if (isOnSale()) realPrice += 5700.3;
  if(!bonus){
    realPrice += 1550.5;
  }
  return realPrice;
}

bool Opera::isOnSale() const {
  const auto creationSculturaPlusTen = getCreationDate().addYears(10).toTime_t();
  const auto currentaDate = QDateTime::currentDateTimeUtc().toTime_t();
  return creationSculturaPlusTen >= currentaDate || hasValue();
}

QString Opera::getImgPath() const { return imgPath; }

QString Opera::getName() const { return name; }

QString Opera::getAuthor() const { return author;}

QDateTime Opera::getCreationDate() const { return creationDate; }

QDateTime Opera::getExpositionDate() const { return expositionDate ;}

u_int Opera::getHeight() const { return height; }

u_int Opera::getWidth() const { return width; }

double Opera::getPrice() const { return price; }

void Opera::setImgPath(const QString &newImgPath) { imgPath = newImgPath; }

void Opera::setName(const QString &newName) { name = newName; }

void Opera::setAuthor(const QString & newAuthor) { author = newAuthor; }

void Opera::SetCreationDate(const QDateTime &newCreationDate) { creationDate = newCreationDate; }

void Opera::setExpositionDate(const QDateTime &newExpositionDate) { expositionDate = newExpositionDate; }

void Opera::setHeight(u_int newHeight){ height = newHeight; }

void Opera::setWidth(u_int newWidth){ width = newWidth; }

void Opera::setPrice(double newPrice) { price = newPrice; }

bool Opera::operator==(const Opera& opera) const { return author == opera.author && name == opera.name; }

QJsonObject Opera::serialize() const {
    QJsonObject charJson;
    QString format = "dd/MM/yyyy";
//    QLocale locale = {QLocale(QLocale::Italian)};
//    galleryInfoLayout->addRow("Data prima esposizione: ", new QLabel(locale.toString(quadro->getExpositionDate(), format)));

    charJson["imgPath"] = getImgPath();
    charJson["author"] = getAuthor();
    charJson["category"] = getCategory();
    charJson["creationDate"] = getCreationDate().toString(format);
    charJson["expositionDate"] = getExpositionDate().toString(format);
    charJson["height"] = static_cast<int>(getHeight());
    charJson["name"] = getName();
    charJson["price"] = getPrice();
    charJson["onSale"] = isOnSale() ? "SI" : "NO";
    charJson["width"] = static_cast<int>(getWidth());
    return charJson;
}

void Opera::deserialize(const QJsonObject& obj) {
    if (obj.contains("imgPath") && obj["imgPath"].isString())
	setImgPath(obj["imgPath"].toString());
    if (obj.contains("name") && obj["name"].isString())
	setName(obj["name"].toString());
    if (obj.contains("author") && obj["author"].isString())
	setAuthor(obj["author"].toString());
    if (obj.contains("height"))
	setHeight(obj["height"].toInt());
    if (obj.contains("width"))
	setWidth(obj["width"].toInt());
    if (obj.contains("creationDate") && obj["creationDate"].isString())
	SetCreationDate(QDateTime::fromString(obj["creationDate"].toString(),"dd/MM/yyyy"));
    if (obj.contains("expositionDate") && obj["expositionDate"].isString())
	setExpositionDate(QDateTime::fromString(obj["expositionDate"].toString(),"dd/MM/yyyy"));
}
