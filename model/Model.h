#ifndef MODEL_H
#define MODEL_H

#include "utility/Container.h"
#include "utility/DeepPtr.h"
#include "schema/Opera.h"

class Model {

private:
  Container<DeepPtr<Opera>> operaContainer;
public:
  Model() = default;
  ~Model();
  Container<DeepPtr<Opera>> getOperaContainer() const;
  Container<DeepPtr<Opera>> getOperaByTypeAndName(const QString&, const QString&, bool) const;
  void choseOpera(const QString& , const QString&, bool, Container<DeepPtr<Opera>>&) const;
  unsigned int getCountSameAuthor(const QString&) const;
  DeepPtr<Opera> searchOpera(int) const;
  int searchOperaGivenName(const QString&) const;
  void clearOperaContainer();
  void insertOpera(Opera*);
  void deleteOpera(int);
};

#endif // MODEL_H
