#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "model/Model.h"
#include "model/Museovirtuale.h"
#include "schema/Opera.h"
#include "schema/Dipinto.h"
#include "schema/Quadro.h"
#include "schema/Scultura.h"
#include "schema/Mosaico.h"
#include <QJsonDocument>


class Controller : public QObject { Q_OBJECT

private:
  MuseoVirtuale* view;
  Model* model;
public:
  explicit Controller(Model* model, QObject *parent = nullptr);
  ~Controller();
  void setModel(Model*);
  void setView(MuseoVirtuale* v);
  Container<DeepPtr<Opera>> getOperaContainer();

public slots:
  void saveData();
  void loadData();

  unsigned int countSameAuthor(const QString&);

  DeepPtr<Opera> searchClicked(int);
  Container<DeepPtr<Opera>> searchByTpeAndName(const QString& = "", const QString& = "");


  // Codice pronto in caso l'applicazione permetta di cancellare/modificare/salvare opere. Avrei sforato le 50 ore implementando e	  testando queste funzioni su GUI
  void deleteBtnClicked(Opera*);
  void modifyBtnClicked(Opera*, Opera*);
  void saveBtnClicked(Opera*);
};

#endif  // CONTROLLER_H
