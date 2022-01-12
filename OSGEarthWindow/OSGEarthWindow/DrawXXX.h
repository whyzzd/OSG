#pragma once
#include<osgViewer/Viewer>

class DrawXXX
{
public:
	DrawXXX();
	DrawXXX(float wid);
	~DrawXXX();

	//������
	osg::Node* createLine(osg::ref_ptr<osg::Vec3Array> vec);
	//����������
	osg::Node* createTrinangle(osg::ref_ptr<osg::Vec3Array> vec);
	//���ƾ���
	osg::Node* createParallelogram(osg::ref_ptr<osg::Vec3Array> vec);
	
	
	/*osg::Node* createTest(){
		return new osg::Node;
	}
*/
	
	float mLineWidth;
protected:

private:
	osg::ref_ptr<osg::EllipsoidModel>em;
};