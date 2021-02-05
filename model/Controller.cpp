#include "Controller.h"

Controller::Controller(Model* m, QObject* parent) : QObject(parent), view(nullptr), model(m) {}

Controller::~Controller() {}

void Controller::setModel(Model *m) { model = m; }

void Controller::setView(GalleriaVirtuale* v) { view = v; view->setController(this); }

Container<DeepPtr<Opera>> Controller::getOperaContainer() const { return model->getOperaContainer(); }

void Controller::saveData() const {
  const auto operaList = model->getOperaContainer();
  if (!operaList.isEmpty()) {
      QString fileName = QFileDialog::getSaveFileName(view, tr("Save container"), "/data", tr("JSON files (*.json)"));
      if (!fileName.endsWith(".json")) fileName.append(".json");
      QJsonArray arrayJson;
      for (int i = 0; i < operaList.getSize(); ++i) arrayJson.push_back(QJsonValue(operaList[i]->serialize()));
      const QJsonDocument docJson(arrayJson);
      const QString docString = docJson.toJson();
      QFile saveFile(fileName);
      saveFile.open(QIODevice::WriteOnly);
      saveFile.write(docString.toUtf8());
      saveFile.close();
  } else view->showErrorMessage("Nessun dato da salvare");
}

void Controller::loadData() const {
  QString fileName = QFileDialog::getOpenFileName(view, tr("Carica dati json per continuare"), "/data",
						  tr("JSON files (*.json)"));
  if (!fileName.isEmpty()) {
    if (!fileName.endsWith(".json")) view->showErrorMessage("Dati non validi");
    else {
      QFile loadFile(fileName);
      loadFile.open(QIODevice::ReadOnly);
      const QByteArray dataArray = loadFile.readAll();
      loadFile.close();
      const QJsonDocument docJson = QJsonDocument::fromJson(dataArray);
      const auto arrayJson = docJson.array();
      if (arrayJson.isEmpty()) {  view->showErrorMessage("file json vuoto o incorretto"); }
      else {
	if (model->getOperaContainer().getSize() != 0) model->clearOperaContainer();
	foreach (const QJsonValue& value, arrayJson) {
	  const QJsonObject obj = value.toObject();
	  if (obj.contains("category") && obj["category"].isString()) {
	    const QString charClass = obj["category"].toString();
	    DeepPtr<Opera> opera;
	    if (charClass == "Scultura") opera = new Scultura();
	    else if (charClass == "Quadro") opera = new Quadro();
	    else if (charClass == "Mosaico") opera = new Mosaico();
	    else if (charClass == "Dipinto") opera = new Dipinto();
	    opera->deserialize(obj);
	    model->insertOpera(opera->clone());
	  }
	}
	view->updateEntireView();
      }
    }
  }
}

unsigned int Controller::countSameAuthor(const QString & author) const { return model->getCountSameAuthor(author); }

DeepPtr<Opera> Controller::searchClicked(int index) const { return model->searchOpera(index); }

Container<DeepPtr<Opera>> Controller::searchByTpeNameSale(const QString& type, const QString& name, bool isOnSale) const { return model->getOperaByTypeAndName(type, name, isOnSale); }

int Controller::findOperaGivenName(const QString& opName) const { return model->searchOperaGivenName(opName); }

void Controller::saveBtnClicked(Opera* newOpera) const { model->insertOpera(newOpera); }

void Controller::deleteBtnClicked(int indexOpera) const {
  model->deleteOpera(indexOpera);
  view->updateEntireView();
}
