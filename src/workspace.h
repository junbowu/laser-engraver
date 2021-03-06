#pragma once

#include <QGraphicsScene>

#include <src/dialogs/font-dialog.h>
#include <src/models/graphical-object-model.h>
#include <src/sheets.hpp>

class Workspace : public QGraphicsScene {
	Q_OBJECT
public:
	Workspace(qreal x, qreal y, qreal w, qreal h);

	void setDisableBackground(bool value) noexcept;
	void setGridSize(double size) noexcept;

	void drawSheetAreas(std::vector<inverter<sheet::metrics>> &&papers);
	void updateDpi(double dpi, bool scaleObjectWithDpi);

	bool insertPixmapObject(const QString &) noexcept;
	void insertTextObject(const TextWithFont &) noexcept;
	void remove(QGraphicsItem *item) noexcept;

	void selected_object_move_up();
	void selected_object_move_down();
	void selected_object_raise_to_top();
	void selected_object_lower_to_bottom();
	void selected_object_center();
	void selected_object_remove();

	graphical::model *model();
	QGraphicsItem *selected_object();

protected:
	void drawBackground(QPainter *painter, const QRectF &rect) final;

private:
	void drawGrid(QPainter *painter, const QRectF &rect) noexcept;
	void drawXAxis(QPainter *painter, QRect &&scene) noexcept;
	void drawYAxis(QPainter *painter, QRect &&scene) noexcept;
	void drawSheet(QPainter *painter, const inverter<sheet::metrics> &) noexcept;
	void setCommonObjectParameters(QGraphicsItem *);

signals:
	void objectSelectionChanged(bool);
	void objectSelectionChanged(QGraphicsItem *);

private:
	std::unique_ptr<graphical::model> m_model;
	std::vector<inverter<sheet::metrics>> m_papers;
	double m_dpi{300.0};

	double m_gridSize{10.00};

	QColor m_xAxisColor{0xff, 0x00, 0x00, 0x9f};
	QColor m_yAxisColor{0x00, 0xff, 0x00, 0x9f};

	bool m_disableBackground{false};
	bool m_xAxisEnabled{true};
	bool m_yAxisEnabled{true};

	QGraphicsItem *m_selected_object{nullptr};
};
