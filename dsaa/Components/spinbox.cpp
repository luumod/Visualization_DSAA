#include "spinbox.h"
#include "logger.h"
#include "common.h"
#include "textButton.h"
#include <QFont>
#include <QFontMetrics>
#include <QTimer>
#include <QValidator>
#include <QVBoxLayout>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

SpinBox::SpinBox(const QString& name, int minValue, int maxValue, int curValue, QWidget* parent) :
	QWidget(parent), minValue(minValue), maxValue(maxValue), curValue(curValue), defaultValue(curValue)
{
	QFont nameFont = QFont("Corbel", 12);
	QFontMetrics fm(nameFont);
	qreal height = fm.lineSpacing();
	itemName = new QLabel(this);
	itemName->setText(name);
	itemName->setFont(nameFont);
	itemName->setFixedHeight(height);
	itemName->setStyleSheet("color:#1c1c1c");

	QFont textFont = QFont("Corbel", 12);
	fm = QFontMetrics(textFont);
	editor = new QLineEdit(this);
	editor->setFixedHeight(fm.lineSpacing());
	editor->setStyleSheet("color:#5c5c5c;background-color:#00000000;border-style:none;");
	editor->setFont(textFont);
	editor->setReadOnly(false);
	editor->setValidator(new QIntValidator(minValue, maxValue, this));
	connect(editor, &QLineEdit::textChanged, this, [=]() {
		auto text = editor->text();
		if (text.toInt() > maxValue){
			indicator_edit->setStyleSheet("background-color:#ff0000;");
			enterEditEffect();
			this->curValue = maxValue;
		}
		else if (text.toInt() < minValue) {
			indicator_edit->setStyleSheet("background-color:#ff0000;");
			enterEditEffect();
			this->curValue = minValue;
		}
		else {
			indicator_edit->setStyleSheet("background-color:#0078d4;");
			leaveEditEffect();
			this->curValue = editor->text().toInt();
		}
		emit valueChanged(this->curValue);
	});

	bgWidget = new QWidget(this);
	bgWidget->setStyleSheet("background-color:#00000000;border-radius:5px;");
	bgWidget->lower();
	bgWidget->show();

	// The left indicator for the whole item.
	indicator_left = new QWidget(this);
	indicator_left->setStyleSheet("border-radius:3px;background-color:#0078D4");
	opac_left = new QGraphicsOpacityEffect(indicator_left);
	opac_left->setOpacity(0);
	indicator_left->setGraphicsEffect(opac_left);

	// The edit indicator for the edit action.
	indicator_edit = new QWidget(this);
	indicator_edit->setFixedHeight(4);
	indicator_edit->setStyleSheet("background-color:#0078d4;border-radius:2px");
	opac_edit = new QGraphicsOpacityEffect(this);
	opac_edit->setOpacity(0);
	indicator_edit->setGraphicsEffect(opac_edit);

	// Up and down button to adjust the value.
	upButton = new QPushButton(this);
	upButton->setFixedSize(16, 16);
	upButton->setStyleSheet("QPushButton{background-color:#00000000;border-style:none;} QPushButton:pressed{background-color:#1a000000;}");
	upButton->setIcon(QIcon(ICON_FILE "up-arrow.png"));
	connect(upButton, &QPushButton::clicked, this, &SpinBox::onUpButtonClicked);

	downButton = new QPushButton(this);
	downButton->setFixedSize(16, 16);
	downButton->setStyleSheet("QPushButton{background-color:#00000000;border-style:none;} QPushButton:pressed{background-color:#1a000000;}");
	downButton->setIcon(QIcon(ICON_FILE "down-arrow.png"));
	connect(downButton, &QPushButton::clicked, this, &SpinBox::onDownButtonClicked);

	// For the default conditions, the up and down button should be hidden.
	// When the mouse hover one of these, then show.
	upButton->hide();
	downButton->hide();

	this->setFixedHeight(itemName->height() + 10);

	updateEditor();
}

