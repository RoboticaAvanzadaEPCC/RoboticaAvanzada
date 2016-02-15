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
#include "specificworker.h"

/**
* \brief Default constructor
*/
SpecificWorker::SpecificWorker(MapPrx& mprx) : GenericWorker(mprx)
{
	IK=false;
	modovalue=0;
}

/**
* \brief Default destructor
*/
SpecificWorker::~SpecificWorker()
{
	
}

bool SpecificWorker::setParams(RoboCompCommonBehavior::ParameterList params)
{

	string name = PROGRAM_NAME;
	base=QString::fromStdString(params[name+".floor"].value);
	base=QString::fromStdString(params[name+".base"].value);
	inner = new InnerModel(params[name+".InnerModel"].value);
	
	for(int i=1;i<=6;i++)
	{
		legs<<QString::fromStdString(params[name+".nameleg"+to_string(i)].value);
	}
	qDebug()<<"-----------------------legs----------------";
	qDebug()<<base;
	qDebug()<<legs;
	qDebug()<<"-----------------------legs----------------";
	
	leg1=inner->transform(base,legs.at(0));
	leg2=inner->transform(base,legs.at(1));
	leg3=inner->transform(base,legs.at(2));
	leg4=inner->transform(base,legs.at(3));
	leg5=inner->transform(base,legs.at(4));
	leg6=inner->transform(base,legs.at(5));
	timer.start(Period);

	return true;
}

void SpecificWorker::compute()
{
	switch(modovalue)
	{
		case 0:
			modo->setText("FK");
			break;
		case 1:
			modo->setText("IK Leg");
			break;
		case 2:
			modo->setText("IK Body");
			break;
	}
		
// 		leg1=inner->transform(base,legs.at(0));
// 		leg2=inner->transform(base,legs.at(1));
// 		leg3=inner->transform(base,legs.at(2));
// 		leg4=inner->transform(base,legs.at(3));
// 		leg5=inner->transform(base,legs.at(4));
// 		leg6=inner->transform(base,legs.at(5));
	
// 	try
// 	{
// 		camera_proxy->getYImage(0,img, cState, bState);
// 		memcpy(image_gray.data, &img[0], m_width*m_height*sizeof(uchar));
// 		searchTags(image_gray);
// 	}
// 	catch(const Ice::Exception &e)
// 	{
// 		std::cout << "Error reading from Camera" << e << std::endl;
// 	}
}


void SpecificWorker::sendData(const TData& data)
{
// 	QVec angles=QVec::zeros(3);
	RoboCompLegController::AnglesLeg angles;
	RoboCompLegController::PoseLeg pos;
	pos.vel=2;
	pos.ref=base.toStdString();
	angles.q1=0;
	angles.q2=0;
	angles.q3=0;
	float x=0,y=0,z=0;
	for(auto b:data.buttons)
	{
		if(b.clicked){
			modovalue+=1;
			if(modovalue==3)
				modovalue=0;
			break;
		}
	}
	for(auto m:data.axes)
	{
		if(m.name=="x")
		{
			angles.q1=(m.value/65537);
			x=m.value/1000;
		}
		if(m.name=="y")
		{
			angles.q2=(m.value/65537);
			y=m.value/1000;
		}
		if(m.name=="z")
		{
			angles.q3=(m.value/65537);
			z=m.value/1000;
		}
	}
	switch(modovalue)
	{
		case 0:
			legcontroller1_proxy->setFKLeg(angles);
			legcontroller2_proxy->setFKLeg(angles);
			legcontroller3_proxy->setFKLeg(angles);
			legcontroller4_proxy->setFKLeg(angles);
			legcontroller5_proxy->setFKLeg(angles);
			legcontroller6_proxy->setFKLeg(angles);
			break;
		case 1:
			pos.x=leg1.x()+x;
			pos.y=leg1.y()+y;
			pos.z=leg1.z()+z;
			legcontroller1_proxy->setIKLeg(pos);
			
			pos.x=leg2.x()+x;
			pos.y=leg2.y()+y;
			pos.z=leg2.z()+z;
			legcontroller2_proxy->setIKLeg(pos);
			
			pos.x=leg3.x()+x;
			pos.y=leg3.y()+y;
			pos.z=leg3.z()+z;
			legcontroller3_proxy->setIKLeg(pos);
			
			pos.x=leg4.x()+x;
			pos.y=leg4.y()+y;
			pos.z=leg4.z()+z;
			legcontroller4_proxy->setIKLeg(pos);
			
			pos.x=leg5.x()+x;
			pos.y=leg5.y()+y;
			pos.z=leg5.z()+z;
			legcontroller5_proxy->setIKLeg(pos);
			
			pos.x=leg6.x()+x;
			pos.y=leg6.y()+y;
			pos.z=leg6.z()+z;
			legcontroller6_proxy->setIKLeg(pos);
			break;
		case 2:
			RoboCompLegController::PoseBody pb;
			pb.vel=2;
			pb.rx=angles.q1;
			pb.ry=angles.q2;
			pb.rz=angles.q3;
			legcontroller1_proxy->setIKBody(pb);
			legcontroller2_proxy->setIKBody(pb);
			legcontroller3_proxy->setIKBody(pb);
			legcontroller4_proxy->setIKBody(pb);
			legcontroller5_proxy->setIKBody(pb);
			legcontroller6_proxy->setIKBody(pb);
			break;
	}
}






