#include "Museovirtuale.h"
#include "Controller.h"

void MuseoVirtuale::showInfoMsg() const {
  QDialog* dialog = new QDialog();
  dialog->setWindowTitle("Galleria virtuale");
  QVBoxLayout* layout = new QVBoxLayout(dialog);

  dialog->resize(260, 200);
  // Blocco dal resize odioso dell' utente con ben 8 righe di codice purtroppo
  QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(dialog->sizePolicy().hasHeightForWidth());
  dialog->setSizePolicy(sizePolicy);
  dialog->setMinimumSize(QSize(260, 200));
  dialog->setMaximumSize(QSize(260, 200));
  dialog->setSizeGripEnabled(false);

  dialog->setAttribute(Qt::WA_DeleteOnClose); // Evito memory leak

  // Inserisco il messaggio nella finestra con QLabel
  layout->addWidget(new QLabel("Mostra virtuale di opere d'arte", dialog), 0, Qt::AlignCenter);
  layout->addWidget(new QLabel("Versione: 1.0.0", dialog),0,  Qt::AlignCenter);
  layout->addWidget(new QLabel("Dev: Alessio Berton", dialog), 0, Qt::AlignCenter);
  layout->addWidget(new QLabel("Mail: alessio.berton@studenti.it", dialog), 0, Qt::AlignCenter);

  // Mostrare la finestra
  dialog->exec(); //Blocco il widget
}

void MuseoVirtuale::createTopLayout() {

  topLayout = new QHBoxLayout;
  topRightLayout = new QVBoxLayout;

  midInfoLayout = new QHBoxLayout;
  midInfoWidget = new QWidget;
  stackedWidget = new QStackedWidget;

  operaLabel = new QLabel;

  if (!listOperaContainer.isEmpty()) insertImg(listOperaContainer[0]->clone());

  operaImageLayout = new QHBoxLayout;
  operaImageLayout->addWidget(operaLabel);

  operaList = new QListWidget;

  // List box
  operaBox = new QScrollArea;
  operaBox->setWidget(operaList);
  operaBox->setWidgetResizable(true);
  operaBox->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  connect(operaList, &QListWidget::itemSelectionChanged, [this] {
      if (operaList->count() > 0) {
	int index = operaList->currentRow();
	clearLayout(midInfoLayout);
	buildOperaLayout(operaList->item(index)->text());
      }
      if (stackedWidget->isHidden()) stackedWidget->show();
	stackedWidget->setCurrentWidget(midInfoWidget);
  });

  topLayout->addLayout(operaImageLayout);
  topRightLayout->addWidget(operaBox);
  topLayout->addLayout(topRightLayout);
  mainLayout->addLayout(topLayout);
}

void MuseoVirtuale::buildOperaLayout(const QString& operaName) {
  authorInfoLayout = new QFormLayout;
  operaInfoLayout = new QFormLayout;
  galleryInfoLayout = new QFormLayout;

  listOperaContainer = controller->getOperaContainer();
  if (!listOperaContainer.isEmpty()) {
    if (operaName == "") { //SITUAZIONE INIZIALE
      inserisciDescrizioneOpera(listOperaContainer[0]->clone());
      updateForm();
      mainLayout->addLayout(midLayout);
    } else { // UPDATE FORM
      auto listaOpereByName = controller->searchByTpeAndName(typeBox->currentText(), operaName);
      bool continua = true;
      for (int i = 0; i < listaOpereByName.getSize() && continua ; i++ ) {
	if (listaOpereByName[i]->clone()->getName() == operaName) {
	  const auto opera = listaOpereByName[i]->clone();
	  inserisciDescrizioneOpera(opera);
	  operaImg.load(opera->getImgPath());
	  operaLabel->setPixmap(operaImg);
	  continua = !continua;
	}
      }
      operaImageLayout->update();
      updateForm();
      mainLayout->update();
    }
  } else {
    authorInfoLayout->addRow("Attenzione ", new QLabel("Nessuna opera in mostra"));
    updateForm();
    mainLayout->addLayout(midLayout);
  }
}

