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
#include <QStackedWidget>
#include <QFormLayout>
#include <QTextEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTimeEdit>

#include "schema/Opera.h"
#include "utility/Container.h"
#include "utility/DeepPtr.h"


#include "iostream"
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






  // Layouts
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
  QStackedWidget* stackedWidget;


  QVBoxLayout* bottomLayout;
  QHBoxLayout* bottomRigthLayout;


  // Components
  QLineEdit* searchBox;
  QComboBox* typeBox;
  QComboBox* showBox;

  QHBoxLayout* operaImageLayout;

  // Metodi di build-style-errore GUI
  void addMenu();
  void createTopLayout(); // FOTO - LISTA OPERE - ADD - MODIFICA - DELETE
  void buildOperaLayout(const QString& = ""); // DESCRIZIONE
  void createBottomLayout(); // RICERCA -- CATEGORIA -- RESET
  void clearLayout(QLayout*);
  void updateList(const QString& typeOpera, bool, Container<DeepPtr<Opera>>);

  void inserisciDescrizioneOpera(Opera*);
  void updateForm();
  QFrame* createLine();
  void reBuildLayout();
  void resetNameList();

  void searchList(const QString&);
  void showList(const QString&, bool, Container<DeepPtr<Opera>>);
  void sortList(const QString&);
  void buildList(const QString&, const QString&, bool);
  void buildTextList(const QString&, const QString&, bool);
  void insertImg(Opera*);

  void rebuildAfterSearch(Opera*, bool&, bool);

public slots:
  void resetFilters();
  void showInfoMsg() const;

public:
  MuseoVirtuale(Controller* controller, QWidget *parent = nullptr);
  ~MuseoVirtuale() = default;
  //Metodi di utilita'
  void showErrorMessage(const QString& message);
  // Rebuild della GUI - Associa vista al controller
  void updateEntireView();
  void setController(Controller *);
};
#endif // MUSEOVIRTUALE_H
