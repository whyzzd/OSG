#include "DrawXXX.h"
#include <osgFX/Scribe>
#include<iostream>
DrawXXX::DrawXXX()
{
	em=new osg::EllipsoidModel;
}
DrawXXX::DrawXXX(float wid) :mLineWidth(wid)
{
	em = new osg::EllipsoidModel;
}
DrawXXX::~DrawXXX()
{

}

osg::Node* DrawXXX::createLine(osg::ref_ptr<osg::Vec3Array> vec)
{
	osg::Geode* line_gnode = new osg::Geode;
	osg::ref_ptr<osg::Vec3Array>vectex = new osg::Vec3Array;
	osg::ref_ptr<osg::Vec4Array>color = new osg::Vec4Array;
	osg::ref_ptr<osg::Geometry>gemo = new osg::Geometry;
	
	//��һ����
	osg::Vec3d FirstPoint, SecondPoint;
	//��һ���㾭γ��ת��������  ��λ��
	em->convertLatLongHeightToXYZ(osg::DegreesToRadians(vec->at(0).y()), osg::DegreesToRadians(vec->at(0).x()), vec->at(0).z(), FirstPoint.x(), FirstPoint.y(), FirstPoint.z());
	vectex->push_back(FirstPoint);
	//�ڶ����㾭γ��ת��������  ��λ��
	em->convertLatLongHeightToXYZ(osg::DegreesToRadians(vec->at(1).y()), osg::DegreesToRadians(vec->at(1).x()), vec->at(1).z(), SecondPoint.x(), SecondPoint.y(), SecondPoint.z());
	vectex->push_back(SecondPoint);

	//��ɫ
	//color->push_back(osg::Vec4(0.0, 1.0, 0.0, 1.0));
	color->push_back(osg::Vec4(1.0, 0.0, 0.0, 1.0));
	//����
	gemo->setVertexArray(vectex);
	gemo->setColorArray(color);
	//�˾�Ӱ�����Ч��
	//gemo->setColorBinding(osg::Geometry::BIND_PER_VERTEX);   
	gemo->setColorBinding(osg::Geometry::BIND_OVERALL);
	gemo->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP, 0, vectex->size()));
	//�ƹ�
	gemo->getOrCreateStateSet()->setAttribute(new osg::LineWidth(mLineWidth), osg::StateAttribute::ON);
	gemo->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	line_gnode->addDrawable(gemo);

	return line_gnode;
}