void MuseoVirtuale::updateForm(){
  midInfoLayout->addWidget(createLine());
  midInfoLayout->addLayout(operaInfoLayout);
  midInfoLayout->addLayout(authorInfoLayout);
  midInfoLayout->addLayout(galleryInfoLayout);
  // MAGIA
  midInfoLayout->addStretch();
  midInfoWidget->setLayout(midInfoLayout);
  stackedWidget->addWidget(midInfoWidget);
  midLayout->addWidget(stackedWidget);
}


void MuseoVirtuale::inserisciDescrizioneOpera(Opera* singleOpera){
  QString format = "dd MMMM yyyy";
  QLocale locale = {QLocale(QLocale::Italian)};
  QLabel * infoAuthor = new QLabel("Informazioni Autore");
  infoAuthor->setStyleSheet("font-weight: bold; color: black");
  QLabel * infoOpera = new QLabel();
  infoOpera->setStyleSheet("font-weight: bold; color: black");
  QLabel * infoMostra = new QLabel("Informazioni Galleria");
  infoMostra->setStyleSheet("font-weight: bold; color: black");
  const Quadro* quadro = dynamic_cast<Quadro*>(singleOpera->clone());
    if (quadro) {
	  infoOpera->setText("Informazioni Quadro");
	  operaInfoLayout->addRow(infoOpera);
	  operaInfoLayout->addRow("Nome Quadro: ", new QLabel(quadro->getName()));
	  operaInfoLayout->addRow("Altezza in centimetri: ", new QLabel(QString::number(1.0 * quadro->getHeight())));
	  operaInfoLayout->addRow("Larghezza in centimetri: ", new QLabel(QString::number(1.0 * quadro->getWidth())));
	  operaInfoLayout->addRow("Prezzo in euro: ", new QLabel(QString("%L1").arg(quadro->getPrice())));
	  operaInfoLayout->addRow(createLine());
	  operaInfoLayout->addRow("Tipo pittura: ", new QLabel(quadro->getDipintoTypeString()));
	  operaInfoLayout->addRow("Materiale cornice: ", new QLabel(quadro->getQuadroMaterialString()));
	  authorInfoLayout->setContentsMargins(100,0,0,0);
	  authorInfoLayout->addRow(infoAuthor);
	  authorInfoLayout->addRow("Nome Autore: ", new QLabel(quadro->getAuthor()));
	  authorInfoLayout->addRow("Opere esposte dall' autore: ", new QLabel(QString::number(controller->countSameAuthor(quadro->getAuthor()))));
	  galleryInfoLayout->setContentsMargins(100,0,0,0);
	  galleryInfoLayout->addRow(infoMostra);
	  galleryInfoLayout->addRow("Data creazione: ", new QLabel(locale.toString(quadro->getCreationDate(), format)));
	  galleryInfoLayout->addRow("Data prima esposizione: ", new QLabel(locale.toString(quadro->getExpositionDate(), format)));
	  galleryInfoLayout->addRow("Al momento in vendita in galleria: ", new QLabel(quadro->isOnSale() ? "SI" : "NO"));
    } else if (dynamic_cast<Scultura*>(singleOpera->clone())) {
      const Scultura* scultura = dynamic_cast<Scultura*>(singleOpera->clone());
      if (scultura) {
	infoOpera->setText("Informazioni Scultura");
	operaInfoLayout->addRow(infoOpera);
	operaInfoLayout->addRow("Nome Scultura: ", new QLabel(scultura->getName()));
	operaInfoLayout->addRow("Altezza in metri: ", new QLabel(QString::number(1.0 * scultura->getHeight()/100)));
	operaInfoLayout->addRow("Larghezza in metri: ", new QLabel(QString::number(1.0 * scultura->getWidth()/100)));
	operaInfoLayout->addRow("Prezzo in euro: ", new QLabel(QString("%L1").arg(scultura->getPrice())));
	operaInfoLayout->addRow(createLine());
	operaInfoLayout->addRow("Materiale utilizzato: ", new QLabel(scultura->getSculturaMaterialString()));
	authorInfoLayout->setContentsMargins(100,0,0,0);
	authorInfoLayout->addRow(infoAuthor);
	authorInfoLayout->addRow("Nome Autore: ", new QLabel(scultura->getAuthor()));
	authorInfoLayout->addRow("Opere esposte dall' autore: ", new QLabel(QString::number(controller->countSameAuthor(scultura->getAuthor()))));
	galleryInfoLayout->setContentsMargins(100,0,0,0);
	galleryInfoLayout->addRow(infoMostra);
	galleryInfoLayout->addRow("Data creazione: ", new QLabel(locale.toString(scultura->getCreationDate(), format)));
	galleryInfoLayout->addRow("Data prima esposizione: ", new QLabel(locale.toString(scultura->getExpositionDate(), format)));
	galleryInfoLayout->addRow("Al momento in vendita in galleria: ", new QLabel(scultura->isOnSale() ? "SI" : "NO"));
      }
    } else if (dynamic_cast<Mosaico*>(singleOpera->clone())) {
      const Mosaico* mosaico= dynamic_cast<Mosaico*>(singleOpera->clone());
      if (mosaico) {
	infoOpera->setText("Informazioni Mosaico");
	operaInfoLayout->addRow(infoOpera);
	operaInfoLayout->addRow("Nome mosaico: ", new QLabel(mosaico->getName()));
	operaInfoLayout->addRow("Altezza in centimetri: ", new QLabel(QString::number(1.0 * mosaico->getHeight())));
	operaInfoLayout->addRow("Larghezza in centimetri: ", new QLabel(QString::number(1.0 * mosaico->getWidth())));
	operaInfoLayout->addRow("Prezzo in euro: ", new QLabel(QString("%L1").arg(mosaico->getPrice())));
	operaInfoLayout->addRow(createLine());
	operaInfoLayout->addRow("Materiale utilizzato: ", new QLabel(mosaico->getMosaicoMaterialString()));
	authorInfoLayout->setContentsMargins(100,0,0,0);
	authorInfoLayout->addRow(infoAuthor);
	authorInfoLayout->addRow("Nome Autore: ", new QLabel(mosaico->getAuthor()));
	authorInfoLayout->addRow("Opere esposte dall' autore: ", new QLabel(QString::number(controller->countSameAuthor(mosaico->getAuthor()))));
	galleryInfoLayout->setContentsMargins(100,0,0,0);
	galleryInfoLayout->addRow(infoMostra);
	galleryInfoLayout->addRow("Data creazione: ", new QLabel(locale.toString(mosaico->getCreationDate(), format)));
	galleryInfoLayout->addRow("Data prima esposizione: ", new QLabel(locale.toString(mosaico->getExpositionDate(), format)));
	galleryInfoLayout->addRow("Al momento in vendita in galleria: ", new QLabel(mosaico->isOnSale() ? "SI" : "NO"));
    }
  } else if (dynamic_cast<Opera*>(singleOpera->clone())) {
      const Dipinto* dipinto= dynamic_cast<Dipinto*>(singleOpera->clone());
      if (dipinto) {
	infoOpera->setText("Informazioni Dipinto");
	operaInfoLayout->addRow(infoOpera);
	operaInfoLayout->addRow("Nome dipinto: ", new QLabel(dipinto->getName()));
	operaInfoLayout->addRow("Altezza in centimetri: ", new QLabel(QString::number(1.0 * dipinto->getHeight())));
	operaInfoLayout->addRow("Larghezza in centimetri: ", new QLabel(QString::number(1.0 * dipinto->getWidth())));
	operaInfoLayout->addRow("Prezzo in euro: ", new QLabel(QString("%L1").arg(dipinto->getPrice())));
	operaInfoLayout->addRow(createLine());
	operaInfoLayout->addRow("Tipo pittura: ", new QLabel(dipinto->getDipintoTypeString()));
	authorInfoLayout->setContentsMargins(100,0,0,0);
	authorInfoLayout->addRow(infoAuthor);
	authorInfoLayout->addRow("Nome Autore: ", new QLabel(dipinto->getAuthor()));
	authorInfoLayout->addRow("Opere esposte dall' autore: ", new QLabel(QString::number(controller->countSameAuthor(dipinto->getAuthor()))));
	galleryInfoLayout->setContentsMargins(100,0,0,0);
	galleryInfoLayout->addRow(infoMostra);
	galleryInfoLayout->addRow("Data creazione: ", new QLabel(locale.toString(dipinto->getCreationDate(), format)));
	galleryInfoLayout->addRow("Data prima esposizione: ", new QLabel(locale.toString(dipinto->getExpositionDate(), format)));
	galleryInfoLayout->addRow("Al momento in vendita in galleria: ", new QLabel(dipinto->isOnSale() ? "SI" : "NO"));
    }
  }
}

