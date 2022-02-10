#pragma once
#include<QUndoCommand>
class SliderUndoCommand :public QUndoCommand
{
public:
	SliderUndoCommand();
	~SliderUndoCommand();

	void undo() override;
	void redo() override;

private:
};