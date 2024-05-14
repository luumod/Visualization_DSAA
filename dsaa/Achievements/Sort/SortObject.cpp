#include "SortObject.h"

SortObject::SortObject(QObject *parent)
	: QObject(parent)
{

}

bool SortObject::getRunFlag() const
{
	return runFlag;
}

void SortObject::setRunFlag(bool flag)
{
	if (runFlag == flag) {
		return;
	}
	runFlag = flag;
	emit runFlagChanged(flag);
}

void SortObject::on_single_step()
{
	loop_single_step.quit();
}

void SortObject::on_finish_all()
{
	loop_single_step.quit();
	finish = true;
}
