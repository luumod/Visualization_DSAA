#include "framelesswindow.h"
#include "logger.h"
#include "common.h"
#include <QGraphicsDropShadowEffect>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPainterPath>
#include <QMouseEvent>
#include <QGuiApplication>
#include <QPointF>

#define MAX_MOUSE_MOVEMENT 300

FramelessWindow::FramelessWindow(int cornerRadius, unsigned int attributes, QWidget* parent)
	: _cornerRadius(cornerRadius), _attributes((LUI_WINDOW_ATTRIBUTES)attributes), QWidget(parent)
{
#if DEBUG
	Logger::debug("Begin initialized FramelessWindow");
#endif // DEBUG
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowFlags(Qt::FramelessWindowHint);
	setFocusPolicy(Qt::StrongFocus);
	setMouseTracking(true);
	setFocus();
	
	// Create and properly set real displayed window widget
	_FstretchLayout = new QVBoxLayout(this);
	_FstretchLayout->setContentsMargins(30, 30, 30, 30);
	_FwindowWidget = new QWidget(this);
	_FwindowWidget->setObjectName("windowWidget");
	_FwindowWidget->setMouseTracking(true);
	_FstretchLayout->addWidget(_FwindowWidget);
	_FwindowWidget->show();
	setLayout(_FstretchLayout);

	// Set style sheet for window widget
	QString windowWidgetStyleSheet = "QWidget#windowWidget{background-color:" + _backgroundColor.name(QColor::HexArgb) + ";border-radius:" + QString::number(_cornerRadius) + "px;}";
	_FwindowWidget->setStyleSheet(windowWidgetStyleSheet);

	// Set shadow for window widget
	_FwindowShadow = new QGraphicsDropShadowEffect(_FwindowWidget);
	_FwindowShadow->setBlurRadius(30);
	_FwindowShadow->setColor(QColor(0, 0, 0));
	_FwindowShadow->setOffset(0, 0);
	_FwindowWidget->setGraphicsEffect(_FwindowShadow);

	// Create window control buttons container widget & its layout
	// buttons: minimum, maximum, close.
	_FwindowBtnWidget = new QWidget(_FwindowWidget);
	_FwindowBtnWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	_FwindowBtnWidget->setMouseTracking(true);
	_FwindowBtnLayout = new QHBoxLayout(_FwindowBtnWidget);
	_FwindowBtnLayout->setContentsMargins(0, 0, 0, 0);
	_FwindowBtnLayout->setSpacing(10);
	_FwindowBtnLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	_FwindowBtnWidget->setLayout(_FwindowBtnLayout);

	// Create window control buttons
	_minimizeBtn = new QPushButton(_FwindowBtnWidget);
	_maximizeBtn = new QPushButton(_FwindowBtnWidget);
	_closeBtn = new QPushButton(_FwindowBtnWidget);

	_minimizeBtn->setFixedSize(12, 12);
	_maximizeBtn->setFixedSize(12, 12);
	_closeBtn->setFixedSize(12, 12);

	_minimizeBtn->setStyleSheet("QPushButton{border-radius: 6px; background-color: #c2c2c2;}"
		"QPushButton:hover{background-color: #e98b2a;}");
	_maximizeBtn->setStyleSheet("QPushButton{border-radius: 6px; background-color: #c2c2c2;}"
		"QPushButton:hover{background-color: #2d6d4b;}");
	_closeBtn->setStyleSheet("QPushButton{border-radius: 6px; background-color: #c2c2c2;}"
		"QPushButton:hover{background-color: #ab3b3a;}");

	_FwindowBtnLayout->addWidget(_minimizeBtn);
	_FwindowBtnLayout->addWidget(_maximizeBtn);
	_FwindowBtnLayout->addWidget(_closeBtn);
	if ((_attributes & LUI_WINDOW_ATTRIBUTES::LUI_WINDOW_DISABLE_MINIMIZE) == 0) {
		_minimizeBtn->show();
	}
	if ((_attributes & LUI_WINDOW_ATTRIBUTES::LUI_WINDOW_DISABLE_MAXIMIZE) == 0) {
		_maximizeBtn->show();
	}
	if ((_attributes & LUI_WINDOW_ATTRIBUTES::LUI_WINDOW_DISABLE_CLOSE) == 0) {
		_closeBtn->show();
	}

	// Connect window control buttons
	connect(_minimizeBtn, &QPushButton::clicked, this, &QWidget::showMinimized);
	//connect(_maximizeBtn, &QPushButton::clicked, this, &FramelessWindow::controlWindowScale);
	connect(_closeBtn, &QPushButton::clicked, this, &QWidget::close);


#if DEBUG
	Logger::debug("------- End initialized FramelessWindow -------");
#endif // DEBUG
}