void MuseoVirtuale::createBottomLayout() {
  bottomLayout= new QVBoxLayout;

  // Components
  searchBox = new QLineEdit;
  typeBox = new QComboBox;
  showBox = new QComboBox;

  // Search
  QLabel* searchLabel = new QLabel("Cerca");
  searchLabel->setStyleSheet("font-weight: bold; color: black; margin-top: 10px");
  searchBox->setFixedSize(170,25);
  connect(searchBox, &QLineEdit::textChanged, [this] {
      if (!listOperaContainer.isEmpty()) buildTextList(searchBox->text(), typeBox->currentText(), showBox->currentText() == "No" ? false : true);
  });

  // Show
  QLabel* typeLabel = new QLabel("Opera");
  typeLabel->setStyleSheet("font-weight: bold; color: black; margin-top: 10px");
  typeBox->setFixedSize(170,25);
  typeBox->addItem("Tutte");
  typeBox->addItem("Dipinto");
  typeBox->addItem("Quadro");
  typeBox->addItem("Scultura");
  typeBox->addItem("Mosaico");
  connect(typeBox, &QComboBox::currentTextChanged, [this] {
      if (!listOperaContainer.isEmpty()) buildList(searchBox->text(), typeBox->currentText(), showBox->currentText() == "No" ? false : true);
  });

  // Show
  QLabel* showLabel = new QLabel("Solo in vendita");
  showLabel->setStyleSheet("font-weight: bold; color: black; margin-top: 10px");
  showBox->setFixedSize(170,25);
  showBox->addItem("No");
  showBox->addItem("Si");
  connect(showBox, &QComboBox::currentTextChanged, [this] {
      if (!listOperaContainer.isEmpty()) buildList(searchBox->text(), typeBox->currentText(), showBox->currentText() == "No" ? false : true);
  });

  // Reset
  QPushButton* resetButton = new QPushButton("Rimuovi filtri");
  resetButton->setStyleSheet("font-weight: bold; color: black; margin-top: 10px");
  resetButton->setFixedSize(170,30);
  connect(resetButton, SIGNAL(clicked()), this, SLOT(resetFilters()));

  bottomLayout->addWidget(searchLabel);
  bottomLayout->addWidget(searchBox);
  bottomLayout->addWidget(typeLabel);
  bottomLayout->addWidget(typeBox);
  bottomLayout->addWidget(showLabel);
  bottomLayout->addWidget(showBox);
  bottomLayout->addWidget(resetButton);

  bottomLayout->setContentsMargins(18,0,0,120);

  bottomLayout->addStretch();

  mainLayout->addLayout(bottomLayout);
}

