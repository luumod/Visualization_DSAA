#ifndef SORT_FACTORY
#define SORT_FACTORY

#include <QObject>

class SortObject;

/**
 * @brief Factory of all sort object.
 */
class SortFactory : public QObject
{
	Q_OBJECT
private:
	/**
	 * @brief Constructor of SortFactory.
	 */
	explicit SortFactory(QObject* parent = nullptr);
public:
	/**
	 * @brief Because of it is a singleton object, return the only static member.
	 */
	static SortFactory* getInstance();

	/**
	 * @brief According to the idx to create particular sort object.
	 * @param idx The sort type. case Bubble, Quick, Shell .etc
	 * @param parent Their parent object of the sort object.
	 */
	SortObject* createSortObject(int idx, QObject* parent);

	/**
	 * @brief Storage all of supported sort algorithms and return a QStringList to convenient programmer use.
	 */
	QStringList getSortList() const;
};

#endif // !SORT_FACTORY