FramelessWindow::FramelessWindow(QWidget* parent)
	: FramelessWindow(0, LUI_WINDOW_ATTRIBUTES::LUI_WINDOW_NO_ATTRIBUTES, parent)
{
}

FramelessWindow::FramelessWindow(int cornerRadius, QWidget* parent)
	: FramelessWindow(cornerRadius, LUI_WINDOW_ATTRIBUTES::LUI_WINDOW_NO_ATTRIBUTES, parent)
{
}

FramelessWindow::FramelessWindow(unsigned int attributes, QWidget* parent)
	: FramelessWindow(0, attributes, parent)
{
}

FramelessWindow::~FramelessWindow() {}

void FramelessWindow::showEvent(QShowEvent* event) {
	// Initialize window UI after window is shown
	initializeWindowUI();
}

void FramelessWindow::initializeWindowUI() {
	if (_initialized) {
		return;
	}

	// Create a round cornered mask for window widget
	QPainterPath path;
	path.addRoundedRect(_FwindowWidget->rect(), _cornerRadius - 1, _cornerRadius - 1);
	QRegion region(path.toFillPolygon().toPolygon());
	_FwindowWidget->setMask(region);

	// Create a border for window widget (in order to hide zigzagged edges)
	_FwindowBorder = new QWidget(this);
	_FwindowBorder->setObjectName("windowBorder");
	QString windowBorderStyleSheet =
		"QWidget#windowBorder{background-color:#00FFFFFF;border:1.5px solid " + _borderColor.name(QColor::HexArgb) + ";border-radius:" + QString::number(_cornerRadius) + "px;}";
	_FwindowBorder->setStyleSheet(windowBorderStyleSheet);
	_FwindowBorder->setAttribute(Qt::WA_TransparentForMouseEvents);
	_FwindowBorder->move(_FwindowWidget->pos() - QPoint(1, 1));
	_FwindowBorder->resize(_FwindowWidget->size() + QSize(2, 2));
	_FwindowBorder->show();

	// Move button widget to the top right of the window widget
	_FwindowBtnWidget->move(_FwindowWidget->width() - _FwindowBtnWidget->width() - 18, 18);
	_FwindowBtnWidget->show();
	_FwindowBtnWidget->raise();

	// Set initialized state
	_initialized = true;
}

void FramelessWindow::resizeEvent(QResizeEvent* event) {
	// Resize window border
	if (_FwindowBorder != nullptr) {
		_FwindowBorder->move(_FwindowWidget->pos() - QPoint(1, 1));
		_FwindowBorder->resize(_FwindowWidget->size() + QSize(2, 2));
	}

	// Resize window mask
	QPainterPath path;
	path.addRoundedRect(_FwindowWidget->rect(), _cornerRadius - 1, _cornerRadius - 1);
	QRegion region(path.toFillPolygon().toPolygon());
	_FwindowWidget->setMask(region);

	// Move button widget to the top right of the window widget
	_FwindowBtnWidget->move(_FwindowWidget->width() - _FwindowBtnWidget->width() - 18, 18);
}

void FramelessWindow::controlWindowScale() {
	if ((_attributes & LUI_WINDOW_ATTRIBUTES::LUI_WINDOW_DISABLE_MAXIMIZE) != 0) {
		return;
	}
	if (!_maximized) {
		// Maximized the window from current size.
		_lastWindowGeometry = frameGeometry(); // store the rect data.

//#if DEBUG
//		Logger::debug("**************** Maximizing window ****************");
//		Logger::debug(QString::fromStdString("[+] current window size: " + std::to_string(width()) + ", " + std::to_string(height())));
//		Logger::debug(QString::fromStdString("[+] current geometry: " + std::to_string(_lastWindowGeometry.x()) + ", " + std::to_string(_lastWindowGeometry.y()) + ", " + std::to_string(_lastWindowGeometry.width()) + ", " + std::to_string(_lastWindowGeometry.height())));
//		Logger::debug(QString::fromStdString("[+] current window widget size: " + std::to_string(_FwindowWidget->width()) + ", " + std::to_string(_FwindowWidget->height())));
//#endif // USE_LOGGER
//		_FwindowShadow->setEnabled(false);
//		_FwindowBorder->hide();
//		QString windowWidgetStyleSheet = "QWidget#windowWidget{background-color:" + _backgroundColor.name(QColor::HexArgb) + ";}";
//		_FwindowWidget->setStyleSheet(windowWidgetStyleSheet);
//
//		_FstretchLayout->setContentsMargins(0, 0, 0, 0);

		// Maximized the window.
		showMaximized();

		/*QPainterPath path;
		path.addRect(_FwindowWidget->rect());
		QRegion mask(path.toFillPolygon().toPolygon());
		_FwindowWidget->setMask(mask);*/

		_maximized = true;
	}
	else {
		// Restores the widget after it has been maximized or minimized.
		_FstretchLayout->setContentsMargins(30, 30, 30, 30);

		showNormal();

		resize(_lastWindowGeometry.size());
		move(_lastWindowGeometry.topLeft());

		_FwindowShadow->setEnabled(true);
		_FwindowBorder->show();
		QString windowWidgetStyleSheet = "QWidget#windowWidget{background-color:" + _backgroundColor.name(QColor::HexArgb) + ";border-radius:" + QString::number(_cornerRadius) + "px;}";
		_FwindowWidget->setStyleSheet(windowWidgetStyleSheet);

		QPainterPath path;
		path.addRoundedRect(_FwindowWidget->rect(), _cornerRadius - 1, _cornerRadius - 1);
		QRegion mask(path.toFillPolygon().toPolygon());
		_FwindowWidget->setMask(mask);

#if DEBUG
		Logger::debug("**************** Restoring window ****************");
		Logger::debug(QString::fromStdString("[+] current window size: " + std::to_string(width()) + ", " + std::to_string(height())));
		Logger::debug(QString::fromStdString("[+] current geometry: " + std::to_string(frameGeometry().x()) + ", " + std::to_string(frameGeometry().y()) + ", " + std::to_string(frameGeometry().width()) + ", " + std::to_string(frameGeometry().height())));
		Logger::debug(QString::fromStdString("[+] current window widget size: " + std::to_string(_FwindowWidget->width()) + ", " + std::to_string(_FwindowWidget->height())));
#endif // USE_LOGGER
		_maximized = false;
	}
}

