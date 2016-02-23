/*
 *    Copyright (C) 2016 by YOUR NAME HERE
 *
 *    This file is part of RoboComp
 *
 *    RoboComp is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    RoboComp is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with RoboComp.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "legcontrollerI.h"

LegControllerI::LegControllerI(GenericWorker *_worker, QObject *parent) : QObject(parent)
{
	worker = _worker;
	mutex = worker->mutex;       // Shared worker mutex
}


LegControllerI::~LegControllerI()
{
}

void LegControllerI::setListIKLeg(const ListPoseLeg  &ps, const Ice::Current&)
{
	worker->setListIKLeg(ps);
}

StateLeg LegControllerI::getStateLeg(const Ice::Current&)
{
	return worker->getStateLeg();
}

void LegControllerI::setIKLeg(const PoseLeg  &p, const Ice::Current&)
{
	worker->setIKLeg(p);
}

void LegControllerI::setIKBody(const PoseBody  &p, const Ice::Current&)
{
	worker->setIKBody(p);
}

void LegControllerI::setFKLeg(const AnglesLeg  &al, const Ice::Current&)
{
	worker->setFKLeg(al);
}






