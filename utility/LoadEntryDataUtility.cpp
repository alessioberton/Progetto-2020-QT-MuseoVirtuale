#include "utility/LoadEntryDataUtility.h"
#include <fstream>
#include <QFile>
#include "model/Model.h"
#include "schema/Dipinto.h"
#include "schema/Quadro.h"
#include "schema/Scultura.h"
#include "schema/Mosaico.h"

void LoaDdataEntryUtility::retrieveStartData(Model& model) {
  QFile inputFile(":/data/data.json");
  if (inputFile.open(QIODevice::ReadOnly)) {
    QByteArray dataArray = inputFile.readAll();
    inputFile.close();
    QJsonDocument docJson = QJsonDocument::fromJson(dataArray);
    auto arrayJson = docJson.array();
    foreach (const QJsonValue& value, arrayJson) {
      QJsonObject obj = value.toObject();
      if (obj.contains("category") && obj["category"].isString()) {
	QString charClass = obj["category"].toString();
	DeepPtr<Opera> opera;
	if (charClass == "Scultura") opera = new Scultura();
	else if (charClass == "Quadro") opera = new Quadro();
	else if (charClass == "Mosaico") opera = new Mosaico();
	else if (charClass == "Dipinto") opera = new Dipinto();
	opera->deserialize(obj);
	model.insertOpera(opera->clone());
      }
    }
  }
}