void MuseoVirtuale::resetNameList(){
  if (operaList->count() != 0) {
      operaList->reset();
      operaList->clear();
  }
}

void MuseoVirtuale::buildList(const QString& nameStr, const QString& showStr, bool typeSale){
    resetNameList();
    showList(showStr, typeSale, controller->getOperaContainer());
    searchList(nameStr);
}

void MuseoVirtuale::buildTextList(const QString& searchStr, const QString& showStr, bool typeSale) {
  resetNameList();
  if (!listOperaContainer.isEmpty()){
    searchList(searchStr);
    showList(showStr, typeSale, controller->searchByTpeAndName(showStr, searchStr));
  }
}

void MuseoVirtuale::rebuildAfterSearch(Opera* op, bool &showFirstImage, bool typeSale) {
  if (typeSale) {
    if (op->isOnSale()) operaList->addItem(new QListWidgetItem(op->getName()));
  } else operaList->addItem(new QListWidgetItem(op->getName()));
  if (showFirstImage) {
    insertImg(op);
    showFirstImage = false;
  }
}

void MuseoVirtuale::showList(const QString& str, bool typeSale, Container<DeepPtr<Opera>> opereToShow) {
  bool showFirstImage = true;
  if (str == "Tutte") updateList(str, typeSale, opereToShow);
  else if (str == "Quadro") {
      for (int i = 0; i < opereToShow.getSize(); ++i) {
	  Quadro* quadro = dynamic_cast<Quadro*>(opereToShow[i]->clone());
	  if (quadro) rebuildAfterSearch(quadro, showFirstImage, typeSale);
      }
  } else if (str == "Scultura") {
      for (int i = 0; i < opereToShow.getSize(); ++i) {
	  Scultura* scultura = dynamic_cast<Scultura*>(opereToShow[i]->clone());
	  if (scultura) rebuildAfterSearch(scultura, showFirstImage, typeSale);
      }
  } else if (str == "Mosaico") {
    for (int i = 0; i < opereToShow.getSize(); ++i) {
	Mosaico* mosaico = dynamic_cast<Mosaico*>(opereToShow[i]->clone());
	if (mosaico) rebuildAfterSearch(mosaico, showFirstImage, typeSale);
    }
  } else if (str == "Dipinto") {
    for (int i = 0; i < opereToShow.getSize(); ++i) {
	Dipinto* dipinto = dynamic_cast<Dipinto*>(opereToShow[i]->clone());
	if (dipinto && dipinto->getCategory() == "Dipinto") rebuildAfterSearch(dipinto, showFirstImage, typeSale);
    }
  }
}