void FramelessWindow::updateMouseState(QMouseEvent* event) {
	_mouseState = MOUSE_STATE_NONE;
	if ((_attributes & LUI_WINDOW_ATTRIBUTES::LUI_WINDOW_DISABLE_RESIZE) != 0) {
		return;
	}
	if (_maximized) {
		setCursor(Qt::ArrowCursor);
		return;
	}
	// Set mouse state according to abs distance from window border
	if (abs(event->globalPos().x() - (_FwindowWidget->frameGeometry().left() + frameGeometry().left())) < 5) {
		_mouseState |= MOUSE_STATE_RESIZE_LEFT;
	}
	if (abs(event->globalPos().x() - (_FwindowWidget->frameGeometry().right() + frameGeometry().left())) < 5) {
		_mouseState |= MOUSE_STATE_RESIZE_RIGHT;
	}
	if (abs(event->globalPos().y() - (_FwindowWidget->frameGeometry().top() + frameGeometry().top())) < 5) {
		_mouseState |= MOUSE_STATE_RESIZE_TOP;
	}
	if (abs(event->globalPos().y() - (_FwindowWidget->frameGeometry().bottom() + frameGeometry().top())) < 5) {
		_mouseState |= MOUSE_STATE_RESIZE_BOTTOM;
	}
	// Set cursor shape according to mouse state
	switch (_mouseState) {
		case MOUSE_STATE_RESIZE_LEFT:
		case MOUSE_STATE_RESIZE_RIGHT:
			setCursor(Qt::SizeHorCursor);
			break;
		case MOUSE_STATE_RESIZE_TOP:
		case MOUSE_STATE_RESIZE_BOTTOM:
			setCursor(Qt::SizeVerCursor);
			break;
		case MOUSE_STATE_RESIZE_LEFT | MOUSE_STATE_RESIZE_TOP:
		case MOUSE_STATE_RESIZE_RIGHT | MOUSE_STATE_RESIZE_BOTTOM:
			setCursor(Qt::SizeFDiagCursor);
			break;
		case MOUSE_STATE_RESIZE_LEFT | MOUSE_STATE_RESIZE_BOTTOM:
		case MOUSE_STATE_RESIZE_RIGHT | MOUSE_STATE_RESIZE_TOP:
			setCursor(Qt::SizeBDiagCursor);
			break;
		default:
			setCursor(Qt::ArrowCursor);
			break;
	}
}

void FramelessWindow::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton) {
		_mousePressed = true;
		_lastMousePosition = QPointF(event->globalPos());
	}
}

void FramelessWindow::mouseReleaseEvent(QMouseEvent* event) {
	_mousePressed = false;
	QScreen* screen = QGuiApplication::screenAt(event->globalPos());

	if (abs(event->globalPos().y() - screen->geometry().top()) < 5) {
		controlWindowScale();
	}
	updateMouseState(event);
}

