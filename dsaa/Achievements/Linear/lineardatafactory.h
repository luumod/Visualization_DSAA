#ifndef LINEAR_DATA_FACTORY_H_
#define LINEAR_DATA_FACTORY_H_

#include "base_list.h"

class LinearDataFactory : public QObject
{
	Q_OBJECT

private:
	explicit LinearDataFactory(QObject* parent = nullptr);
public:
	static LinearDataFactory* getInstance();

	BaseList* createLinearObject(int row, QObject* parent);
};

#endif // !LINEAR_DATA_FACTORY_H_


