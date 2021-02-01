#include <QApplication>
#include "model/Model.h"
#include "model/Controller.h"
#include "model/Museovirtuale.h"
#include "utility/LoadEntryDataUtility.h"


int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  Model model;
  LoaDdataEntryUtility::retrieveStartData(model);
  Controller controller(&model);
  MuseoVirtuale museoVirtuale(&controller);
  controller.setView(&museoVirtuale);
  museoVirtuale.show();

  return a.exec();
}
