#include "Model.h"

Model::Model() {  }

Model::~Model() { }

Container<DeepPtr<Opera>> Model::getOperaContainer() const { return operaContainer; }

void Model::clearOperaContainer() { operaContainer.clear(); }

void Model::insertOpera(Opera* newOpera) { operaContainer.insert(newOpera); }

void Model::deleteOpera(Opera* oldOpera) { operaContainer.remove(oldOpera); }

void Model::choseOpera(const QString & type, const QString & name, Container<DeepPtr<Opera>> & opere) const {
  if (name == "") {

//    for( auto const& l : operaContainer ) {
//      // do something with l
//    }


    for (int i = 0; i < operaContainer.getSize(); i++){
      if (operaContainer[i]->clone()->getCategory() == type){
	opere.insert(operaContainer[i]);
      }
    }
  } else {
    for (int i = 0; i < operaContainer.getSize(); i++){
      if (operaContainer[i]->clone()->getCategory() == type &&
	  operaContainer[i]->clone()->getName().toLower().startsWith(name.toLower())){
	opere.insert(operaContainer[i]);
      }
    }
  }
}

Container<DeepPtr<Opera>> Model::getOperaByTypeAndName(const QString &type, const QString &name) const {
  auto opere = Container<DeepPtr<Opera>>();
  if (type == ""  && name == "") return opere;
  if (type == "Tutte"  && name == "") return getOperaContainer();
  if (type == "Tutte"  && name != "") {
    for (int i = 0; i < operaContainer.getSize(); i++){
      if (operaContainer[i]->clone()->getName().toLower().startsWith(name.toLower())){
	opere.insert(operaContainer[i]);
      }
    }
  } else choseOpera(type, name, opere);
  return opere;
}

unsigned int Model::getCountSameAuthor(const QString &author) const {
  unsigned int value = 0;
  for (int i = 0; i < operaContainer.getSize(); i++){
    if (operaContainer[i]->getAuthor() == author) value++;
  }
  return value;
}

DeepPtr<Opera> Model::searchOpera(int index) const { return operaContainer[index]; }