void MuseoVirtuale::insertImg(Opera* operaToDispay){
  operaImg.load(operaToDispay->clone()->getImgPath());
  operaLabel->setPixmap(operaImg);
}

void MuseoVirtuale::searchList(const QString & str) {
    for (int i = 0; i < operaList->count(); ++i) {
	QListWidgetItem* listItem = operaList->item(i);
	if (!listItem->text().toLower().startsWith(str.toLower())) {
	    operaList->takeItem(i);
	    --i;    // count() gets updated by takeItem()
	}
    }
}

void MuseoVirtuale::resetFilters() {
    searchBox->clear();
    typeBox->setCurrentIndex(0);
    showBox->setCurrentIndex(0);
}

MuseoVirtuale::MuseoVirtuale(Controller* c, QWidget *parent) : QMainWindow(parent), controller(c) {
  setWindowIcon(QIcon(":/img/appIcona.png"));
  setFixedSize(1600, 900);
  appLayout = new QVBoxLayout;
  midLayout = new QVBoxLayout;
  authorInfoLayout = new QFormLayout;
  operaInfoLayout = new QFormLayout;
  galleryInfoLayout = new QFormLayout;

  listOperaContainer = controller->getOperaContainer();

  addMenu();
  createTopLayout();
  buildOperaLayout();
  createBottomLayout();
  updateList("Tutte", false, listOperaContainer);
  appLayout->addLayout(mainLayout);
  appLayout->setSpacing(0);
  QWidget* mainWidget = new QWidget(this);
  mainWidget->setLayout(appLayout);
  setCentralWidget(mainWidget);
}

