#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "model/Model.h"
#include "model/GalleriaVirtuale.h"
#include "schema/Opera.h"
#include "schema/Dipinto.h"
#include "schema/Quadro.h"
#include "schema/Scultura.h"
#include "schema/Mosaico.h"
#include <QJsonDocument>

class Controller : public QObject { Q_OBJECT

private:
  GalleriaVirtuale* view;
  Model* model;
public:
  explicit Controller(Model* model, QObject *parent = nullptr);
  ~Controller();
  void setModel(Model*);
  void setView(GalleriaVirtuale*);
  Container<DeepPtr<Opera>> getOperaContainer() const;
  unsigned int countSameAuthor(const QString&) const;
  DeepPtr<Opera> searchClicked(int) const;
  Container<DeepPtr<Opera>> searchByTpeNameSale(const QString& = "", const QString& = "", bool = false) const;
  int findOperaGivenName(const QString&) const;
public slots:
  void saveData() const;
  void loadData() const;
  void deleteBtnClicked(int) const;
  // Codice "pronto" in caso l'applicazione permetta di salvare opere. Avrei sforato sicuramente le 50 ore implementando e testando questa funzione
  void saveBtnClicked(Opera*) const;
};

#endif  // CONTROLLER_H