void SpinBox::resizeEvent(QResizeEvent* event)
{
#if DEBUG
	Logger::debug("-------- SpinBox::resizeEvent ---------\n");
#endif
	indicator_left->resize(6, 0.4 * this->height());
	indicator_left->move(4, 0.3 * this->height());

	itemName->move(margin, this->height() / 2 - itemName->height() / 2);
	itemName->setFixedWidth(this->width() * 0.3 - margin - spacing);

	editor->resize(this->width() * 0.6 - margin, editor->height());
	editor->move(this->width() * 0.5, this->height() / 2 - editor->height() / 2);

	upButton->move(this->width() * 0.9, this->height() / 2 - upButton->height());
	downButton->move(this->width() * 0.9, this->height() / 2);

	indicator_edit->move(this->width() * 0.5, this->height() - 7);
	indicator_edit->resize(this->width() * 0.45 - margin, 4);

	bgWidget->setFixedSize(this->size());
}

void SpinBox::enterEditEffect()
{
	QParallelAnimationGroup* group = new QParallelAnimationGroup(this);
	QPropertyAnimation* fade = new QPropertyAnimation(opac_edit, "opacity", this);
	fade->setStartValue(opac_edit->opacity());
	fade->setEndValue(0.99);
	fade->setDuration(150);
	group->addAnimation(fade);
	group->start();
}

void SpinBox::leaveEditEffect()
{
	QParallelAnimationGroup* group = new QParallelAnimationGroup(this);
	QPropertyAnimation* fade = new QPropertyAnimation(opac_edit, "opacity", this);
	fade->setStartValue(opac_edit->opacity());
	fade->setEndValue(0);
	fade->setDuration(350);
	group->addAnimation(fade);
	group->start();
}

void SpinBox::enterEvent(QEnterEvent* event)
{
	upButton->show();
	downButton->show();
	bgWidget->setStyleSheet("border-radius:5px;background-color:#0a000000");
	QParallelAnimationGroup* enter = new QParallelAnimationGroup(this);
	//Control the indication bar animation effect.
	QPropertyAnimation* longer = new QPropertyAnimation(indicator_left, "geometry", this);
	longer->setStartValue(indicator_left->geometry());
	longer->setEndValue(QRectF(4, 0.25 * this->height(), 6, this->height() * 0.5));
	longer->setDuration(150);
	longer->setEasingCurve(QEasingCurve::OutBack);
	//Control the opacity of the other area.
	QPropertyAnimation* fadeIn = new QPropertyAnimation(opac_left, "opacity", this);
	fadeIn->setStartValue(opac_left->opacity());
	fadeIn->setEndValue(0.99);
	fadeIn->setDuration(100);
	enter->addAnimation(longer);
	enter->addAnimation(fadeIn);
	enter->start();
}

void SpinBox::leaveEvent(QEvent* event)
{
	upButton->hide();
	downButton->hide();
	bgWidget->setStyleSheet("border-radius:5px;background-color:#00000000");
	QParallelAnimationGroup* leave = new QParallelAnimationGroup(this);
	QPropertyAnimation* shorter = new QPropertyAnimation(indicator_left, "geometry", this);
	shorter->setStartValue(indicator_left->geometry());
	shorter->setEndValue(QRectF(4, 0.3 * this->height(), 6, this->height() * 0.4));
	shorter->setDuration(150);
	shorter->setEasingCurve(QEasingCurve::OutBack);
	QPropertyAnimation* fadeOut = new QPropertyAnimation(opac_left, "opacity", this);
	fadeOut->setStartValue(opac_left->opacity());
	fadeOut->setEndValue(0);
	fadeOut->setDuration(100);
	leave->addAnimation(shorter);
	leave->addAnimation(fadeOut);
	leave->start();

	if (mousePressed)
		mousePressed = false;
}