void FramelessWindow::mouseMoveEvent(QMouseEvent* event) {
	if (event->buttons() == Qt::NoButton) {
		_mousePressed = false;
	}
	if (abs(event->globalPos().x() - _lastMousePosition.x()) > MAX_MOUSE_MOVEMENT) {
		// Maybe moving window across monitors, avoid window disappear
		_lastMousePosition = QPointF(event->globalPos());
	}
	if (abs(event->globalPos().y() - _lastMousePosition.y()) > MAX_MOUSE_MOVEMENT) {
		// Maybe moving window across monitors, avoid window disappear
		_lastMousePosition = QPointF(event->globalPos());
	}
	if (!_mousePressed) {
		updateMouseState(event);
	}
	else {
		// Resize window according to mouse state
		switch (_mouseState) {
			case MOUSE_STATE_RESIZE_LEFT:
				resize(frameGeometry().width() - event->globalPos().x() + frameGeometry().left() + _FwindowWidget->frameGeometry().left(), frameGeometry().height());
				move(event->globalPos().x() - _FwindowWidget->frameGeometry().left(), frameGeometry().top());
				break;
			case MOUSE_STATE_RESIZE_RIGHT:
				resize(event->globalPos().x() - frameGeometry().left() + _FwindowWidget->frameGeometry().left(), frameGeometry().height());
				break;
			case MOUSE_STATE_RESIZE_TOP:
				resize(frameGeometry().width(), frameGeometry().height() - event->globalPos().y() + frameGeometry().top() + _FwindowWidget->frameGeometry().top());
				move(frameGeometry().left(), event->globalPos().y() - _FwindowWidget->frameGeometry().top());
				break;
			case MOUSE_STATE_RESIZE_BOTTOM:
				resize(frameGeometry().width(), event->globalPos().y() - frameGeometry().top() + _FwindowWidget->frameGeometry().top());
				break;
			case MOUSE_STATE_RESIZE_LEFT | MOUSE_STATE_RESIZE_TOP:
				resize(frameGeometry().width() - event->globalPos().x() + frameGeometry().left() + _FwindowWidget->frameGeometry().left(), frameGeometry().height() - event->globalPos().y() + frameGeometry().top() + _FwindowWidget->frameGeometry().top());
				move(event->globalPos().x() - _FwindowWidget->frameGeometry().left(), event->globalPos().y() - _FwindowWidget->frameGeometry().top());
				break;
			case MOUSE_STATE_RESIZE_LEFT | MOUSE_STATE_RESIZE_BOTTOM:
				resize(frameGeometry().width() - event->globalPos().x() + frameGeometry().left() + _FwindowWidget->frameGeometry().left(), event->globalPos().y() - frameGeometry().top() + _FwindowWidget->frameGeometry().top());
				move(event->globalPos().x() - _FwindowWidget->frameGeometry().left(), frameGeometry().top());
				break;
			case MOUSE_STATE_RESIZE_RIGHT | MOUSE_STATE_RESIZE_TOP:
				resize(event->globalPos().x() - frameGeometry().left() + _FwindowWidget->frameGeometry().left(), frameGeometry().height() - event->globalPos().y() + frameGeometry().top() + _FwindowWidget->frameGeometry().top());
				move(frameGeometry().left(), event->globalPos().y() - _FwindowWidget->frameGeometry().top());
				break;
			case MOUSE_STATE_RESIZE_RIGHT | MOUSE_STATE_RESIZE_BOTTOM:
				resize(event->globalPos().x() - frameGeometry().left() + _FwindowWidget->frameGeometry().left(), event->globalPos().y() - frameGeometry().top() + _FwindowWidget->frameGeometry().top());
				break;
			default:
				if (_maximized) {
					qreal wRatio = (qreal)event->pos().x() / (qreal)_FwindowWidget->width();
					controlWindowScale();
					move(event->globalPos().x() - _FwindowWidget->width() * wRatio, event->globalPos().y() - 52);
				}
				else {
					move(frameGeometry().left() + event->globalPos().x() - _lastMousePosition.x(), frameGeometry().top() + event->globalPos().y() - _lastMousePosition.y());
				}
				break;
		}
		_lastMousePosition = QPointF(event->globalPos());
	}
}

FramelessWindow::LUI_WINDOW_ATTRIBUTES FramelessWindow::getWindowAttributes() {
	return _attributes;
}

void FramelessWindow::setWindowAttributes(unsigned int attributes) {
	_attributes = (LUI_WINDOW_ATTRIBUTES)attributes;
	if ((_attributes & LUI_WINDOW_ATTRIBUTES::LUI_WINDOW_DISABLE_MINIMIZE) == 0) {
		_minimizeBtn->show();
	}
	else {
		_minimizeBtn->hide();
	}
	if ((_attributes & LUI_WINDOW_ATTRIBUTES::LUI_WINDOW_DISABLE_MAXIMIZE) == 0) {
		_maximizeBtn->show();
	}
	else {
		_maximizeBtn->hide();
	}
	if ((_attributes & LUI_WINDOW_ATTRIBUTES::LUI_WINDOW_DISABLE_CLOSE) == 0) {
		_closeBtn->show();
	}
	else {
		_closeBtn->hide();
	}
}
