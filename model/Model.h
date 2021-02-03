#ifndef MODEL_H
#define MODEL_H

#include "utility/Container.h"
#include "utility/DeepPtr.h"
#include "schema/Opera.h"

class Model {

private:
  Container<DeepPtr<Opera>> operaContainer;
public:
  Model();
  ~Model();
  Container<DeepPtr<Opera>> getOperaContainer() const;
  Container<DeepPtr<Opera>> getOperaByTypeAndName(const QString& = "", const QString& = "") const;
  void choseOpera(const QString& , const QString&, Container<DeepPtr<Opera>> &) const;
  unsigned int getCountSameAuthor(const QString&) const;
  void clearOperaContainer();
  void insertOpera(Opera*);
  void deleteOpera(Opera*);
  DeepPtr<Opera> searchOpera(int) const;
};

#endif // MODEL_H
