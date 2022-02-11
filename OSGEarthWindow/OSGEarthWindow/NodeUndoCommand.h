#pragma once
#include<QUndoCommand>
#include<OsgContainer.h>
#include<osgEarthAnnotation/FeatureEditing>
//һ�β�������һ���������
class AddNodeCommand :public QUndoCommand
{
public:
	AddNodeCommand(OsgContainer**viewer, osgEarth::Annotation::FeatureEditor *editor);
	~AddNodeCommand();

	void undo() override;
	void redo() override;

private:
	OsgContainer **m_viewer;
	osg::ref_ptr<osgEarth::Annotation::FeatureEditor> m_editor;
	osg::ref_ptr<osgEarth::Annotation::FeatureEditor> m_editor1;
};

class DelNodeCommand :public QUndoCommand
{
public:
	DelNodeCommand(OsgContainer**viewer, osgEarth::Annotation::FeatureEditor *editor);
	~DelNodeCommand();

	void undo() override;
	void redo() override;

private:
	OsgContainer **m_viewer;
	osg::ref_ptr<osgEarth::Annotation::FeatureEditor> m_editor;
	osg::ref_ptr<osgEarth::Annotation::FeatureEditor> m_editor1;
};