void SpinBox::mousePressEvent(QMouseEvent* event)
{
	bgWidget->setStyleSheet("border-radius:5px;background-color:#1a000000");
	mousePressed = true;
}

void SpinBox::mouseReleaseEvent(QMouseEvent* event)
{
	if (mousePressed) {
		bgWidget->setStyleSheet("border-radius:5px;background-color:#0a000000");
		mousePressed = false;
	}
}

void SpinBox::onUpButtonClicked()
{
	if (enabled && curValue < maxValue) {
		curValue++;
		updateEditor();
		enterEditEffect();
		emit valueChanged(curValue);
		QTimer::singleShot(500, this, &SpinBox::leaveEditEffect);
	}
}

void SpinBox::onDownButtonClicked()
{
	if (enabled && curValue > minValue) {
		curValue--;
		updateEditor();
		enterEditEffect();
		emit valueChanged(curValue);
		QTimer::singleShot(500, this, &SpinBox::leaveEditEffect);
	}
}

void SpinBox::setValue(int value)
{
	if (value >= minValue && value <= maxValue) {
		curValue = value;
		updateEditor();
	}
}

int SpinBox::value() const
{
	return curValue;
}

void SpinBox::setRange(int min, int max)
{
	minValue = min;
	maxValue = max;
	if (curValue < minValue)
		curValue = minValue;
	else if (curValue > maxValue)
		curValue = maxValue;
	updateEditor();
}

void SpinBox::setEnabled(bool enable)
{
	enabled = enable;
	upButton->setEnabled(enable);
	downButton->setEnabled(enable);
}

void SpinBox::recoverDefaultValue(){
	curValue = defaultValue;
	updateEditor();
}

void SpinBox::updateEditor()
{
	editor->setText(QString::number(curValue));
}


/*
--------------------------------------------------------
*/

SpinBoxGroup::SpinBoxGroup(QString name, QWidget* parent) :
	QWidget(parent) {
	QFont titleFont = QFont("Corbel", 16);
	QFontMetrics fm(titleFont);
	qreal height = fm.lineSpacing();
	 
	QWidget* row_widget = new QWidget(this);
	QHBoxLayout* row_layout = new QHBoxLayout(row_widget);
	row_layout->setContentsMargins(0, 0, 0, 0);
	groupName = new QLabel(this);
	groupName->setMinimumHeight(height);
	groupName->setFont(titleFont);
	groupName->setText(name);
	
	textButton* btn_reset = new textButton("reset", this);
	connect(btn_reset, &textButton::clicked, this, [=]() {
		for (auto& x : spinboxs) {
			x->recoverDefaultValue();
		}
		emit spinBoxReset();
	});
	btn_reset->setFixedHeight(groupName->height());
	row_layout->addWidget(groupName);
	row_layout->addWidget(btn_reset);
	row_layout->setStretch(0, 7);
	row_layout->setStretch(1, 3);
	row_widget->setLayout(row_layout);

	QWidget* spacingLine = new QWidget(this);
	spacingLine->setFixedHeight(1);
	spacingLine->setStyleSheet("background-color:#0a000000");

	this->setFixedHeight(groupName->height() + middleSpacing + 1 + bottomSpacing);

	mainLayout = new QVBoxLayout(this);
	mainLayout->setContentsMargins(10, 0, 10, bottomSpacing);
	mainLayout->setSpacing(middleSpacing);
	mainLayout->addWidget(row_widget);
	mainLayout->addWidget(spacingLine);
}

void SpinBoxGroup::AddItem(SpinBox* item) {
	spinboxs.push_back(item);
	this->setFixedHeight(this->height() + middleSpacing + item->height());
	mainLayout->addWidget(item);
	if (selectedID == -1) {
		selectedID = 0;
	}
	connect(item, &SpinBox::valueChanged, this, &SpinBoxGroup::spinBoxItemChange);
}