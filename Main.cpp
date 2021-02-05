#include <QApplication>
#include "model/Model.h"
#include "model/Controller.h"
#include "model/GalleriaVirtuale.h"
#include "utility/LoadEntryDataUtility.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Model model;
  LoaDdataEntryUtility::retrieveStartData(model);
  Controller controller(&model);
  GalleriaVirtuale galleriaVirtuale(&controller);
  controller.setView(&galleriaVirtuale);
  galleriaVirtuale.show();
  return a.exec();
}
