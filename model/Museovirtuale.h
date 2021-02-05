#ifndef MUSEOVIRTUALE_H
#define MUSEOVIRTUALE_H

#include <QString>
#include <QWidget>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QPushButton>
#include <QIcon>
#include <QFile>
#include <QDialog>
#include <QLabel>
#include <QProgressBar>
#include <QMessageBox>
#include <QToolButton>
#include <QTextStream>
#include <QFileDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIcon>
#include <QToolBar>
#include <QAction>
#include <QPixmap>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QScrollArea>
#include <QListWidget>
#include <QListWidgetItem>
#include <QFormLayout>
#include <QTextEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTimeEdit>


#include <QSignalMapper>

#include "schema/Opera.h"
#include "utility/Container.h"
#include "utility/DeepPtr.h"

using namespace std;

class Controller;

class MuseoVirtuale : public QMainWindow {  Q_OBJECT
private:
  Container<DeepPtr<Opera>> listOperaContainer;
  QLabel* operaLabel;
  Controller* controller;
  QMenuBar* menuBar;
  QFormLayout* authorInfoLayout;
  QFormLayout* operaInfoLayout;
  QFormLayout* galleryInfoLayout;
  QVBoxLayout* appLayout;
  QVBoxLayout* mainLayout;
  QHBoxLayout* toolbarLayout;
  QHBoxLayout* topLayout;
  QVBoxLayout* topRightLayout;
  QListWidget* operaList;
  QPixmap operaImg;
  QScrollArea* operaBox;
  QVBoxLayout* midLayout;
  QHBoxLayout* midInfoLayout;
  QWidget* midInfoWidget;
  QVBoxLayout* bottomLayout;
  QHBoxLayout* bottomRigthLayout;
  QLineEdit* searchBox;
  QComboBox* typeBox;
  QComboBox* showBox;
  QHBoxLayout* operaImageLayout;
  // Metodi Non costanti
  void addMenu();
  void createTopLayout(); // FOTO - LISTA OPERE - ADD - MODIFICA - DELETE
  void buildMidLayout(const QString& = ""); // DESCRIZIONE
  void createBottomLayout(); // RICERCA -- CATEGORIA -- RESET
  void changeListener();
  void buildList(const QString&, const QString&, bool);
  void showList(const QString&, bool, Container<DeepPtr<Opera>>);
  void updateList(const QString&, bool, Container<DeepPtr<Opera>>);
  void rebuildAfterSearch(Opera*, bool&, bool);
  void updateMidLayout(QHBoxLayout*, Opera*);
  void insertImg(Opera*);
  // Metodi costanti
  void resetLayout(QLayout*) const;
  void inserisciDescrizioneOpera(Opera*) const;
  void updateForm() const;
  QFrame* createLine() const;
  void resetNameList() const;
  void deleteList(const QString&) const;
  void buildTextList(const QString&, const QString&, bool) const;
  QDialog* buildDialog() const;
public slots:
  void resetFilters() const;
  void showInfoMsg() const;
public:
  MuseoVirtuale(Controller* controller, QWidget *parent = nullptr);
  ~MuseoVirtuale() = default;
  void showErrorMessage(const QString&) const;
  void updateEntireView();
  void setController(Controller*);
};
#endif // MUSEOVIRTUALE_H
