#include "Model.h"

Model::~Model() { }

void Model::clearOperaContainer() { operaContainer.clear(); }

void Model::insertOpera(Opera* newOpera) { operaContainer.insert(newOpera); }

void Model::deleteOpera(int indexOldOpera) { operaContainer.remove(indexOldOpera); }

Container<DeepPtr<Opera>> Model::getOperaContainer() const { return operaContainer; }

void Model::choseOpera(const QString& type, const QString& name, bool isOnSale, Container<DeepPtr<Opera>>& opere) const {
  if (name == "") {
    for (int i = 0; i < operaContainer.getSize(); i++) {
      if (operaContainer[i]->getCategory() == type) {
	if (!isOnSale) opere.insert(operaContainer[i]);
	else if (isOnSale == operaContainer[i]->isOnSale()) opere.insert(operaContainer[i]);
      }
    }
  } else {
    for (int i = 0; i < operaContainer.getSize(); i++) {
      if (operaContainer[i]->getCategory() == type &&
	  operaContainer[i]->getName().toLower().startsWith(name.toLower())){
	if (!isOnSale) opere.insert(operaContainer[i]);
	else if (isOnSale == operaContainer[i]->isOnSale()) opere.insert(operaContainer[i]);
      }
    }
  }
}

Container<DeepPtr<Opera>> Model::getOperaByTypeAndName(const QString& type, const QString& name, bool isOnSale) const {
  auto opere = Container<DeepPtr<Opera>>();
  if (type == ""  && name == "") return opere;
  if (type == "Tutte"  && name == "") return getOperaContainer();
  if (type == "Tutte"  && name != "") {
    for (int i = 0; i < operaContainer.getSize(); i++) {
      if (operaContainer[i]->getName().toLower().startsWith(name.toLower())) {
	if (!isOnSale) opere.insert(operaContainer[i]);
	else if (isOnSale == operaContainer[i]->isOnSale()) opere.insert(operaContainer[i]);
      }
    }
  } else choseOpera(type, name, isOnSale, opere);
  return opere;
}

unsigned int Model::getCountSameAuthor(const QString& author) const {
  unsigned int value = 0;
  for (int i = 0; i < operaContainer.getSize(); i++) if (operaContainer[i]->getAuthor() == author) value++;
  return value;
}

int Model::searchOperaGivenName(const QString& opName) const {
  bool found = false;
  int i = 0;
  while (i < operaContainer.getSize() && !found){
     if (operaContainer[i]->getName() == opName) found = !found;
     else i++;
  }
  return i;
}

DeepPtr<Opera> Model::searchOpera(int index) const { return operaContainer[index]; }