void MuseoVirtuale::showErrorMessage(const QString& message) {
  QDialog* dialog = new QDialog();
  dialog->setWindowTitle("Galleria virtuale");
  QVBoxLayout* layout = new QVBoxLayout(dialog);

  dialog->resize(260, 200);
  // Blocco dal resize odioso dell' utente con ben 7 righe di codice purtroppo
  QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(dialog->sizePolicy().hasHeightForWidth());
  dialog->setSizePolicy(sizePolicy);
  dialog->setMinimumSize(QSize(260, 200));
  dialog->setMaximumSize(QSize(260, 200));
  dialog->setSizeGripEnabled(false);

  dialog->setAttribute(Qt::WA_DeleteOnClose); // Evito memory leak

  // Inserisco il messaggio nella finestra con QLabel
  layout->addWidget(new QLabel(message, dialog), 0, Qt::AlignCenter);

  // Mostrare la finestra
  dialog->exec(); //Blocco il widget
}


void MuseoVirtuale::addMenu() {
  mainLayout = new QVBoxLayout;
  toolbarLayout = new QHBoxLayout;

  menuBar = new QMenuBar;

  QMenu* file = new QMenu("File", menuBar);
  QMenu* help = new QMenu("Help", menuBar);

  // Menù "File"
  QAction* save= file->addAction("Salva");
  QAction* load= file->addAction("Carica");
  QAction* exit = file->addAction("Chiudi");

  connect(save, SIGNAL(triggered()),controller, SLOT(saveData()));
  connect(load, SIGNAL(triggered()),controller,SLOT(loadData()));
  connect(exit, SIGNAL(triggered()),this,SLOT(close()));

  // Menù "Help"
  QAction* helpButton = help->addAction("Informazioni");
  connect(helpButton, SIGNAL(triggered()), this, SLOT(showInfoMsg()) );

  menuBar->addMenu(file);
  menuBar->addMenu(help);
  toolbarLayout->addWidget(menuBar);
  appLayout->addLayout(toolbarLayout);
}

void MuseoVirtuale::clearLayout(QLayout* layout){
    while(layout->count() > 0){
	QLayoutItem* item = layout->takeAt(0);
	if(QWidget* widget = item->widget()){
	    widget->deleteLater();
	}
	else if (QLayout* innerLayout = item->layout()) {
	    clearLayout(innerLayout);
	}
	delete item;
    }
}

void MuseoVirtuale::updateList(const QString& typeOpera, bool typeSale, Container<DeepPtr<Opera>> opereToShow) {
    for (int i = 0; i < opereToShow.getSize(); i++) {
      const Opera* deepOpera = opereToShow[i]->clone();
      if (!typeSale) operaList->addItem(new QListWidgetItem(deepOpera->getName()));
      else if (typeSale) if (deepOpera->isOnSale()) operaList->addItem(new QListWidgetItem(deepOpera->getName()));
    }

    if (operaList->count() > 0){
      auto test = operaList->item(0)->text();
      insertImg(controller->searchByTpeAndName(typeOpera, operaList->item(0)->text())[0]->clone());
    }
}

void MuseoVirtuale::setController(Controller *c) { controller = c;}

void MuseoVirtuale::reBuildLayout() {
  authorInfoLayout = new QFormLayout;
  operaInfoLayout = new QFormLayout;
  galleryInfoLayout = new QFormLayout;

  listOperaContainer = controller->getOperaContainer();
  if (!listOperaContainer.isEmpty()) {
      inserisciDescrizioneOpera(listOperaContainer[0]->clone());
      updateForm();
  } else {
    authorInfoLayout->addRow("Attenzione ", new QLabel("Nessuna opera in mostra"));
    updateForm();
    mainLayout->addLayout(midLayout);
  }
}

void MuseoVirtuale::updateEntireView() {
  clearLayout(midInfoLayout);
  reBuildLayout();
  updateList("Tutte", false, listOperaContainer);
  mainLayout->update();
}

QFrame* MuseoVirtuale::createLine() {
    QFrame* line = new QFrame;
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    return line;
}