osg::Node* DrawXXX::createTrinangle(osg::ref_ptr<osg::Vec3Array> vec)
{
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	osg::ref_ptr<osg::Vec3Array>vectex = new osg::Vec3Array;
	//��һ����
	osg::Vec3d FirstPoint, SecondPoint, ThirdPoint, ForthPoint;
	//��һ���㾭γ��ת��������  ��λ��
	em->convertLatLongHeightToXYZ(osg::DegreesToRadians(vec->at(0).y()), osg::DegreesToRadians(vec->at(0).x()), vec->at(0).z(), FirstPoint.x(), FirstPoint.y(), FirstPoint.z());
	vectex->push_back(FirstPoint);
	//�ڶ����㾭γ��ת��������  ��λ��
	em->convertLatLongHeightToXYZ(osg::DegreesToRadians(vec->at(1).y()), osg::DegreesToRadians(vec->at(1).x()), vec->at(1).z(), SecondPoint.x(), SecondPoint.y(), SecondPoint.z());
	vectex->push_back(SecondPoint);
	//�������㾭γ��ת��������  ��λ��
	em->convertLatLongHeightToXYZ(osg::DegreesToRadians(vec->at(2).y()), osg::DegreesToRadians(vec->at(2).x()), vec->at(2).z(), ThirdPoint.x(), ThirdPoint.y(), ThirdPoint.z());
	vectex->push_back(ThirdPoint);
	geom->setVertexArray(vectex);

	//������ɫ����
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
	geom->setColorArray(c.get());
	//geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);
	c->push_back(osg::Vec4(1.f, 0.f, 0.f, 1.f));
	//���ö��������ʽ
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, 3));
	//�ֶ����巨��
	osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;
	geom->setNormalArray(n.get());
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
	//n->push_back(osg::Vec3(-2.f, -1.f, 10.f));
	n->push_back(osg::Vec3(0.f, -1.f, 0.f));


	//�ƹ�
	//geom->getOrCreateStateSet()->setAttribute(new osg::LineWidth(3.0), osg::StateAttribute::OFF);
	geom->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	osg::Geode *geode = new osg::Geode;
	geode->addDrawable(geom.get());
	return geode;
}
osg::Node* DrawXXX::createParallelogram(osg::ref_ptr<osg::Vec3Array> vec)
{
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	osg::ref_ptr<osg::Vec3Array>vectex = new osg::Vec3Array;
	//��һ����
	osg::Vec3d FirstPoint, SecondPoint,ThirdPoint,ForthPoint;
	//��һ���㾭γ��ת��������  ��λ��
	em->convertLatLongHeightToXYZ(osg::DegreesToRadians(vec->at(0).y()), osg::DegreesToRadians(vec->at(0).x()), vec->at(0).z(), FirstPoint.x(), FirstPoint.y(), FirstPoint.z());
	vectex->push_back(FirstPoint);
	//�ڶ����㾭γ��ת��������  ��λ��
	em->convertLatLongHeightToXYZ(osg::DegreesToRadians(vec->at(1).y()), osg::DegreesToRadians(vec->at(1).x()), vec->at(1).z(), SecondPoint.x(), SecondPoint.y(), SecondPoint.z());
	vectex->push_back(SecondPoint);
	//�������㾭γ��ת��������  ��λ��
	em->convertLatLongHeightToXYZ(osg::DegreesToRadians(vec->at(2).y()), osg::DegreesToRadians(vec->at(2).x()), vec->at(2).z(), ThirdPoint.x(), ThirdPoint.y(), ThirdPoint.z());
	//ThirdPoint.x() = -ThirdPoint.x();
	//ThirdPoint.y() = -ThirdPoint.y();
	//ThirdPoint.z() = -ThirdPoint.z();
	vectex->push_back(ThirdPoint);
	//���ĸ��㾭γ��ת��������  ��λ��
	ForthPoint.x() =- SecondPoint.x() + FirstPoint.x() + ThirdPoint.x();
	ForthPoint.y() =- SecondPoint.y() + FirstPoint.y() + ThirdPoint.y();
	ForthPoint.z() =- SecondPoint.z() + FirstPoint.z() + ThirdPoint.z();
	vectex->push_back(ForthPoint);
	geom->setVertexArray(vectex);

	//������ɫ����
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
	geom->setColorArray(c.get());
	//geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);
	c->push_back(osg::Vec4(1.f, 0.f, 0.f, 1.f));
	/*c->push_back(osg::Vec4(0.f, 1.f, 0.f, 1.f));
	c->push_back(osg::Vec4(0.f, 0.f, 1.f, 1.f));
	c->push_back(osg::Vec4(1.f, 1.f, 1.f, 1.f));*/
	//���ö��������ʽ
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
	//geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, 4));
	//����һ
	//�ֶ����巨��
	osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;
	geom->setNormalArray(n.get());
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
	//n->push_back(osg::Vec3(-2.f, -1.f, 10.f));
	n->push_back(osg::Vec3(0.f, -1.f, 0.f));
	//������
	//�Զ����ɷ���
	//osgUtil::SmoothingVisitor::smooth(*(geom.get()));//�Զ����ɷ���

	//�ƹ�
	//geom->getOrCreateStateSet()->setAttribute(new osg::LineWidth(3.0), osg::StateAttribute::OFF);
	geom->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	osg::Geode *geode = new osg::Geode;
	geode->addDrawable(geom.get());
	return geode;
}

