#pragma once
#include<QUndoCommand>
#include<OsgContainer.h>
#include<osgEarthAnnotation/FeatureEditing>
//一次操作创建一次命令对象
class AddNodeCommand :public QUndoCommand
{
public:
	AddNodeCommand(OsgContainer**viewer, osgEarth::Annotation::FeatureEditor *editor);
	AddNodeCommand(OsgContainer**viewer, osgEarth::Annotation::FeatureEditor *editor, osgEarth::Annotation::FeatureNode*node);
	
	~AddNodeCommand();

	void undo() override;
	void redo() override;

private:
	OsgContainer **m_viewer;
	osg::ref_ptr<osgEarth::Annotation::FeatureEditor> m_editor;
	osg::ref_ptr<osgEarth::Annotation::FeatureEditor> m_editor1;

	osg::ref_ptr<osgEarth::Annotation::FeatureNode> m_node;
	osg::ref_ptr<osgEarth::Annotation::FeatureNode> m_node1;
};

class DelNodeCommand :public QUndoCommand
{
public:
	DelNodeCommand(OsgContainer**viewer, osgEarth::Annotation::FeatureEditor *editor);
	DelNodeCommand(OsgContainer**viewer, osgEarth::Annotation::FeatureEditor *editor, osgEarth::Annotation::FeatureNode*node);
	~DelNodeCommand();

	void undo() override;
	void redo() override;

private:
	OsgContainer **m_viewer;
	osg::ref_ptr<osgEarth::Annotation::FeatureEditor> m_editor;
	osg::ref_ptr<osgEarth::Annotation::FeatureEditor> m_editor1;
	osg::ref_ptr<osgEarth::Annotation::FeatureNode> m_node;
	osg::ref_ptr<osgEarth::Annotation::FeatureNode> m_node1;
};