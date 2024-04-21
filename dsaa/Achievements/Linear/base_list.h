#ifndef CORE_BASE_LIST_H_
#define CORE_BASE_LIST_H_

#include <QObject>
#include <QColor>

class QPainter;
class BaseList : public QObject {
	Q_OBJECT

public:
	explicit BaseList(QObject* parent = nullptr);

	~BaseList();

	bool empty() const;

	std::size_t size() const;

	void updateColors(const QString& node, const QString& arrow, const QString& text);
	void updateSettings(int nodeWidth, int nodeHeight, int arrowSize, int textSpace, int maxNodesPerRow, int row_spacing);
	void resetSettings();
public:
	virtual void draw(QPainter* painter, int width, int height) = 0;

public:
	struct Node {
		int data{};
		Node* prev{};
		Node* next{};
	};
	using Node_ptr = Node*;

	Node_ptr m_head{ nullptr };
	Node_ptr m_tail{ nullptr };
	std::size_t m_size{};

	void init_first_element(const int& elem);

	void clean_up();

	void copy_data(const BaseList& rhs);

	void push_back(const int& elem);

	void push_front(const int& elem);

	int& back() const;

	int& front() const;

	void pop_front();

	void pop_back();

protected:
	int nodeWidth = 60;
	int nodeHeight = 30;
	int arrowSize = 10;
	int textSpace = 5;
	int maxNodesPerRow = 5;
	int row_spacing = 20;

	// Adjust color.
	QColor color_node = QColor(216, 240, 224);
	QColor color_text = QColor(0, 0, 0);
	QColor color_arrow = QColor(0, 0, 0);
};

#endif  // CORE_BASE_LIST_H_
